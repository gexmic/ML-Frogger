/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Lane node is where the car will be attache to

*/

#include "LaneNode.h"
#include "DataTables.h"
#include <time.h>
#include <stdlib.h>
#include "Vehicule.h"


namespace GEX
{
	const std::map<Vehicule::Type, LaneData> table = initializeLaneData();

	LaneNode::LaneNode(Vehicule::Type type) :
		_carType(type),
		_time(0)
	{
		// create a car at the start of the game 
		srand(time(NULL));
		std::unique_ptr<Vehicule> vehicule1(new Vehicule(_carType));
		vehicule1->setPosition(table.at(_carType).initialSpawn1);
		vehicule1->setVelocity(table.at(_carType).velocity);
		attachChild(std::move(vehicule1));
		// create another car in another possition
		std::unique_ptr<Vehicule> vehicule2(new Vehicule(_carType));
		vehicule2->setPosition(table.at(_carType).initialSpawn2);
		vehicule2->setVelocity(table.at(_carType).velocity);
		attachChild(std::move(vehicule2));

		initializeRandomTimeToSpan();

	}

	void LaneNode::updateCurrent(sf::Time deltaTime, CommandeQueue & commands)
	{	
		_time += deltaTime.asSeconds();

		if (_time >= _timeBeforSpanNewCar)
		{
			// if the time is gretar that the time for span create another car
			std::unique_ptr<Vehicule> vehicule(new Vehicule(_carType));
			vehicule->setPosition(table.at(_carType).spawnPosition);
			vehicule->setVelocity(table.at(_carType).velocity);	
			attachChild(std::move(vehicule));
			_time = 0;
			initializeRandomTimeToSpan();
		}			
	}

	unsigned int LaneNode::getCategory() const
	{
		return Category::Track;
	}

	void LaneNode::initializeRandomTimeToSpan()
	{
		// set ramdom time for the next car to spwan
		_timeBeforSpanNewCar = 4 +(rand() % (7 - 4 + 1));
	}
	
}


