/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

create the water object depend of the type

*/

#pragma once
#include "Entity.h"

namespace GEX
{

	class WaterObject : public Entity
	{
	public:
		enum Type
		{
			Turtle2,
			Turtle3,
			Log3,
			Log4,
			Log5
		};
	public:
		WaterObject(Type type);
		~WaterObject();

		void drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const;
		sf::FloatRect									getBoundingRect() const override;
		unsigned int									getCategory() const override;

	private:
		virtual void		updateCurrent(sf::Time dt, CommandeQueue& commands) override;

	private:
		Type				_type;
		sf::Sprite			_sprite;

	};

}

