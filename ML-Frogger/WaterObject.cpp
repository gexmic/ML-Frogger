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

	void WaterObject::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		if (getPosition().x <= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x > 480)
			destroy();
		if (getPosition().x >= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x < 0)
			destroy();
		Entity::updateCurrent(dt, commands);
	}
}
