/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

enum to have the type of Frog

*/

#pragma once

namespace GEX
{
	namespace Category
	{
		enum Type
		{
			None = 0,			 // bit fied operator
			SceneGroundLayer		= 1 << 0,
			Frog					= 1 << 1,
			Car1					= 1 << 2,
			RaceCar1				= 1 << 3,
			RaceCar2				= 1 << 4,
			Truck					= 1 << 5,
			Tractor					= 1 << 6,
			Track					= 1 << 7,
			Water					= 1 << 8,

			// groupe all the different car together
			Car						= Car1 | RaceCar1 | RaceCar2 | Tractor | Tractor,

		};
	}
}
