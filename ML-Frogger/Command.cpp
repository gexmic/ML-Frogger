/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

Command class

*/


#include "Command.h"
#include "Category.h"


namespace GEX
{
	Command::Command() :
		action(),
		category(Category::None)
	{}
}




