#include "Lane.h"
#include "TextureHolder.h"
#include "DataTables.h"
#include "Utility.h"


namespace GEX
{
	const std::map<Lane::Type, LaneData> table = initializeLaneData();
	Lane::Lane(Type type) :
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).vehiculeLocation),
		_speedTravel(table.at(type).speed),
		_spawnPosition(table.at(type).spawnPosition)
	{
		centerOrigin(_sprite);
	}

	float Lane::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	void Lane::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}

	void Lane::movementUpdate(sf::Time dt)
	{
		const std::vector<Direction>& directions = table.at(_type).direction;

		float distanceToTravel = directions.at(_directionIndex).distance;
		float vx = getMaxSpeed() * GEX::cos(distanceToTravel);
		float vy = getMaxSpeed() * GEX::sin(distanceToTravel);
		setVelocity(vx, vy);
	}

	void Lane::updateCurrent(sf::Time dt, CommandeQueue & commands)
	{
		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

}