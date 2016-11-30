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
		data[Vehicule::Type::RaceCar1].velocity				= sf::Vector2f(-40.f, 0.f);
		data[Vehicule::Type::RaceCar1].spawnPosition        = sf::Vector2f(520, 540);
		data[Vehicule::Type::RaceCar1].destroyPoint			= -20.f;

		data[Vehicule::Type::Tracktor].texture				= TextureID::FroggerAtlas;
		data[Vehicule::Type::Tracktor].vehiculeLocation		= sf::IntRect(214, 62, 33,  33);
		data[Vehicule::Type::Tracktor].velocity				= sf::Vector2f(50.f, 0.f);
		data[Vehicule::Type::Tracktor].spawnPosition		= sf::Vector2f(-20, 500);
		data[Vehicule::Type::Tracktor].destroyPoint			= 520.f;

		data[Vehicule::Type::Car].texture					= TextureID::FroggerAtlas;
		data[Vehicule::Type::Car].vehiculeLocation			= sf::IntRect(1, 62, 35, 29);
		data[Vehicule::Type::Car].velocity					= sf::Vector2f(-40.f, 0.f);
		data[Vehicule::Type::Car].spawnPosition				= sf::Vector2f(520, 460);
		data[Vehicule::Type::Car].destroyPoint				= -20.f;

		data[Vehicule::Type::RaceCar2].texture				= TextureID::FroggerAtlas;
		data[Vehicule::Type::RaceCar2].vehiculeLocation		= sf::IntRect(69, 100, 37, 37);
		data[Vehicule::Type::RaceCar2].velocity				= sf::Vector2f(55.f, 0.f);
		data[Vehicule::Type::RaceCar2].spawnPosition		= sf::Vector2f(-20, 420);
		data[Vehicule::Type::RaceCar2].destroyPoint			= 520.f;

		data[Vehicule::Type::Truck].texture					= TextureID::FroggerAtlas;
		data[Vehicule::Type::Truck].vehiculeLocation		= sf::IntRect(293, 1, 61, 28);
		data[Vehicule::Type::Truck].velocity				= sf::Vector2f(-40.f, 0.f);
		data[Vehicule::Type::Truck].spawnPosition			= sf::Vector2f(520, 380);
		data[Vehicule::Type::Truck].destroyPoint			= -40.f;

		return data;
	}
}