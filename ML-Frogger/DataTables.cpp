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

	std::map<Lane::Type, LaneData> initializeLaneData()
	{
		std::map<Lane::Type, LaneData> data;

		data[Lane::Type::RaceCar1].texture = TextureID::FroggerAtlas;
		data[Lane::Type::RaceCar1].vehiculeLocation = sf::IntRect(139, 100, 38, 39);
		data[Lane::Type::RaceCar1].speed = -40.f;
		data[Lane::Type::RaceCar1].spawnPosition = sf::Vector2f(460.f, 580.f);
		data[Lane::Type::RaceCar1].direction.push_back(Direction(40.f, 0.f));

		return data;
	}
}