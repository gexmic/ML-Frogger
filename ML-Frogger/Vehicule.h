#pragma once
#include "Entity.h"

namespace GEX
{

	class Vehicule : public Entity
	{
	public:
		enum Type
		{
			RaceCar1,
			RaceCar2,
			Car,
			Truck,
			Tracktor
		};
	public:
		Vehicule(Type type);
		~Vehicule();

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

