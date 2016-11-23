#include "Frog.h"
#include "TextureHolder.h"
#include "Utility.h"

namespace GEX
{

	Frog::Frog() :
		_location(61, 1, 33, 23),
		_sprite(TextureHolder::getInstance().get(TextureID::FroggerAtlas))
		
	{
		
		_sprite.setTextureRect(_location);
		centerOrigin(_sprite);
		sf::FloatRect tmp = _sprite.getLocalBounds();
		sf::Vector2f tmpPos = _sprite.getPosition();
	}

	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Frog::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		Entity::updateCurrent(dt, commands);
	}


	
}