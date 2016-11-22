/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the frogger game for my project at NBCC Moncton programing course

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Application class will run the game loop and load the materia that is required in the
begining of the game.

*/

#include "Application.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "FontHolder.h"
#include "TitleState.h"

#include "GameOver.h"


namespace GEX
{

	const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

	Application::Application() :
		_window(sf::VideoMode(480, 600), "States", sf::Style::Close),
		_player(),
		_stateStack(State::Context(_window, _player, _music /*_soundPlayer*/)),
		_statsText()
	{
		_window.setKeyRepeatEnabled(false);

		FontHolder::getInstance().load(FontID::Main,				"../Media/Sansation.ttf");
		TextureHolder::getInstance().load(TextureID::TitleScreen,	"../Media/Textures/FroggerTitle.png");
		TextureHolder::getInstance().load(TextureID::MenuScreen,	"../Media/Textures/FroggerTitle.png");
		TextureHolder::getInstance().load(TextureID::Background,     "../Media/Textures/background.png");
		

		_statsText.setFont(FontHolder::getInstance().get(FontID::Main));
		_statsText.setPosition(5.f, 5.f);
		_statsText.setCharacterSize(10u);

		registerStates();
		_stateStack.pushState(StateID::Title);
	}

	void Application::run()
	{

		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;
		while (_window.isOpen())
		{
			sf::Time dt = clock.restart();
			timeSinceLastUpdate += dt;


			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processInput();
				update(TimePerFrame);

				if (_stateStack.isEmpty())
					_window.close();
			}
			updateStatistics(dt);
			render();
		}
	}

	void Application::processInput()
	{
		sf::Event event;

		while (_window.pollEvent(event))
		{
			_stateStack.handleEvent(event);

			if (event.type == sf::Event::Closed)
				_window.close();
		}

	}

	void Application::update(sf::Time dt)
	{
		_stateStack.update(dt);
	}

	void Application::render()
	{
		_window.clear();
		_stateStack.draw();

		_window.setView(_window.getDefaultView());
		_window.draw(_statsText);

		_window.display();
	}

	void Application::updateStatistics(sf::Time dt)
	{
		static int numFrames = 0;
		static sf::Time timePassed = sf::Time::Zero;

		timePassed += dt;
		numFrames += 1;

		if (timePassed >= sf::seconds(1.f))
		{
			_statsText.setString(
				"Frame / Second = " + std::to_string(numFrames) + "\n" +
				"Time / Update = " + std::to_string(timePassed.asMicroseconds() / numFrames) + "us");
			numFrames = 0;
			timePassed -= sf::seconds(1.f);
		}
	}

	void Application::registerStates()
	{
		_stateStack.registerState<TitleState>			(StateID::Title);
		_stateStack.registerState<MenuState>			(StateID::Menu);
		_stateStack.registerState<GameState>			(StateID::Game);
	}



}