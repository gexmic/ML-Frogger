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

	int Frog::getNumberOfLives()
	{
		return _lives;
	}

	/*for (int = 0; i < live : ++i)
	{
		_liveSprite->setposition(460 - (i * 20), 20);
		_window.draw(_liveSprite);
	}*/

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);	}

	void drawLive()
	{

	}

	void Frog::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		Entity::updateCurrent(dt, commands);
	}


	
}