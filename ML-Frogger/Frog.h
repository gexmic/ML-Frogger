#pragma once
#include "Entity.h"
#include <vector>
namespace GEX
{
	class Frog : public Entity
	{
	public:
		Frog();
		int getNumberOfLives();


	private:
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		virtual void        updateCurrent(sf::Time dt, CommandeQueue& commands) override;

	private:
		sf::Sprite			_sprite;
		sf::Sprite			_livesSprite;
		sf::IntRect			_frogLocation;
		sf::IntRect			_liveLocation;
		int					_lives;
		
	};
}

