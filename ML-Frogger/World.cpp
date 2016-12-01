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
#include "Utility.h"
#include "SoundPlayer.h"
#include "SoundNode.h"
#include "DataTables.h"
#include "LaneNode.h"
#include "Vehicule.h"
#include "WaterLaneNode.h"
#include "WaterObject.h"

namespace GEX
{
	bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2);
	const std::map<Vehicule::Type, LaneData> table = initializeLaneData();

	World::World(sf::RenderWindow& window/*, SoundPlayer& soundPlayer*/ ) :
		_window(window),
		_worldView(window.getDefaultView()),
		//_soundPlayer(soundPlayer),
		_sceneGraph(),
		_sceneLayers(),
		_commandQueue(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2, _worldView.getSize().y - 20)
	
		
	{
		buildScene();
		
		// start the view at the bottom of the world
		//_worldView.setCenter(_spawnPosition);
	}

	void World::update(sf::Time deltaTime)
	{		
		//_playerAircraft->setVelocity(0.f, 0.f);

		updateSound();		

		while (!_commandQueue.isEmpty())
		{
			_sceneGraph.onCommande(_commandQueue.pop(), deltaTime);
		}

		handleCollisions();
		_sceneGraph.removeWercks();

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
	{			
		/*return !_playerFrog->isMarkedForRemoval();*/
		return true;
	}	

	
	void World::buildScene()
	{
		// Put the layer nodes into the scene graph
		for (std::size_t i = 0; i < LayerCount; ++i)
		{
			Category::Type category = (i == Ground) ? Category::SceneGroundLayer : Category::None;
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

		// add frog to the ground layer
		std::unique_ptr<Frog> frog(new Frog());
		_playerFrog = frog.get();
		_playerFrog->setPosition(_spawnPosition);
		_sceneLayers[Ground]->attachChild(std::move(frog));		

		std::unique_ptr<LaneNode> laneOne(new LaneNode(Vehicule::Type::RaceCar1));
		_sceneLayers[Ground]->attachChild(std::move(laneOne));

		std::unique_ptr<LaneNode> laneTwo(new LaneNode(Vehicule::Type::Tracktor));
		_sceneLayers[Ground]->attachChild(std::move(laneTwo));

		std::unique_ptr<LaneNode> laneThree(new LaneNode(Vehicule::Type::Car));
		_sceneLayers[Ground]->attachChild(std::move(laneThree));

		std::unique_ptr<LaneNode> laneFour(new LaneNode(Vehicule::Type::RaceCar2));
		_sceneLayers[Ground]->attachChild(std::move(laneFour));

		std::unique_ptr<LaneNode> laneFive(new LaneNode(Vehicule::Type::Truck));
		_sceneLayers[Ground]->attachChild(std::move(laneFive));

		std::unique_ptr<WaterLaneNode> waterOne(new WaterLaneNode(WaterObject::Type::Turtle3));
		_sceneLayers[Ground]->attachChild(std::move(waterOne));

		std::unique_ptr<WaterLaneNode> waterTwo(new WaterLaneNode(WaterObject::Type::Log4));
		_sceneLayers[Ground]->attachChild(std::move(waterTwo));

		std::unique_ptr<WaterLaneNode> waterTrree(new WaterLaneNode(WaterObject::Type::Log3));
		_sceneLayers[Ground]->attachChild(std::move(waterTrree));

		std::unique_ptr<WaterLaneNode> waterFour(new WaterLaneNode(WaterObject::Type::Turtle2));
		_sceneLayers[Ground]->attachChild(std::move(waterFour));

		std::unique_ptr<WaterLaneNode> waterFive(new WaterLaneNode(WaterObject::Type::Log5));
		_sceneLayers[Ground]->attachChild(std::move(waterFive));

	
	}

	sf::FloatRect World::getViewBounds() const
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}

	sf::FloatRect World::getBattleFieldBound() const
	{
		sf::FloatRect bounds = getViewBounds();		
		bounds.width += 40;
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


