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
			SoundEffet				= 1 << 1,
			Frog					= 1 << 2,
			Car1					= 1 << 3,
			RaceCar1				= 1 << 4,
			RaceCar2				= 1 << 5,
			Truck					= 1 << 6,
			Tractor					= 1 << 7,

			Car						= Car1 | RaceCar1 | RaceCar2 | Tractor | Tractor,

		};
	}
}
