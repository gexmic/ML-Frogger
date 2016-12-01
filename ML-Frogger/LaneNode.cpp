#include "LaneNode.h"
#include "DataTables.h"
#include <time.h>
#include <stdlib.h>


namespace GEX
{
	const std::map<Vehicule::Type, LaneData> table = initializeLaneData();

	LaneNode::LaneNode(Vehicule::Type type) :
		_carType(type),
		_time(0)
	{
		srand(time(NULL));
		std::unique_ptr<Vehicule> vehicule1(new Vehicule(_carType));
		vehicule1->setPosition(table.at(_carType).initialSpawn1);
		vehicule1->setVelocity(table.at(_carType).velocity);
		attachChild(std::move(vehicule1));

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
			std::unique_ptr<Vehicule> vehicule(new Vehicule(_carType));
			vehicule->setPosition(table.at(_carType).spawnPosition);
			vehicule->setVelocity(table.at(_carType).velocity);
			attachChild(std::move(vehicule));
			_time = 0;
			initializeRandomTimeToSpan();
		}	

		
	}

	void LaneNode::initializeRandomTimeToSpan()
	{
		_timeBeforSpanNewCar = 3 +(rand() % (6 - 3 + 1));
	}
	
}


