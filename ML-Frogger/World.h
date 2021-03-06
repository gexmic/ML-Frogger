/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

tthis world class is the world of the game. It will draw the backgound the airplane and enneni plane. later it will also have the drop item

*/


#pragma once
///

#include "SFML\Graphics.hpp"
#include "SceneNode.h"
#include <array>
#include "CommandeQueue.h"
#include <vector>
#include "Airplaine.h"
#include "CommandeQueue.h"
#include "SoundPlayer.h"



namespace GEX
{

	class World
	{
	private:
		struct SpawnPoint
		{
			SpawnPoint(Airplaine::Type type, float _x, float _y) :
				type(type),
				x(_x),
				y(_y)
			{}
			Airplaine::Type					type;
			float							x;
			float							y;
		};

	public:
		/// make non-copy
		World(const World&) = delete;
		World&								operator=(const World&) = delete;

		/// constructor						
		explicit							World(sf::RenderWindow& target, SoundPlayer& soundPlayer);

		void								update(sf::Time deltaTime);
		void								guidMissiles();
		void								draw();
		void								adapPlayerPosition();
		CommandeQueue&						getCommandQueue();
		bool								hasAlivePlayer();
		bool								hasReachedFinich() const;


	private:
		void								buildScene();

		sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattleFieldBound() const;
		void								spawnEnemies();
		void								addEnemies();
		void								addEnemy(Airplaine::Type type, float relx, float rely);
		void								addEnemy(SpawnPoint spoint);
		void								handleCollisions();
		void								destroyEntitieOurSideView();
		void								updateSound();


	private:
		enum Layer
		{
			Backgroud,
			Air,
			FinishLine,
			LayerCount
		};

	private:
		sf::RenderWindow&						_window;
		sf::View								_worldView;
		SceneNode								_sceneGraph;
		std::array<SceneNode*, LayerCount>		_sceneLayers;
		CommandeQueue							_commandQueue;
		SoundPlayer&							_soundPlayer;

		sf::FloatRect							_worldBounds;
		sf::Vector2f							_spawnPosition;
		sf::Vector2f							_finishline;
		float									_scrollSpeed;
		Airplaine*								_playerAircraft;
		std::vector<SpawnPoint>					_enemiSpanPoint;
		std::vector<Airplaine*>					_activeEnemies;
	};
}


