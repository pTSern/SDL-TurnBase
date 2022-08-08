#include "PickingPhase.h"
const std::string PickingPhase::s_pickingID = "PICKING PHASE";
int PickingPhase::m_pickingTime = 0;
int PickingPhase::m_currentTeam = 0;
int PickingPhase::m_currentChamp = 0;
bool PickingPhase::m_Break = false;

static std::vector<std::vector<Champion*>> m_pTeamList(NUMBER_OF_TEAM, std::vector<Champion*>(NUMBER_OF_CHAMPION_IN_A_TEAM, nullptr));
static std::vector<GameObject*> m_championList;
static std::vector<std::string> deleteTextureList;
static std::vector<int> deleteIndexList;

void PickingPhase::Update(float dt)
{
	
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) m_gameObjects[i]->Update(dt);
		else break;
		//std::cout << m_index << std::endl;
	}
}
void PickingPhase::Render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) m_gameObjects[i]->Draw();
		else break;
	}
}

void PickingPhase::Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList)
{
	int xRow = 0; 
	int yCol = 0;
	int callbackID = 0; //only need s_Picking(int index) (ID = 0)
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i].pros != nullptr)
		{
			TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
			//Init champion list
			m_championList.push_back(GameObjectFactory::GetInstance()->Create(textureList[i].className, textureList[i].pros));
			//Init "Button" list
			m_gameObjects.push_back(GameObjectFactory::GetInstance()->Create("MENUBUTTON", new Properties(xRow, yCol, X_DISTANCE_BETWEEN_CHAMPION, Y_DISTANCE_BETWEEN_CHAMPION, 10, textureList[i].textureID, SDL_FLIP_NONE, callbackID, i)));
			xRow += X_DISTANCE_BETWEEN_CHAMPION;
			if (xRow > SCREEN_WIDTH)
			{
				yCol += Y_DISTANCE_BETWEEN_CHAMPION;
				xRow = 0;
			}
		}
		else
		{
			TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
		}
		deleteTextureList.push_back(textureList[i].textureID);
	}
}
bool PickingPhase::OnEnter()
{
	SoundManager::GetInstance()->PlayMusic("picking");
	m_textureList =
	{
		{"wizard", "assets/the_wizard.png", "WIZARD", new Properties(0, 0, 168, 168, 18, "wizard", SDL_FLIP_NONE)},
		{"jingu", "assets/the_jingu.png", "JINGU", new Properties(0, 0, 168, 168, 12, "jingu", SDL_FLIP_NONE)},
		{"god", "assets/the_god.png", "GOD", new Properties(0, 0, 168, 168, 27, "god", SDL_FLIP_NONE)},
		{"sam", "assets/the_samurai.png", "SAMURAI", new Properties(0, 0, 168, 168, 28, "sam", SDL_FLIP_NONE)},
		{"mage", "assets/the_mage.png", "MAGE", new Properties(0, 0, 168, 168, 28, "mage", SDL_FLIP_NONE)}
	};
	Handle_LoadedTexture_Object(m_textureList);

	m_callbacks.push_back(s_Picking);
	m_callbacks.push_back(s_Exit);
	this->setCallbacks(m_callbacks);
	
	return true;
}
bool PickingPhase::OnExit()
{
	//Clean all noneed texture
	std::sort(deleteIndexList.begin(), deleteIndexList.end());
	for (int i = deleteIndexList.size()-1; i >= 0 ; i--)
	{
		deleteTextureList.erase(deleteTextureList.begin() + deleteIndexList[i]);
		m_gameObjects.erase(m_gameObjects.begin() + deleteIndexList[i]);
	}
	for (int i = 0; i < deleteTextureList.size(); i++)
	{
		TextureManager::GetInstance()->Drop(deleteTextureList[i]);
	}
	//for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	//{
	//	delete m_gameObjects[i];
	//}
	//Clean all vector

	m_gameObjects.clear();
	//TextureManager::GetInstance()->Infor();
	m_championList.clear();
	m_textureList.clear();
	deleteIndexList.clear();
	deleteTextureList.clear();
	m_callbacks.clear();
	
	//std::vector<std::string>().swap(deleteTextureList);
	//std::vector<int>().swap(deleteIndexList);
	//std::vector<GameObject*>().swap(m_championList);
	//std::vector<TexttureFileHandler>().swap(m_textureList);
	//std::vector<GameObject*>().swap(m_gameObjects);
	//std::vector<Callback>().swap(m_callbacks);

	//m_gameObjects.shrink_to_fit();
	//m_championList.shrink_to_fit();
	//m_textureList.shrink_to_fit();
	//deleteIndexList.shrink_to_fit();
	//deleteTextureList.shrink_to_fit();
	//m_callbacks.shrink_to_fit();

	m_currentTeam = 0;
	m_currentChamp = 0;
	m_pickingTime = 0;
	return true;
}
void PickingPhase::s_Picking(int index)
{
	//count picking time
	m_pickingTime++;
	//set position for champion when he in battle by picking
	dynamic_cast<Champion*>(m_championList[index])->SetPositionInBattle(m_currentChamp);
	//set champion in team
	m_pTeamList[m_currentTeam][m_currentChamp] = dynamic_cast<Champion*>(m_championList[index]);
	//input index need to be deleted
	deleteIndexList.push_back(index);
	//increate Team nummber after picking
	m_currentTeam++;
	//caculate team number, if it > number of team -> reset it to 0 then increa currentChamp (next champion)
	if (m_currentTeam >= NUMBER_OF_TEAM )
	{
		m_currentTeam = 0;
		m_currentChamp++;
	}
	//Change game state after picking time == number of team x number of champion in a team
	if (m_pickingTime == NUMBER_OF_TEAM * NUMBER_OF_CHAMPION_IN_A_TEAM)
	{
		PickingPhase::m_Break = true;
		Engine::GetInstance()->getStateMachine()->ChangeState(new PlayState(m_pTeamList));
	}
}

void PickingPhase::s_Exit(int index)
{
}

void PickingPhase::setCallbacks(const std::vector<Callback>& callbacks)
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (dynamic_cast<MenuButton*>(m_gameObjects[i]))
		{
			MenuButton* pButton = dynamic_cast<MenuButton*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
			//std::cout << pButton->getCallbackID() <<std::endl;
		}
	}
}