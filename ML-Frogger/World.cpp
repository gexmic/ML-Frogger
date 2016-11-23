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
#include "TextureHolder.h"
#include "SpriteNode.h"
#include <math.h>
#include "ResourceIdentifiers.h"
#include <algorithm>
#include <iostream>

#include "SoundPlayer.h"
#include "SoundNode.h"

namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);

	World::World(sf::RenderWindow& window/*, SoundPlayer& soundPlayer*/ ) :
		_window(window),
		_worldView(window.getDefaultView()),
		//_soundPlayer(soundPlayer),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, 600),
		_spawnPosition(_worldView.getSize().x / 2, _worldView.getSize().y - 20)
	
		
	{
		buildScene();
		
		// start the view at the bottom of the world
		//_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time deltaTime)
	{
		
		std::cout << _playerFrog->getPosition().x << "  " << _playerFrog->getPosition().y << std::endl;
		//_playerAircraft->setVelocity(0.f, 0.f);

		updateSound();

		
		destroyEntitieOurSideView();

		while (!_commandQueue.isEmpty())
		{
			_sceneGraph.onCommande(_commandQueue.pop(), deltaTime);
		}

		handleCollisions();
		_sceneGraph.removeWercks();

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

	
	void World::draw()
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);

	}

	void World::adapPlayerPosition()
	{
		/*sf::FloatRect viewBounds(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
		const float borderDistance = 25.f;

		sf::Vector2f position = _playerFrog->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerFrog->setPosition(position);*/
	}

	CommandeQueue & World::getCommandQueue()
	{
		return _commandQueue;
	}

	bool World::hasAlivePlayer()
	{	// find the bug
		
		/*return !_playerFrog->isMarkedForRemoval();*/
		return true;
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
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(0, 0, 480, 600);

		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		background->setPosition(_worldBounds.left, _worldBounds.top );
		_sceneLayers[Backgroud]->attachChild(std::move(background));		

		std::unique_ptr<Frog> frog(new Frog());
		_playerFrog = frog.get();
		_playerFrog->setPosition(_spawnPosition);
		_sceneLayers[Air]->attachChild(std::move(frog));
	
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
	
	
	void World::handleCollisions()
	{
		// build a list of all pair of colloding scenenode all pair
		std::set<SceneNode::Pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);

		// for each collision do someting
	/*	for (auto pair : collisionPairs)
		{
			if (matchesCategories(pair, Category::PlayerAircraft, Category::EnnemyAircraft))
			{
				auto& player = static_cast<Airplaine&> (*pair.first);
				auto& enemy = static_cast<Airplaine&>(*pair.second);

				player.damage(enemy.getHitPoint());
				enemy.destroy();
			}*/

			

			/*if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
			{
				auto& playerAirplaine = static_cast<Airplaine&> (*pair.first);
				auto& projectile = static_cast<Projectile&>(*pair.second);

				playerAirplaine.damage(projectile.getHitPoint());
				projectile.destroy();
			}*/
			// to do
		
		
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
		/*_soundPlayer.setListenerPosition(_playerFrog->getWorldPosition());
		_soundPlayer.removeStoppedSounds();*/
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


