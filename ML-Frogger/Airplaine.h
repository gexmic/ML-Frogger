/**
@file Airplaine.h
@author  Michael Landry <mic_23@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include "Command.h"
#include "Projectile.h"
#include "CommandeQueue.h"
#include "Animation.h"
#include "Pickup.h"

namespace GEX
{
	class TextNode;
	class Airplaine : public Entity
	{
	public:
		enum Type {
			Raptor,
			Eagle,
			Avenger
		};

		Airplaine(Type type = Type::Eagle);
		unsigned int		getCategory() const override;
		float				getMaxSpeed() const;
		void				fire();
		void				launchMissile();
		sf::FloatRect		getBoundingRect() const override;
		bool				isAllied() const;
		void				increaseSpread();
		void				increaseFireRate();
		void				collectMissiles(unsigned int count);
		virtual bool		isMarkedForRemoval() const override;
		void				playLocalSound(CommandeQueue& command, SoundEffectID effect);


	private:
		void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const override;
		void				movementUpdate(sf::Time dt);
		virtual void        updateCurrent(sf::Time dt, CommandeQueue& commands) override;
		void				updateTexts();
		void				createBullets(SceneNode& node) const;
		void				createProjectile(SceneNode& node, Projectile::Type type, float xOffSet, float yOffSet) const;
		void				checkProjectileLaunch(sf::Time dt, CommandeQueue& commands);
		void				checkPickupDrop(CommandeQueue& commands);
		void				createPickup(SceneNode& node) const;

	private:
		Type				_type;
		sf::Sprite			_sprite;
		TextNode*			_healthDisplay;
		int					_directionIndex;
		float				_travelDistance;
		Command				_fireCommand;
		Command				_launchMissileCommand;
		std::size_t			_missileAmmo;
		std::size_t			_fireRateLevel;
		std::size_t			_spreadLevel;
		bool				_isFiring;
		bool				_isLaunchingMissile;
		bool				_showExplosion;
		bool				_playedExplosionSound;
		sf::Time			_fireCountdown;
		bool				_isMarkedForRemoval;
		Animation			_explosion;
		Command				_dropPickupCommand;
		bool				_spawnedPickup;

	};
}