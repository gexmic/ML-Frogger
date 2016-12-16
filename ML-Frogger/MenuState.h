/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

The menu state is where you have the menu play or exit the game with the backgound of frogger.

*/

#pragma once
#include "State.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace GEX
{

	class MenuState : public State
	{
	public:
								MenuState(StateStack& stack, Context context);

		virtual void            draw();
		virtual bool            update(sf::Time dt);
		virtual bool            handleEvent(const sf::Event& event);
		void                    updateOptionText();

	private:
		enum OptionNames
		{
			Play,
			Exit,
		};

	private:
		sf::Sprite              _backgroundSprite;

		std::vector<sf::Text>   _options;
		std::size_t             _optionIndex;
	};
}


