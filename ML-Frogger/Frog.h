#pragma once
#include "Entity.h"
#include <vector>
#include "Animation2.h"
namespace GEX
{
	class Frog : public Entity
	{
		enum State {
			MoveIdel,
			MoveRight,
			MoveLeft,
			MoveUp,
			MoveDown
		};
	public:
		Frog();
		unsigned int		getCategory() const override;
		void				move(float x, float y, sf::Time dt);

	private:
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		virtual void        updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void				movementUpdate(sf::Time dt);
	private:		
		sf::Sprite			_sprite;
		State				_directionMove;
		mutable sf::Sprite	_livesSprite;
		sf::IntRect			_frogLocation;
		sf::IntRect			_liveLocation;
		int					_lives;
		std::map<State, std::unique_ptr<Animation2>>	_animations;
	};
}

