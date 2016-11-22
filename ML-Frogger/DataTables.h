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
#include <vector>

namespace GEX
{


	struct Direction
	{
		Direction	(float a, float b);
		float		angle;
		float		distance;

	};	

}