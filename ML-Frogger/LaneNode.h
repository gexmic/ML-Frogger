/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Lane node is where the car will be attache to 

*/

#pragma once
#include "SceneNode.h"
#include "Vehicule.h"
#include <memory>

namespace GEX
{
	class Vehicule;

	class LaneNode : public SceneNode
	{
	public:
		typedef std::unique_ptr<Vehicule> Ptr;
	public:
		LaneNode(Vehicule::Type type);
		void											updateCurrent(sf::Time deltaTime, CommandeQueue& commands) override;
		unsigned int									getCategory() const override;

	private:
		void					initializeRandomTimeToSpan();
	private:
		sf::Vector2f			_spwanPosition;	
		Vehicule::Type			_carType;
		float					_time;
		int						_timeBeforSpanNewCar;
		int						_min;
		int						_max;		
	};
}
