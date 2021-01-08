#pragma once
#include "../CSC8503Common/PushdownState.h"
#include "../CSC8503Common/PushdownMachine.h"
//#include	"../"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"
#include "../../Common/Window.h"
#include "CourseGame.h"

using namespace NCL;
using namespace CSC8503;

enum CurrentState
{
	MainMenuState,
	PlayState,
	DebugState,
	PauseState
};

CourseGame* g;

class Pause : public PushdownState
{
	PushdownResult OnUpdate(float dt, PushdownState** newState) override
	{


		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
		{
			return PushdownResult::Pop;
		}
		return PushdownResult::NoChange;
	}
	void OnAwake() override
	{
		//Debug::
		Debug::Print("Press Space To  Start", Vector2(50, 50), Vector4(1, 0, 0, 1));
		std::cout << "Paused";
	}
};


class Play : public PushdownState
{
	PushdownResult OnUpdate(float dt, PushdownState** newState) override
	{

		g->UpdateGame(dt);

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::P))
		{
			*newState = new Pause();
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE))
		{
			return PushdownResult::Pop;
		}

		return PushdownResult::NoChange;

	}
	void OnAwake() override
	{

	}
};

class MainMenu : public PushdownState
{

	PushdownResult OnUpdate(float dt, PushdownState** newState) override
	{
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::SPACE))
		{
			*newState = new Play();
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::ESCAPE))
		{
			return PushdownResult::Pop;
		}
		return PushdownResult::NoChange;
	}

	void  OnAwake() override
	{

		Debug::Print("Press Space To  Start", Vector2(50, 50), Vector4(1, 0, 0, 1));

		std::cout << " Welcome to a really awesome game !\n";
		std::cout << " Press Space To Begin or escape to quit !\n";
		g = new CourseGame();
	}
};


