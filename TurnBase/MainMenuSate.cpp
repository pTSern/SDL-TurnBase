#include "MainMenuState.h"
const std::string MainMenuState::s_menuID = "MENU";
bool MainMenuState::m_Break = false;
//static std::vector<std::vector<Champion*>> m_pTeamList(0, std::vector<Champion*>(0, nullptr));
static bool deleteAll(MainMenuState* theElement) { delete theElement; return true; }
void MainMenuState::Update(float dt)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) m_gameObjects[i]->Update(dt);
		else break;
	}
}
void MainMenuState::Render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) m_gameObjects[i]->Draw();
		else break;
		//std::cout << "Draw\n";
	}
}
void MainMenuState::Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		//if (textureList[i].className != "")
		//{
			//TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
			m_gameObjects.push_back(GameObjectFactory::GetInstance()->Create(textureList[i].className, textureList[i].pros));
		//}
		//else
		//{
		//	TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
		//}
	}
}
bool MainMenuState::OnEnter()
{
	SoundManager::GetInstance()->PlayMusic("menu");
	TextureManager::GetInstance()->Load("Menu", "assets/the_menu.png");
	m_textureList = 
	{ 
		{"Play", "", "MENUBUTTON", new Properties((SCREEN_WIDTH - 166) / 2, (SCREEN_HEIGHT - 142) / 2 , 167, 42, 1, "Menu", SDL_FLIP_NONE, 0)},
		{"Exit", "", "MENUBUTTON", new Properties((SCREEN_WIDTH - 166) / 2, (SCREEN_HEIGHT - 42) / 2 , 167, 42, 1, "Menu", SDL_FLIP_NONE, 1, 0, 2)}
	};
	Handle_LoadedTexture_Object(m_textureList);

	m_callbacks.push_back(s_MenuToPlay);
	m_callbacks.push_back(s_ExitFromMenu);
	setCallbacks(m_callbacks);

	return true;
}
bool MainMenuState::OnExit()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Clean();
	}

	m_textureList.clear();
	m_gameObjects.clear();
	m_callbacks.clear();
	TextureManager::GetInstance()->Drop("Menu");
	//for (int i = 0; i < m_textureList.size(); i++)
	//{
	//	TextureManager::GetInstance()->Drop(m_textureList[i].textureID);
	//}
	//std::vector<TexttureFileHandler>().swap(m_textureList);
	//std::vector<GameObject*>().swap(m_gameObjects);
	//std::vector<Callback>().swap(m_callbacks);

	//m_gameObjects.shrink_to_fit();
	//m_callbacks.shrink_to_fit();
	//m_textureList.shrink_to_fit();
	return true;
}
void MainMenuState::s_MenuToPlay(int index)
{
	MainMenuState::m_Break = true;
	Engine::GetInstance()->getStateMachine()->ChangeState(new PickingPhase());
}

void MainMenuState::s_ExitFromMenu(int index)
{
	Engine::GetInstance()->Quit();
}

void MainMenuState::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}