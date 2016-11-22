/**
@file Aorcraft.cpp
@author  Michael Landry <mic_23@hotmail.com>
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt
These additions and modifications are my sole work for prog 1266

@section DESCRIPTION


*/
#include "Airplaine.h"
#include "Category.h"
#include "TextNode.h"
#include "DataTables.h"
#include "Utility.h"
#include <memory>
#include "SoundNode.h"
#include "SoundPlayer.h"

namespace GEX
{
	const std::map<Airplaine::Type, AirplainDate> table = initializeAircraftDate();

	Airplaine::Airplaine(Type type) :
		Entity(table.at(type).hitpoint),
		_type(type),
		_sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).location),
		_explosion(TextureHolder::getInstance().get(TextureID::Explosion)),
		_directionIndex(0),
		_travelDistance(0),
		_missileAmmo(8),
		_fireRateLevel(1),
		_spreadLevel(1),
		_isMarkedForRemoval(false),
		_playedExplosionSound(false),
		_showExplosion(true),
		_spawnedPickup(false)
	{
		centerOrigin(_sprite);

		_explosion.setFrameSize(sf::Vector2i(256, 256));
		_explosion.setNumFrames(16);
		_explosion.setDuration(sf::seconds(1));
		centerOrigin(_explosion);

		_fireCommand.category = Category::SceneAirLayer;
		_fireCommand.action = [this](SceneNode& node, sf::Time)
		{
			this->createBullets(node);
		};

		_launchMissileCommand.category = Category::SceneAirLayer;
		_launchMissileCommand.action = [this](SceneNode& node, sf::Time)
		{
			this->createProjectile(node, Projectile::Type::Missile, 0.f, 0.5f);
		};

		std::unique_ptr<TextNode> healthDisplay(new TextNode(std::to_string(getHitPoint()) + "HP "));
		_healthDisplay = healthDisplay.get();
		healthDisplay->setPosition(0.f, 50.f);
		attachChild(std::move(healthDisplay));

		_dropPickupCommand.category = Category::SceneAirLayer;
		_dropPickupCommand.action = [this](SceneNode& node, sf::Time)
		{
			createPickup(node);
		};
	}

	unsigned int Airplaine::getCategory() const
	{
		switch (_type)
		{
		case Type::Eagle:
			return Category::PlayerAircraft;
		case Type::Raptor:
			return Category::EnnemyAircraft;
		case Type::Avenger:
			return Category::EnnemyAircraft;
		default:
			assert(0);
			return Category::None;
		}

	}

	float Airplaine::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	void Airplaine::fire()
	{
		if (table.at(_type).fireInterval != sf::Time::Zero)
			_isFiring = true;
	}

	void Airplaine::launchMissile()
	{
		if (_missileAmmo > 0)
		{
			_isLaunchingMissile = true;
			--_missileAmmo;
		}
	}

	sf::FloatRect Airplaine::getBoundingRect() const
	{
		return getWorldTransform().transformRect(_sprite.getGlobalBounds());
	}

	bool Airplaine::isAllied() const
	{
		return _type == Airplaine::Type::Eagle;
	}

	void Airplaine::increaseSpread()
	{
		if (_spreadLevel < 3)
			++_spreadLevel;
	}

	void Airplaine::increaseFireRate()
	{
		if (_fireRateLevel < 10)
			++_fireRateLevel;
	}

	void Airplaine::collectMissiles(unsigned int count)
	{
		_missileAmmo += count;
	}

	bool Airplaine::isMarkedForRemoval() const
	{
		return isDestroyed() && (_explosion.isFinished() || !_showExplosion);
	}

	void Airplaine::playLocalSound(CommandeQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPosition = getWorldPosition();

		Command command;
		command.category = Category::SoundEffet;
		command.action = derivedAction<SoundNode>([effect, worldPosition](SoundNode& node, sf::Time) 
		{node.playSound(effect, worldPosition); });
		commands.push(command);
	}



	void Airplaine::updateCurrent(sf::Time dt, CommandeQueue& commands)
	{
		// adjust speed if on diag
		sf::Vector2f velocity = getVelocity();
		if (velocity.x != 0.f && velocity.y != 0.f)
			setVelocity(velocity / std::sqrt(2.f));

		if (isDestroyed())
		{
			_explosion.update(dt);
			//_isMarkedForRemoval = true;
			updateTexts();
			if (!_playedExplosionSound)
			{
				SoundEffectID soundEffect = (randomInt(2) == 0) ? SoundEffectID::Explosion1 : SoundEffectID::Explosion2;
				playLocalSound(commands, soundEffect);
				_playedExplosionSound = true;
				checkPickupDrop(commands);
			}
			return;
		}

		updateTexts();
		checkProjectileLaunch(dt, commands);


		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);  // call Entity base class method
	}

	void Airplaine::updateTexts()
	{
		_healthDisplay->setText(std::to_string(getHitPoint()) + " HP");
		_healthDisplay->setPosition(0.f, 50.f);
		_healthDisplay->setRotation(-getRotation());
	}

	void Airplaine::createBullets(SceneNode & node) const
	{
		Projectile::Type type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;

		switch (_spreadLevel)
		{
		case 1:
			createProjectile(node, type, 0, 0.5f);
			break;

		case 2:
			createProjectile(node, type, -0.33f, 0.33f);
			createProjectile(node, type, 0.33f, 0.33f);
			break;

		case 3:
			createProjectile(node, type, -0.5f, 0.33f);
			createProjectile(node, type, 0, 0.5f);
			createProjectile(node, type, 0.5f, 0.33f);
			break;
		}

	}

	void Airplaine::createProjectile(SceneNode & node, Projectile::Type type, float xOffSet, float yOffSet) const
	{
		// node is the ScreenAirLayer node that the command was targeted to
		std::unique_ptr<Projectile> projectile(new Projectile(type));

		sf::Vector2f offset(xOffSet * _sprite.getGlobalBounds().width, yOffSet + _sprite.getGlobalBounds().height);
		sf::Vector2f velocity(0, projectile->getMaxSpeed());
		float sign = isAllied() ? -1.f : 1;
		projectile->setPosition(getWorldPosition() + offset * sign);
		projectile->setVelocity(velocity * sign);
		node.attachChild(std::move(projectile));
	}

	void Airplaine::checkProjectileLaunch(sf::Time dt, CommandeQueue & commands)
	{
		if (!isAllied())
			fire();


		// automatic gun fire
		if (_isFiring && _fireCountdown <= sf::Time::Zero)
		{
			commands.push(_fireCommand);
			playLocalSound(commands, isAllied() ? SoundEffectID::AlliedGunFire : SoundEffectID::EnemyGunFire);
			_isFiring = false;
			_fireCountdown += table.at(_type).fireInterval / (_fireRateLevel + 1.f);
		}
		else if (_fireCountdown > sf::Time::Zero)
		{
			_fireCountdown -= dt;
			_isFiring = false;
		}

		if (_isLaunchingMissile)
		{
			commands.push(_launchMissileCommand);
			playLocalSound(commands, SoundEffectID::LauchMissile);
			_isLaunchingMissile = false;
		}
	}

	void Airplaine::checkPickupDrop(CommandeQueue & commands)
	{
		if (Category::EnnemyAircraft)
		{
			commands.push(_dropPickupCommand);
			_spawnedPickup = false;
			if (randomInt(3) == 1)
				_spawnedPickup = true;
		}
	}

	void Airplaine::createPickup(SceneNode & node) const
	{
		if (_spawnedPickup)
		{
			//int num = randomInt(int(Pickup::Type::typeCount));
			//auto type = Pickup::Type(num);
			std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type(randomInt(int(Pickup::Type::TypeCount)))));
			pickup->setPosition(getWorldPosition());
			node.attachChild(std::move(pickup));
		}
	}

	void Airplaine::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		if (isDestroyed() && _showExplosion)
			target.draw(_explosion, state);
		else
			target.draw(_sprite, state);
	}

	void Airplaine::movementUpdate(sf::Time dt)
	{
		const std::vector<Direction>& directions = table.at(_type).direction;
		if (!directions.empty())
		{
			float distanceToTravel = directions.at(_directionIndex).distance;
			if (_travelDistance > distanceToTravel)
			{
				_directionIndex = (_directionIndex + 1) % directions.size();
				_travelDistance = 0;
			}
			_travelDistance += getMaxSpeed() * dt.asSeconds();
			float dirAngle = directions.at(_directionIndex).angle + 90.f;
			float vx = getMaxSpeed() * GEX::cos(dirAngle);
			float vy = getMaxSpeed() * GEX::sin(dirAngle);
			setVelocity(vx, vy);
		}
	}
}