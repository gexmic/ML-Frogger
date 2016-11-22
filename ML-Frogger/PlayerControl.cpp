/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

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
		FrogMover(float vx, float vy) : velocity(vx, vy)
		{}
		void operator() (Frog& frog, sf::Time dt) const
		{
			//frog.accelerate(velocity);
		}
		sf::Vector2f velocity;
	};

	PlayerControl::PlayerControl() :
		_missionStatus(MissionStatus::Active)
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
		_keyBindings[sf::Keyboard::Space]	= Action::FireBullet;
		_keyBindings[sf::Keyboard::M]		= Action::launchMissile;
	}

	void PlayerControl::initializaActionBindings()
	{
		const float playerSpeed = 200.f;

		_actionBindings[Action::MoveLeft].action		= derivedAction<Frog>(FrogMover(-playerSpeed, 0.f));
		_actionBindings[Action::MoveRight].action		= derivedAction<Frog>(FrogMover(playerSpeed, 0.f));
		_actionBindings[Action::MoveUp].action			= derivedAction<Frog>(FrogMover(0.f, -playerSpeed));
		_actionBindings[Action::MoveDown].action		= derivedAction<Frog>(FrogMover(0.f, playerSpeed));


		for (auto& pair : _actionBindings)
		{
			pair.second.category = Category::PlayerAircraft;
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
			return true;
		default:
			return false;
		}
	}
	void PlayerControl::setMissionStatus(MissionStatus status)
	{
		_missionStatus = status;
	}
	MissionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}
}


