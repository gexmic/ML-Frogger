#pragma once
#include "Entity.h"
#include "SFML\Window.hpp"
#include "TextureHolder.h"


namespace GEX
{
	class Airplaine;
	class Pickup : public Entity
	{
	public:
		enum  Type
		{
			HealtRifie,
			MissileRifle,
			FireSpred,
			FireRart,
			TypeCount
		};

	public:
							Pickup(Type type);
		unsigned int		getCategory() const override;
		void				apply(Airplaine& player) const;

	private:

		void						drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		sf::FloatRect				getBoundingRect() const;

	private:
		Type				_type;
		sf::Sprite			_sprite;
	};

}
