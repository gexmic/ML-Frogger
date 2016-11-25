#include "Frog.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "JsonFrameParser.hpp"

namespace GEX
{


	Frog::Frog() :
		_frogLocation(61, 1, 33, 23),
		_liveLocation(6, 1, 18, 21),
		_sprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_livesSprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_lives(3)
	{
		_sprite.setTextureRect(_frogLocation);
		centerOrigin(_sprite);

		_livesSprite.setTextureRect(_liveLocation);
		centerOrigin(_livesSprite);

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
		if (x == -40)
		{
			_directionMove = State::MoveLeft;
			_animations[_directionMove]->start();
		}

		else if (x == 40)
		{
			_directionMove = State::MoveRight;
			_animations[_directionMove]->start();
		}
		else if (y == -40)
		{
			_directionMove = State::MoveUp;
			_animations[_directionMove]->start();
		}
		else if (y == 40)
		{
			_directionMove = State::MoveDown;
			_animations[_directionMove]->start();
		}
		else
			_directionMove = State::MoveIdel;
	}

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
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
		_sprite.setTextureRect(_animations[_directionMove]->update(dt));

	}
}