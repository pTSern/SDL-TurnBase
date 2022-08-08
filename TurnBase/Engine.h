#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "StateGameMachine.h"
#include "TextureManager.h"
#include "Input.h"
#include "Timer.h"
#include <map>
#include "MainMenuState.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

class Engine
{
public:
	static Engine* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new Engine();
	}

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

	bool Init();
	void Clean();
	void Quit();

	void Update();
	void Render();
	void Events();

	inline bool isRunning()
	{
		return m_isRunning;
	}
	inline SDL_Renderer* GetRenderer()
	{
		return m_pRenderer;
	}
private:
	Engine() {};
	bool m_isRunning;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	static Engine* s_pInstance;
	GameStateMachine* m_pGameStateMachine = nullptr;
};

