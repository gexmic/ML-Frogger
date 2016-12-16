/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

this dataTable class have a table for the frog attributes wen a frog is construct it get the information on the table 
The information for the car and the water object it also there

*/

#pragma once
#include "ResourceIdentifiers.h"
#include <map>
#include <vector>
#include "Frog.h"
#include "Vehicule.h"
#include "WaterObject.h"

namespace GEX
{


	struct Direction
	{
		Direction		(float a, float b);
		float			angle;
		float			distance;

	};	

	struct  FrogData
	{
		int				jump;
		TextureID		texture;
		sf::IntRect		frogLocation;
		sf::IntRect		liveLocation;
	};

	struct  LaneData
	{
		TextureID				texture;
		sf::IntRect				vehiculeLocation;
		sf::Vector2f			velocity;
		sf::Vector2f			spawnPosition;
		sf::Vector2f			initialSpawn1;
		sf::Vector2f			initialSpawn2;
		sf::Vector2f			destroyPoint;

	};

	struct WaterData
	{
		TextureID				texture;
		sf::IntRect				Location;
		sf::Vector2f			velocity;
		sf::Vector2f			spawnPosition;
		sf::Vector2f			initialSpawn1;
		sf::Vector2f			initialSpawn2;
		sf::Vector2f			destroyPoint;
	};

	std::map<Frog::Type, FrogData> initializeFrogData();
	std::map<Vehicule::Type, LaneData> initializeLaneData();
	std::map<WaterObject::Type, WaterData> initializeWaterData();

}