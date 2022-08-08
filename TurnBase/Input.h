#pragma once
#include <SDL.h>
#include <vector>
#include "Transform.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class Input
{
public:
	static Input* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new Input();
	}

	bool GetMouseButtonState(int buttonNumber)
	{
		return m_mouseButtonStates[buttonNumber];
	}

	Transform* GetMousePosition()
	{
		return m_mousePosition;
	}

	void Listen();
	bool GetKeyDown(SDL_Scancode key);
	bool GetMouseKeyDown();

	bool KeyUp();
	bool KeyDown();
	
private:
	Input();
	static Input* s_pInstance;
	std::vector<bool> m_mouseButtonStates;

	void MouseButtonDown(SDL_Event event);
	void MouseButtonUp(SDL_Event event);
	//void KeyDown();
	//void KeyUp();

	const Uint8* m_pKeyState;
	Transform* m_mousePosition = new Transform(0,0);

};

