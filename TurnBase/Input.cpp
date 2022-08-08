#include "Input.h"
#include "Engine.h"
Input::Input() 
{
	m_pKeyState = SDL_GetKeyboardState(nullptr);

	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
};

Input* Input::s_pInstance = nullptr;

void Input::Listen()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		Engine::GetInstance()->Quit();
		break;
	case SDL_MOUSEBUTTONDOWN:
		MouseButtonDown(event);
		break;
	case SDL_MOUSEBUTTONUP:
		MouseButtonUp(event);
		break;
	case SDL_MOUSEMOTION:
		m_mousePosition->X = (event.motion.x);
		m_mousePosition->Y = (event.motion.y);
		break;
	case SDL_KEYDOWN:
		KeyDown();
		break;
	case SDL_KEYUP:
		KeyUp();
		break;
	}
}
bool Input::GetKeyDown(SDL_Scancode key)
{
	if (m_pKeyState[key] == 1)
	{
		return true;
	}
	return false;
}

bool Input::KeyDown()
{
	m_pKeyState = SDL_GetKeyboardState(nullptr);
	return true;
}
bool Input::KeyUp()
{
	m_pKeyState = SDL_GetKeyboardState(nullptr);
	return true;
}

void Input::MouseButtonDown(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void Input::MouseButtonUp(SDL_Event event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}