/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

this dataTable class have a table for the airplaine attributes wen a airplaine is construct it get the information on the table 

*/

#pragma once
#include "ResourceIdentifiers.h"
#include <map>
#include "Airplaine.h"
#include <vector>
#include "Projectile.h"
#include "Pickup.h"
#include "Particule.h"

namespace GEX
{


	struct Direction
	{
		Direction	(float a, float b);
		float		angle;
		float		distance;

	};

	struct AirplainDate
	{
		int						hitpoint;
		float					speed;
		TextureID				texture;
		sf::IntRect				location;
		sf::Time				fireInterval;
		std::vector<Direction>  direction;
	};

	struct ProjectileDate
	{
		int						damege;
		float					speed;
		float					approachRate; ///< for guided projectile how fast ther turn
		TextureID				texture;
		sf::IntRect				location;

	};

	struct PickupDate
	{
		std::function<void(Airplaine&)>		action;
		TextureID							texture;
		sf::IntRect				            location;
	};

	struct ParticuleData
	{
		sf::Color							color;
		sf::Time							lifetime;
	};

	std::map<Airplaine::Type, AirplainDate>			initializeAircraftDate();
	std::map<Projectile::Type, ProjectileDate>		initializeProjectileDate();
	std::map<Pickup::Type, PickupDate>				initializePickupDate();
	std::map<Particule::Type, ParticuleData>        initializeParticleData();

}