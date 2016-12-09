/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This class is for all the command that the player could do in the game for moving the frog and navigate to the menu. Also later

*/

#pragma once
#include "SFML/Graphics.hpp"
#include "CommandeQueue.h"
#include "Command.h"
#include <map>
#include "Animation2.h"

namespace GEX
{
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
	};	

	class PlayerControl
	{
	public:
												PlayerControl();
		
		void									handleEvent(const sf::Event& event, CommandeQueue& commands);
		void									handleRealTimeInput(CommandeQueue& commands);
	private:
		void									initializaKeyBindings();
		void									initializaActionBindings();
		bool									isRealTimeAction(Action action);
		

	private:
		std::map<sf::Keyboard::Key, Action>		_keyBindings;
		std::map<Action, Command>				_actionBindings;
		
	};

}

