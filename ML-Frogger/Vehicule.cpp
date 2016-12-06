#include "Vehicule.h"
#include "TextureHolder.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>


namespace GEX
{
	const std::map<Vehicule::Type, LaneData> table = initializeLaneData();

	Vehicule::Vehicule(Type type) :
		Entity(),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).vehiculeLocation)


	{
		centerOrigin(_sprite);
	}

	Vehicule::~Vehicule()
	{
		std::cout << "Car Destroyd " << _type << std::endl;
	}



	void Vehicule::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	sf::FloatRect Vehicule::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	unsigned int Vehicule::getCategory() const
	{
		return Category::Track;
	}



	void Vehicule::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{		
		if (getPosition().x <= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x > 480)
			destroy();
		if (getPosition().x >= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x < 0)
			destroy();
		Entity::updateCurrent(dt, commands);
	}
}
