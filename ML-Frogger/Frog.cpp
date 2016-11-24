#include "Frog.h"
#include "TextureHolder.h"
#include "Utility.h"

namespace GEX
{

	Frog::Frog() :
		_frogLocation(61, 1, 33, 23),
		_liveLocation(6, 1, 18,21),
		_sprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_livesSprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas)),
		_lives(5)		
	{		
		_sprite.setTextureRect(_frogLocation);
		centerOrigin(_sprite);

		_livesSprite.setTextureRect(_liveLocation);
		centerOrigin(_livesSprite);

	}

	unsigned int Frog::getCategory() const
	{
		return Category::Frog;
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
		Entity::updateCurrent(dt, commands);
	}	
}