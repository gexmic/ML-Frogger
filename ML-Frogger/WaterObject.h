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

