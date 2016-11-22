/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

world class

*/


#include "World.h"
#include "Airplaine.h"
#include "TextureHolder.h"
#include "SpriteNode.h"
#include <math.h>
#include "ResourceIdentifiers.h"
#include <algorithm>
#include "Pickup.h"
#include "ParticuleNode.h"
#include "SoundPlayer.h"
#include "SoundNode.h"

namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer ) :
		_window(window),
		_worldView(window.getDefaultView()),
		_soundPlayer(soundPlayer),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, 2000.f),
		_spawnPosition(_worldView.getSize().x / 2,
		_worldBounds.height - (_worldView.getSize().y / 2.f)),
		_scrollSpeed(-50.0f),
		_playerAircraft(nullptr)
		
	{
		buildScene();
		addEnemies();
		// start the view at the bottom of the world
		_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time deltaTime)
	{
		_worldView.move(0.f, _scrollSpeed * deltaTime.asSeconds());
		_playerAircraft->setVelocity(0.f, 0.f);

		updateSound();

		guidMissiles();
		destroyEntitieOurSideView();

		while (!_commandQueue.isEmpty())
		{
			_sceneGraph.onCommande(_commandQueue.pop(), deltaTime);
		}

		handleCollisions();
		_sceneGraph.removeWercks();
		spawnEnemies();

		//// adjust player position
		//sf::Vector2f position = _playerAircraft->getPosition();
		//sf::Vector2f velocity = _playerAircraft->getVelocity();
		//float angularVelocity = _playerAircraft->getRotation();

		//if (velocity.x != 0 && velocity.y != 0)
		//{
		//	_playerAircraft->setVelocity(velocity / sqrtf(2.f));
		//}

		//_playerAircraft->setRotation(angularVelocity);
		// apply movements
		_sceneGraph.update(deltaTime, _commandQueue);
		adapPlayerPosition();
	}

	void World::guidMissiles()
	{
		// set up command to get a list of ennemy planes

		Command enemyColector;
		enemyColector.category = Category::EnnemyAircraft;
		enemyColector.action = derivedAction<Airplaine>([this](Airplaine& enemy, sf::Time dt)
		{
			if (!enemy.isDestroyed())
				this->_activeEnemies.push_back(&enemy);
		});

		// set up missile guider

		Command missileGuider;
		missileGuider.category = Category::AlliedProjectile;
		missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt)
		{
			// ignore bullet
			if (!missile.isGuided())
				return;
			float minDist = std::numeric_limits<float>::max();
			Airplaine* closestEnemy = nullptr;

			for (Airplaine* enemy : this->_activeEnemies)
			{
				float enemyDistance = distance(missile, *enemy);

				if (enemyDistance < minDist)
				{
					closestEnemy = enemy;
					minDist = enemyDistance;
				}
			}

			if (closestEnemy)
			{
				missile.guideTowards(closestEnemy->getWorldPosition());
			}
		});

		// clear enemi list
		_activeEnemies.clear();
		// push commands
		_commandQueue.push(enemyColector);
		_commandQueue.push(missileGuider);		
	}

	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);

	}

	void World::adapPlayerPosition()
	{
		sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 25.f;

		sf::Vector2f position = _playerAircraft->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerAircraft->setPosition(position);
	}

	CommandeQueue & World::getCommandQueue()
	{
		return _commandQueue;
	}

	bool World::hasAlivePlayer()
	{	// find the bug
		
		return !_playerAircraft->isMarkedForRemoval();		
	}

	bool World::hasReachedFinich() const
	{	
		return !_worldBounds.contains(_playerAircraft->getPosition());
		
	}


	void World::buildScene()
	{
		// Put the layer nodes into the scene graph
		for (std::size_t i = 0; i < LayerCount; ++i)
		{
			Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;
			SceneNode::Ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attachChild(std::move(layer));
		}

		

		//prepare tiled background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Jungle);
		sf::IntRect textureRect(0, 0, 2000, 4000);
		texture.setRepeated(true);

		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		background->setPosition(_worldBounds.left, _worldBounds.top - 2000.f);
		_sceneLayers[Backgroud]->attachChild(std::move(background));


		


		// Add the background sprite to the scene
		sf::Texture& finish = TextureHolder::getInstance().get(TextureID::FinishLine);
		sf::IntRect FinishRect(0, 0, 1024, 76);
		std::unique_ptr<SpriteNode> finishLine(new SpriteNode(finish, FinishRect));
		_sceneLayers[FinishLine]->attachChild(std::move(finishLine));



		//particle system
		std::unique_ptr<ParticuleNode> smokeNode(new ParticuleNode(Particule::Type::Smoke));
		_sceneLayers[Air]->attachChild(std::move(smokeNode));

		std::unique_ptr<ParticuleNode> fireNode(new ParticuleNode(Particule::Type::Propellant));
		_sceneLayers[Air]->attachChild(std::move(fireNode));


		// Add player's aircraft
		std::unique_ptr<Airplaine> leader(new Airplaine(Airplaine::Type::Eagle));
		_playerAircraft = leader.get();
		_playerAircraft->setPosition(_spawnPosition);
		_playerAircraft->setVelocity(0.f, _scrollSpeed);
		_sceneLayers[Air]->attachChild(std::move(leader));

		// add SoundNode

		std::unique_ptr<SoundNode> soundEffectNode(new SoundNode(_soundPlayer));
		_sceneGraph.attachChild(std::move(soundEffectNode));
	
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattleFieldBound() const
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.top -= 100;
		bounds.height += 100;
		return bounds;
	}
	void World::spawnEnemies()
	{
		while (!_enemiSpanPoint.empty() && _enemiSpanPoint.back().y > getBattleFieldBound().top)
		{
			auto span = _enemiSpanPoint.back();
			std::unique_ptr<Airplaine> enemy(new Airplaine(span.type));
			enemy->setPosition(span.x, span.y);			
			enemy->setRotation(180);
			_sceneLayers[Air]->attachChild(std::move(enemy));
			_enemiSpanPoint.pop_back();
		}
	}
	void World::addEnemies()
	{
		//add enemy spwan point

		addEnemy(Airplaine::Type::Avenger, -250.f, 200);
		addEnemy(Airplaine::Type::Avenger,  250.f, 200);
		addEnemy(Airplaine::Type::Raptor, -350.f, 400);
		addEnemy(Airplaine::Type::Raptor,  350.f, 400);

		addEnemy(Airplaine::Type::Avenger, -250.f, 800);
		addEnemy(Airplaine::Type::Avenger, 250.f, 800);
		addEnemy(Airplaine::Type::Raptor, -350.f, 900);
		addEnemy(Airplaine::Type::Raptor, 350.f, 900);

		/*addEnemy(Airplaine::Type::Avenger, -250.f, 800);
		addEnemy(Airplaine::Type::Raptor, 250.f, 800);
		addEnemy(Airplaine::Type::Raptor, -350.f, 900);
		addEnemy(Airplaine::Type::Raptor, 350.f, 900);*/

		std::sort(_enemiSpanPoint.begin(), _enemiSpanPoint.end(), [](SpawnPoint lhs, SpawnPoint rhs)
		{
			return lhs.y < rhs.y;
		});
		
	}
	void World::addEnemy(Airplaine::Type type, float relx, float rely)
	{
		addEnemy(SpawnPoint(type, relx, rely));
	}

	void World::addEnemy(SpawnPoint sp)
	{
		sp.x = _spawnPosition.x + sp.x;
		sp.y = _spawnPosition.y - sp.y;
		_enemiSpanPoint.push_back(sp);
	}
	void World::handleCollisions()
	{
		// build a list of all pair of colloding scenenode all pair
		std::set<SceneNode::Pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		// for each collision do someting
		for (auto pair : collisionPairs)
		{
			if (matchesCategories(pair, Category::PlayerAircraft, Category::EnnemyAircraft))
			{
				auto& player = static_cast<Airplaine&> (*pair.first);
				auto& enemy = static_cast<Airplaine&>(*pair.second);

				player.damage(enemy.getHitPoint());
				enemy.destroy();
			}

			if (matchesCategories(pair, Category::EnnemyAircraft, Category::AlliedProjectile) ||
				matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
			{
				auto& Airplaines = static_cast<Airplaine&> (*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

				Airplaines.damage(projectile.getHitPoint());
				projectile.destroy();
			}

			/*if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
			{
				auto& playerAirplaine = static_cast<Airplaine&> (*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

				playerAirplaine.damage(projectile.getHitPoint());
				projectile.destroy();
			}*/
			// to do
			if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
			{
				auto& playerAirplaine = static_cast<Airplaine&> (*pair.first);
				auto& pickup = static_cast<Pickup&>(*pair.second);

				pickup.apply(playerAirplaine);
				pickup.destroy();
				playerAirplaine.playLocalSound(_commandQueue, SoundEffectID::CollectPickup);
			}
		}
	}

	void World::destroyEntitieOurSideView()
	{
		Command command;
		command.category = Category::Projectile | Category::EnnemyAircraft;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattleFieldBound().intersects(e.getBoundingRect()))
				e.destroy();
		});

		_commandQueue.push(command);
	}

	void World::updateSound()
	{
		_soundPlayer.setListenerPosition(_playerAircraft->getWorldPosition());
		_soundPlayer.removeStoppedSounds();
	}

	

	bool matchesCategories(SceneNode::Pair & colliders, Category::Type type1, Category::Type type2)
	{
		unsigned int category1 = colliders.first->getCategory();
		unsigned int category2 = colliders.second->getCategory();

		if (type1 & category1 && type2 & category2)
		{
			return true;
		}
		else if (type1 & category2 && type2 & category1)
		{
			std::swap(colliders.first, colliders.second);
			return true;
		}
		else
			return false;		
	}
}


