/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

this dataTable class have a table for the future frog attributes wen a frog is construct it get the information on the table 

*/

#pragma once
#include "ResourceIdentifiers.h"
#include <map>
#include <vector>
#include "Frog.h"
#include "Lane.h"

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
		float					speed;
		sf::Vector2f			spawnPosition;
		std::vector<Direction>  direction;

	};

	std::map<Frog::Type, FrogData> initializeFrogData();
	std::map<Lane::Type, LaneData> initializeLaneData();

}