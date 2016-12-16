/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

This is a enum for all the resource the game have background, frog

*/

#pragma once

namespace GEX
{
	enum class TextureID
	{		
		TitleScreen,
		MenuScreen,
		Background,
		FroggerAtlas
	};

	enum class FontID
	{
		Main
	};

	enum class SoundEffectID {
		AlliedGunFire,
		Botton,
		CollectPickup,
		EnemyGunFire,
		Explosion1,
		Explosion2,
		LauchMissile
	};
}
