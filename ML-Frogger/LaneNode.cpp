#include "LaneNode.h"
#include "DataTables.h"
#include <time.h>
#include <stdlib.h>


namespace GEX
{
	const std::map<Vehicule::Type, LaneData> table = initializeLaneData();

	LaneNode::LaneNode(Vehicule::Type type) :
		_carType(type),
		_carToSpan(1),
		_time(0)
	{
		srand(time(NULL));
		initializeRandomTimeToSpan();
	}

	void LaneNode::updateCurrent(sf::Time deltaTime, CommandeQueue & commands)
	{	
		_time += deltaTime.asSeconds();

		if (_time >= 5)
		{
			std::unique_ptr<Vehicule> vehicule(new Vehicule(_carType));
			_car = vehicule.get();
			vehicule->setPosition(table.at(_carType).spawnPosition);
			vehicule->setVelocity(table.at(_carType).velocity);
			attachChild(std::move(vehicule));
			_time == 0;
			initializeRandomTimeToSpan();
		}	

		if (_car != NULL)
		{

			if (_car->getPosition().x <= table.at(_carType).destroyPoint && table.at(_carType).spawnPosition.x > 480)
				_car->destroy();

			if (_car->getPosition().x >= table.at(_carType).destroyPoint && table.at(_carType).spawnPosition.x < 0)
				_car->destroy();
		}
	}

	void LaneNode::initializeRandomTimeToSpan()
	{
		_timeBeforSpanNewCar = rand() % (6 + 1 - 4) + 4;
	}
	
}
//(rand() % (max + 1 - min)) + min

