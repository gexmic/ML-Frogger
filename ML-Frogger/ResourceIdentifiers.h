/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

This is a enum for all the resource the game have, plane, backgoud, button.

*/

#pragma once

namespace GEX
{
	enum class TextureID
	{
		Desert,
		Airplane,
		Missile,
		TitleScreen,
		MenuScreen,
		GexScreen,
		ButtonNormal,
		ButtonSelected,
		ButtonPressed,
		Bullet,	
		HealthRefill,
		MissileRefill,
		FireSpread,
		FireRate,
		Particale,
		Entity,
		Explosion,
		FinishLine,
		Jungle
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
