/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Frog class manage the direction the frog whil move, animation and the sprite of the frog and the life left.

*/

#pragma once
#include "Entity.h"
#include <vector>
#include "Animation2.h"
namespace GEX
{
	class Frog : public Entity
	{
	public:
		enum Type
		{
			Frogger
		};
		enum State {
			MoveIdel,
			MoveRight,
			MoveLeft,
			MoveUp,
			MoveDown
		};
	public:
		Frog(Type type = Type::Frogger);
		unsigned int									getCategory() const override;
		void											move(float x, float y, sf::Time dt);
		sf::FloatRect									getBoundingRect() const override;
		void											handelColision();

	private:
		void											drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		virtual void									updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void											movementUpdate(sf::Time dt);

	private:		
		sf::Sprite										_sprite;
		State											_directionMove;
		mutable sf::Sprite								_livesSprite;
		sf::IntRect										_frogLocation;
		sf::IntRect										_liveLocation;
		int												_lives;
		std::map<State, std::unique_ptr<Animation2>>	_animations;
		bool											_hitByCar;
		CommandeQueue									_commandQueue;
	};
}

