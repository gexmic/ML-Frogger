/**
@file
@author  D Burchill <david.burchill@nbcc.ca>
@version 1.0

@section LICENSE

This software is based on the original frogger game. Is a project for my programing class in NBCC Moncton

@section DESCRIPTION

different state the game could be in
*/

#include "State.h"
#include "StateStack.h"



namespace GEX
{

	State::Context::Context(sf::RenderWindow& window, PlayerControl& player) :
		window(&window),
		player(&player)
	{}


	GEX::State::State(StateStack & stack, Context context) :
		_stack(&stack),
		_context(context)
	{}

	State::~State()
	{
	}

	void State::requestStackPush(StateID stateID)
	{
		_stack->pushState(stateID);
	}

	void State::requestStackPop()
	{
		_stack->popState();
	}

	void State::requestStateClear()
	{
		_stack->clearStates();
	}

	State::Context State::getContext() const
	{
		return _context;
	}	
}