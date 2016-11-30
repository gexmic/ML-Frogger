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
		std::cout << "Car Destroyd" << std::endl;
	}



	void Vehicule::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}



	void Vehicule::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		Entity::updateCurrent(dt, commands);
	}
}
