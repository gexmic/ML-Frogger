#pragma once
#include "Entity.h"
namespace GEX
{
	class Frog : public Entity
	{
	public:
		Frog();

	private:
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		virtual void        updateCurrent(sf::Time dt, CommandeQueue& commands) override;

	private:
		sf::Sprite			_sprite;
		sf::IntRect			_location;

	};
}

