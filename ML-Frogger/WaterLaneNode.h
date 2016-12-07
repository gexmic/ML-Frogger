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

