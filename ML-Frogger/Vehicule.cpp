/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

create the vehicul to be spwan in the lane node

*/

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
		// for debug see in the consol if the car are destroyd
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
		// check if the vehicule are outside the view and if yes destroy then
		if (getPosition().x <= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x > 480)
			destroy();
		if (getPosition().x >= table.at(_type).destroyPoint.x && table.at(_type).spawnPosition.x < 0)
			destroy();
		Entity::updateCurrent(dt, commands);
	}
}
