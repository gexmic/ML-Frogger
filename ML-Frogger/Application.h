/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the frogger game for my project at NBCC Moncton programing course

@section DESCRIPTION

Application class will run the game loop and load the materia that is required in the 
begining of the game.

*/

#pragma once
#include "PlayerControl.h"
#include "StateStack.h"

#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "CommandeQueue.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

namespace GEX
{

	class Application
	{
	public:
								Application();
		void                    run();

	private:
		void                    processInput();
		void                    update(sf::Time dt);
		void                    render();

		void                    updateStatistics(sf::Time dt);
		void                    registerStates();

	private:
		static const sf::Time   TimePerFrame;

		sf::RenderWindow        _window;
		PlayerControl           _player;		
		MusicPlayer				_music;
		SoundPlayer				_soundPlayer;
		StateStack              _stateStack;
		sf::Text                _statsText;
	};
}
