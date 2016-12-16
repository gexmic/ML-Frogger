/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

This is the class of the game state. the game state is wen the player control the frog.

*/

#pragma once
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "World.h"
#include "PlayerControl.h"
#include "State.h"
#include "CommandeQueue.h"

namespace GEX
{


	class GameState : public State
	{
	public:
							GameState(StateStack& stack, Context context);

		virtual void        draw();
		virtual bool        update(sf::Time dt);
		virtual bool        handleEvent(const sf::Event& event);


	private:
		World               _world;
		PlayerControl&      _player;

	};
}

