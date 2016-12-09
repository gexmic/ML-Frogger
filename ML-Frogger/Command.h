/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

This is the command class that will pass commande to the commandeQueue class.

*/


#pragma once
#include <cassert>
#include <functional>
#include "SFML/System/Time.hpp"


namespace GEX
{
	class SceneNode; // forward decleration

	class Command
	{
	public:
													Command();

		std::function<void(SceneNode&, sf::Time)>   action;
		unsigned int								category;
	};

	template <typename GameObject, typename function>
	std::function<void(SceneNode&, sf::Time)>derivedAction(function fn)
	{
		return [=](SceneNode& node, sf::Time dt)
		{
			// check if downcast is safe
			assert(dynamic_cast<GameObject*>(&node) != nullptr);

			// downcast node
			fn(static_cast<GameObject&>(node), dt);
		};
	}
}


