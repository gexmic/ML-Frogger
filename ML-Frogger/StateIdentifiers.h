/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Enum for the different state the game could be in

*/

#pragma once

enum class StateID
{
	None,
	Title,
	Menu,
	Game,
	Loading,
	Pause,
	Gex,
	GameOver
};