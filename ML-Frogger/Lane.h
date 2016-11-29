#pragma once
#include "Entity.h"

namespace GEX
{

	class Lane : public Entity
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
							Lane(Type type);
		float				getMaxSpeed() const;

	private:
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		void				movementUpdate(sf::Time dt);
		virtual void		updateCurrent(sf::Time dt, CommandeQueue& commands) override;

	private:
		Type				_type;
		float				_speedTravel;
		sf::Sprite			_sprite;
		sf::Vector2f		_spawnPosition;
		int					_directionIndex;
	};

}
