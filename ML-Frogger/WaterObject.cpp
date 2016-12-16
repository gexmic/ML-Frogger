/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

create the water object depend of the type

*/

#include "WaterObject.h"
#include "DataTables.h"
#include "TextureHolder.h"
#include "Utility.h"
#include <iostream>


namespace GEX
{
	const std::map<WaterObject::Type, WaterData> table = initializeWaterData();

	WaterObject::WaterObject(Type type) :
		Entity(),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).Location)
	{
		centerOrigin(_sprite);
	}

	WaterObject::~WaterObject()
	{
		std::cout << "water Destroyd " << _type << std::endl;
	}

	void WaterObject::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	sf::FloatRect WaterObject::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());;
	}

	unsigned int WaterObject::getCategory() const
	{
		return Category::Water;
	}

	void WaterObject::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{

		// check if the object is outside the view of the game and if yes destroy
		if (getPosition().x <= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x > 480)
			destroy();
		if (getPosition().x >= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x < 0)
			destroy();
		Entity::updateCurrent(dt, commands);
	}
}
