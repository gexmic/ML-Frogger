/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Frog class manage the direction the frog whil move, animation and the sprite of the frog and the life left.

*/

#include "Frog.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "JsonFrameParser.hpp"

namespace GEX
{
	Frog::Frog() :
		_frogLocation(61, 1, 33, 23), // set the location of the frog in the sprite sheet will be move later in the table.
		_liveLocation(6, 1, 18, 21), // set the location of the live icon in the sprite sheet will be move later in the table.
		_sprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_livesSprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_lives(3)
	{
		_sprite.setTextureRect(_frogLocation);
		centerOrigin(_sprite);

		_livesSprite.setTextureRect(_liveLocation);
		centerOrigin(_livesSprite);

		// add to the map all the animation for the frof movement 
		JsonFrameParser frames("../Media/Textures/FroggerAtlas.json");

		_animations[State::MoveIdel] = std::unique_ptr<Animation2>(new Animation2(false));
		_animations[State::MoveIdel]->addFrameSet(frames.getFramesFor("up 2"));

		_animations[State::MoveLeft] = std::unique_ptr<Animation2>(new Animation2(false));
		_animations[State::MoveLeft]->addFrameSet(frames.getFramesFor("left"));
		_animations[State::MoveLeft]->setDurationAsSeconds(0.40f);

		_animations[State::MoveRight] = std::unique_ptr<Animation2>(new Animation2(false));
		_animations[State::MoveRight]->addFrameSet(frames.getFramesFor("right"));
		_animations[State::MoveRight]->setDurationAsSeconds(0.40f);

		_animations[State::MoveDown] = std::unique_ptr<Animation2>(new Animation2(false));
		_animations[State::MoveDown]->addFrameSet(frames.getFramesFor("down"));
		_animations[State::MoveDown]->setDurationAsSeconds(0.40f);

		_animations[State::MoveUp] = std::unique_ptr<Animation2>(new Animation2(false));
		_animations[State::MoveUp]->addFrameSet(frames.getFramesFor("up"));
		_animations[State::MoveUp]->setDurationAsSeconds(0.40f);

	}

	unsigned int Frog::getCategory() const
	{
		return Category::Frog;
	}

	void Frog::move(float x, float y, sf::Time dt)
	{
		// check with the value of x and y to know with side the frog is going and set the state to it.
		if (x == -40)
		{
			_directionMove = State::MoveLeft;
		}

		else if (x == 40)
		{
			_directionMove = State::MoveRight;
		}
		else if (y == -40)
		{
			_directionMove = State::MoveUp;
		}
		else if (y == 40)
		{
			_directionMove = State::MoveDown;
		}
		else
		{
			_directionMove = State::MoveIdel;
		}
		// start the animation on the correct side the frog move
		_animations[_directionMove]->start();
		sf::Vector2f tmp = _sprite.getPosition();
		_sprite.setPosition(tmp.x + x, tmp.y + y);
	}

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
		// draw the live the player have left in the top right conner.
		for (int i = 0; i < _lives; ++i)
		{
			sf::Vector2f tmp(460.f - i * 20.f, 20.f);
			_livesSprite.setPosition(tmp);
			target.draw(_livesSprite);
		}
	}

	void Frog::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		movementUpdate(dt);

		Entity::updateCurrent(dt, commands);
	}

	void Frog::movementUpdate(sf::Time dt)
	{
		// update the animation of the frog
		_sprite.setTextureRect(_animations[_directionMove]->update(dt));
	}
}