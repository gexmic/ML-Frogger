/**
@file
@author  Michael Landry	mic_23@hotmail.com
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

This sprite node is for the sprit object in the game.

*/

#pragma once
#include "SceneNode.h"

namespace GEX
{

	class SpriteNode : public SceneNode
	{
	public:
					SpriteNode(const sf::Texture&);
					SpriteNode(const sf::Texture&, sf::IntRect);

	 void			drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
		
	private:
		sf::Sprite  _sprite;
	};
}


