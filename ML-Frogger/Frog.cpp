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
#include "DataTables.h"
#include "LaneNode.h"
#include "FontHolder.h"

namespace GEX
{
	const std::map<Frog::Type, FrogData> table = initializeFrogData();
	Frog::Frog(Type type) :
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).frogLocation),
		_livesSprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).liveLocation),
		_lives(3),
		_score(0),
		_lastHigherPosition(580)
	{
		centerOrigin(_sprite);
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
		if (x <= -40)
		{
			_directionMove = State::MoveLeft;
		}

		else if (x >= 40)
		{
			_directionMove = State::MoveRight;
		}
		else if (y <= -40)
		{
			_directionMove = State::MoveUp;
		}
		else if (y >= 40)
		{
			_directionMove = State::MoveDown;
		}
		else
		{
			_directionMove = State::MoveIdel;
		}
		// start the animation on the correct side the frog move
		_animations[_directionMove]->start();
		sf::Vector2f tmp = this->getPosition();
		this->setPosition(tmp.x + x, tmp.y + y);
	}

	sf::FloatRect Frog::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	void Frog::handelColision()
	{
		/*Command command;
		command.category = Category::Track;
		command.action = derivedAction<Entity>( [this](SceneNode& e, sf::Time)
		{
			if (e.getBoundingRect().intersects(this->getBoundingRect()))
				_hitByCar = true;
		});

		_commandQueue.push(command);*/
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
		target.draw(_scoreText);
	}

	void Frog::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		/*if (_hitByCar)
		{
			this->setPosition(240, 580);
		}*/
		movementUpdate(dt);
		calculateScore();
		updateScore();
		Entity::updateCurrent(dt, commands);
	}

	void Frog::movementUpdate(sf::Time dt)
	{
		// update the animation of the frog
		_sprite.setTextureRect(_animations[_directionMove]->update(dt));
	}
	void Frog::calculateScore()
	{
		if (_lastHigherPosition > getPosition().y)
		{
			_lastHigherPosition = getPosition().y;
			_score += 20;
		}
			
	}

	void Frog::updateScore()
	{
		_scoreText.setString("score: " + std::to_string(_score));
		_scoreText.setFont(FontHolder::getInstance().get(FontID::Main));
		_scoreText.setCharacterSize(20);
		centerOrigin(_scoreText);
		_scoreText.setPosition(50.f, 20.f);
	}


}