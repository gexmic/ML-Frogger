/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Data Tables class

*/

#include "DataTables.h"
#include <functional>

namespace GEX
{
	Direction::Direction(float a, float b) : angle(a), distance(b)
	{}	

	std::map<Frog::Type, FrogData> initializeFrogData()
	{
		std::map<Frog::Type, FrogData> data;

		data[Frog::Type::Frogger].jump = 40;
		data[Frog::Type::Frogger].texture = TextureID::FroggerAtlas;
		data[Frog::Type::Frogger].frogLocation = sf::IntRect(61, 1, 33, 23);
		data[Frog::Type::Frogger].liveLocation = sf::IntRect(6, 1, 18, 21);

		return data;
	}

	std::map<Vehicule::Type, LaneData> initializeLaneData()
	{
		std::map<Vehicule::Type, LaneData> data;

		data[Vehicule::Type::RaceCar1].texture				= TextureID::FroggerAtlas;
		data[Vehicule::Type::RaceCar1].vehiculeLocation		= sf::IntRect(139, 100, 38, 39);
		data[Vehicule::Type::RaceCar1].velocity				= sf::Vector2f(-30.f, 0.f);
		data[Vehicule::Type::RaceCar1].spawnPosition        = sf::Vector2f(500.f, 540.f);
		data[Vehicule::Type::RaceCar1].initialSpawn1		= sf::Vector2f(460.f, 540.f);
		data[Vehicule::Type::RaceCar1].initialSpawn2		= sf::Vector2f(240.f, 540.f);
		data[Vehicule::Type::RaceCar1].destroyPoint			= sf::Vector2f(-20.f, 540.f);

		data[Vehicule::Type::Tracktor].texture				= TextureID::FroggerAtlas;
		data[Vehicule::Type::Tracktor].vehiculeLocation		= sf::IntRect(214, 62, 33,  33);
		data[Vehicule::Type::Tracktor].velocity				= sf::Vector2f(50.f, 0.f);
		data[Vehicule::Type::Tracktor].spawnPosition		= sf::Vector2f(-20.f, 500.f);
		data[Vehicule::Type::Tracktor].initialSpawn1		= sf::Vector2f(150.f, 500.f);
		data[Vehicule::Type::Tracktor].initialSpawn2		= sf::Vector2f(330.f, 500.f);
		data[Vehicule::Type::Tracktor].destroyPoint			= sf::Vector2f(520.f, 500.f);

		data[Vehicule::Type::Car].texture					= TextureID::FroggerAtlas;
		data[Vehicule::Type::Car].vehiculeLocation			= sf::IntRect(1, 62, 35, 29);
		data[Vehicule::Type::Car].velocity					= sf::Vector2f(-25.f, 0.f);
		data[Vehicule::Type::Car].spawnPosition				= sf::Vector2f(500.f, 460.f);
		data[Vehicule::Type::Car].initialSpawn1				= sf::Vector2f(264.f, 460.f);
		data[Vehicule::Type::Car].initialSpawn2				= sf::Vector2f(95.f, 460.f);
		data[Vehicule::Type::Car].destroyPoint				= sf::Vector2f(-20.f, 460.f);

		data[Vehicule::Type::RaceCar2].texture				= TextureID::FroggerAtlas;
		data[Vehicule::Type::RaceCar2].vehiculeLocation		= sf::IntRect(69, 100, 37, 37);
		data[Vehicule::Type::RaceCar2].velocity				= sf::Vector2f(60.f, 0.f);
		data[Vehicule::Type::RaceCar2].spawnPosition		= sf::Vector2f(-20, 420);
		data[Vehicule::Type::RaceCar2].initialSpawn1		= sf::Vector2f(355.f, 420.f);
		data[Vehicule::Type::RaceCar2].initialSpawn1		= sf::Vector2f(128.f, 420.f);
		data[Vehicule::Type::RaceCar2].destroyPoint			= sf::Vector2f(520.f, 420);

		data[Vehicule::Type::Truck].texture					= TextureID::FroggerAtlas;
		data[Vehicule::Type::Truck].vehiculeLocation		= sf::IntRect(293, 1, 61, 28);
		data[Vehicule::Type::Truck].velocity				= sf::Vector2f(-70.f, 0.f);
		data[Vehicule::Type::Truck].spawnPosition			= sf::Vector2f(500.f, 380.f);
		data[Vehicule::Type::Truck].initialSpawn1			= sf::Vector2f(290.f, 380.f);
		data[Vehicule::Type::Truck].initialSpawn1			= sf::Vector2f(60.f, 380.f);
		data[Vehicule::Type::Truck].destroyPoint			= sf::Vector2f(-40.f, 380.f);

		return data;
	}
}