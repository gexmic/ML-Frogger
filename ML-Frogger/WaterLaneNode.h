/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

manage the creation of water object 

*/

#pragma once
#include "SceneNode.h"
#include "WaterObject.h"

namespace GEX
{
	class WaterObject;

	class WaterLaneNode : public SceneNode
	{
	public:
								WaterLaneNode(WaterObject::Type type);
		void					updateCurrent(sf::Time deltaTime, CommandeQueue& commands) override;
		unsigned int									getCategory() const override;

	private:
		void					initializeRandomTimeToSpan();
	private:
		sf::Vector2f			_spwanPosition;
		WaterObject::Type		_type;
		float					_time;
		int						_timeBeforSpanNewCar;
		int						_min;
		int						_max;
	};
}

