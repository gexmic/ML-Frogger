#pragma once
#include "SceneNode.h"
#include "Vehicule.h"

namespace GEX
{
	class Vehicule;

	class LaneNode : public SceneNode
	{
	public:
		LaneNode(Vehicule::Type type);
		void					updateCurrent(sf::Time deltaTime, CommandeQueue& commands) override;

	private:
		void					initializeRandomTimeToSpan();
	private:
		sf::Vector2f			_spwanPosition;		
		int						_carToSpan;
		Vehicule::Type			_carType;
		Vehicule*				_car;
		float					_time;
		int						_timeBeforSpanNewCar;
		int						_min;
		int						_max;
		
		
	};
}

