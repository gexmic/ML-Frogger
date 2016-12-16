/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Player control class

*/

#include "PlayerControl.h"
#include "Category.h"
#include "Frog.h"

namespace GEX
{
	struct FrogMover
	{
		FrogMover(float vx, float vy) : frogHop(vx, vy)
		{}
		void operator() (Frog& frog, sf::Time dt) const	{

			frog.move(frogHop.x, frogHop.y, dt);
		}
		sf::Vector2f frogHop;
	};

	PlayerControl::PlayerControl() 
	{
		initializaKeyBindings();
		initializaActionBindings();

	}

	void PlayerControl::handleEvent(const sf::Event& event, CommandeQueue& commands)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			auto found = _keyBindings.find(event.key.code);
			if (found != _keyBindings.end())
			{
				commands.push(_actionBindings[found->second]);
			}
		}
	}

	void PlayerControl::handleRealTimeInput(CommandeQueue& commands)
	{
		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);
		}
	}

	void PlayerControl::initializaKeyBindings()
	{
		_keyBindings[sf::Keyboard::Left]	= Action::MoveLeft;
		_keyBindings[sf::Keyboard::Right]	= Action::MoveRight;
		_keyBindings[sf::Keyboard::Up]		= Action::MoveUp;
		_keyBindings[sf::Keyboard::Down]	= Action::MoveDown;
	}

	void PlayerControl::initializaActionBindings()
	{
		const float playerSpeed = 200.f;


		_actionBindings[Action::MoveLeft].action		= derivedAction<Frog>(FrogMover(-40, 0.f));
		_actionBindings[Action::MoveRight].action		= derivedAction<Frog>(FrogMover(40, 0.f));
		_actionBindings[Action::MoveUp].action			= derivedAction<Frog>(FrogMover(0.f, -40));
		_actionBindings[Action::MoveDown].action		= derivedAction<Frog>(FrogMover(0.f, 40));

		for (auto& pair : _actionBindings)
		{
			pair.second.category = Category::Frog;
		}	
	}

	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveUp:
		case Action::MoveDown:
			return false;
		default:
			return false;
		}
	}	
}