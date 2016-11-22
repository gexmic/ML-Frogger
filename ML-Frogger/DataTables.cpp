/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

Data Tables class

*/

#include "DataTables.h"
#include "Projectile.h"
#include <functional>

namespace GEX
{
	Direction::Direction(float a, float b) : angle(a), distance(b)
	{}

	std::map<Airplaine::Type, AirplainDate> initializeAircraftDate()
	{
		std::map<Airplaine::Type, AirplainDate> data;

		data[Airplaine::Type::Eagle].hitpoint		= 100;
		data[Airplaine::Type::Eagle].speed			= 200.f;
		data[Airplaine::Type::Eagle].fireInterval	= sf::seconds(1);
		data[Airplaine::Type::Eagle].texture		= TextureID::Entity;
		data[Airplaine::Type::Eagle].location	= sf::IntRect(0, 0, 48,	64);
		///////////////////////////////
		data[Airplaine::Type::Raptor].hitpoint		= 20;
		data[Airplaine::Type::Raptor].fireInterval	= sf::seconds(2);
		data[Airplaine::Type::Raptor].speed			= 80.f;
		data[Airplaine::Type::Raptor].texture		= TextureID::Entity;
	    data[Airplaine::Type::Raptor].location = sf::IntRect(144, 0, 84, 64);

		data[Airplaine::Type::Raptor].direction.push_back(Direction(+80.f, 80.f));
		data[Airplaine::Type::Raptor].direction.push_back(Direction(-80.f, 160.f));
		data[Airplaine::Type::Raptor].direction.push_back(Direction(+80.f, 80.f));
		///////////////////////////////
		data[Airplaine::Type::Avenger].hitpoint		= 40;
		data[Airplaine::Type::Avenger].speed		= 50.f;
		data[Airplaine::Type::Avenger].fireInterval = sf::seconds(2);
		data[Airplaine::Type::Avenger].texture		= TextureID::Entity;
		data[Airplaine::Type::Avenger].location     = sf::IntRect(228, 0, 60, 59);

		data[Airplaine::Type::Avenger].direction.push_back(Direction(+70.f, 150.f));
		data[Airplaine::Type::Avenger].direction.push_back(Direction(0.f, 25.f));
		data[Airplaine::Type::Avenger].direction.push_back(Direction(-70.f, 300));
		data[Airplaine::Type::Avenger].direction.push_back(Direction(0.f, 25.f));
		data[Airplaine::Type::Avenger].direction.push_back(Direction(+70.f, 150.f));
		///////////////////////////////
		return data;
	}

	std::map<Projectile::Type, ProjectileDate> initializeProjectileDate()
	{
		std::map<Projectile::Type, ProjectileDate> data;

		data[Projectile::Type::AlliedBullet].damege		= 10;
		data[Projectile::Type::AlliedBullet].speed		= 300.f;
		data[Projectile::Type::AlliedBullet].texture	= TextureID::Entity;
		data[Projectile::Type::AlliedBullet].location   = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::EnemyBullet].damege		= 10;
		data[Projectile::Type::EnemyBullet].speed		= 300.f;
		data[Projectile::Type::EnemyBullet].texture		= TextureID::Entity;
		data[Projectile::Type::EnemyBullet].location    = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::Missile].damege			= 200;
		data[Projectile::Type::Missile].speed			= 300.f;
		data[Projectile::Type::Missile].approachRate    = 1000.f;
		data[Projectile::Type::Missile].texture			= TextureID::Entity;
		data[Projectile::Type::Missile].location        = sf::IntRect(160, 64, 15, 32);

		return data;
	}

	std::map<Pickup::Type, PickupDate> initializePickupDate()
	{
		std::map<Pickup::Type, PickupDate> data;

		data[Pickup::Type::HealtRifie].texture = TextureID::Entity;
		data[Pickup::Type::HealtRifie].action = [](Airplaine& a) {a.repair(25); };
		data[Pickup::Type::HealtRifie].location = sf::IntRect(0, 64, 40, 40);

		data[Pickup::Type::MissileRifle].texture = TextureID::Entity;
		data[Pickup::Type::MissileRifle].action = [](Airplaine& a) {a.collectMissiles(3); };
		data[Pickup::Type::MissileRifle].location = sf::IntRect(40, 64, 40, 40);

		data[Pickup::Type::FireSpred].texture = TextureID::Entity;
		data[Pickup::Type::FireSpred].action = [](Airplaine& a) {a.increaseSpread(); };
		data[Pickup::Type::FireSpred].location = sf::IntRect(80, 64, 40, 40);

		data[Pickup::Type::FireRart].texture = TextureID::Entity;
		data[Pickup::Type::FireRart].action = [](Airplaine& a) {a.increaseFireRate(); };
		data[Pickup::Type::FireRart].location = sf::IntRect(120, 64, 40, 40);

		// add the rest on type pickup and in application load the new texture

		return data;
	}

	std::map<Particule::Type, ParticuleData> initializeParticleData()
	{
		std::map<Particule::Type, ParticuleData> data;

		data[Particule::Type::Propellant].color = sf::Color(255, 111, 0);
		data[Particule::Type::Propellant].lifetime = sf::seconds(0.1f);

		data[Particule::Type::Smoke].color = sf::Color(64,64,64);
		data[Particule::Type::Smoke].lifetime = sf::seconds(0.5f);

		return data;
	}
}