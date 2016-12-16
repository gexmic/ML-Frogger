/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

different state the game could be in
*/


#pragma once
#include "SFML/System/Time.hpp"
#include "SFML/Window/Event.hpp"
#include <memory>
#include "StateIdentifiers.h"

namespace sf
{
	class RenderWindow;
}

namespace GEX
{
	class StateStack;
	class PlayerControl;
	class MusicPlayer;
	class SoundPlayer;

	class State
	{
	public:
		typedef std::unique_ptr<State> Ptr;

		struct Context
		{
			Context(sf::RenderWindow& window, PlayerControl& player);

			sf::RenderWindow*   window;
			PlayerControl*      player;
		};


	public:
							State(StateStack& stack, Context context);
		virtual             ~State();

		virtual void        draw() = 0;
		virtual bool        update(sf::Time dt) = 0;
		virtual bool        handleEvent(const sf::Event& event) = 0;

	protected:
		void                requestStackPush(StateID stateID);
		void                requestStackPop();
		void                requestStateClear();
		Context             getContext() const;

	private:
		StateStack*         _stack;
		Context             _context;
	};
}