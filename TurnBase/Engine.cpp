#include "Engine.h"
#include "SoundManager.h"
Engine* Engine::s_pInstance = nullptr;

bool Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0 && IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError()); //same to printf
		return false;
	}

	m_pWindow = SDL_CreateWindow("Turn Base", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if (m_pWindow == nullptr)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	//Init music
	Mix_VolumeMusic(50);
	SoundManager::GetInstance()->LoadMusic("menu", "music/menu.ogg");
	SoundManager::GetInstance()->LoadMusic("battle", "music/battle.ogg");
	SoundManager::GetInstance()->LoadMusic("picking", "music/picking.ogg");
	//Init fonts
	FontsManager::GetInstance()->Load("minecraft", "./fonts/Minecraft-Regular.ttf", 16);
	//Init Game State
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->ChangeState(new MainMenuState());

	m_isRunning = true;
	return m_isRunning;
}
void Engine::Clean()
{
	TextureManager::GetInstance()->Clean();
	
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	IMG_Quit();
	SDL_Quit();
}
void Engine::Quit()
{
	SoundManager::GetInstance()->Clean();
	FontsManager::GetInstance()->Clean();
	m_isRunning = false;
}
void Engine::Update()
{
	float dt = Timer::GetInstance()->GetDeltaTime();;
	m_pGameStateMachine->Update(dt);
}
void Engine::Render()
{
	SDL_SetRenderDrawColor(m_pRenderer, 0, 0,0,0);
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->Render();

	SDL_RenderPresent(m_pRenderer);
}
void Engine::Events()
{
	Input::GetInstance()->Listen();

}