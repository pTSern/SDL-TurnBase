#include "PlayState.h"
const std::string PlayState::s_playID = "PLAY";
bool PlayState::m_Break = false;
int PlayState::s_gameTurn = 1;
void PlayState::Render()
{
	TextureManager::GetInstance()->Draw("background", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_FLIP_NONE);
	TextureManager::GetInstance()->Draw("skill_layer", 0, SCREEN_HEIGHT - 268, SCREEN_WIDTH, 268, SDL_FLIP_NONE);
	m_gameObjects = m_copyGameObjects;
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) (m_gameObjects[i])->Draw();
		else break;
	}
}
void PlayState::Update(float dt)
{
	int noTurnNum = 0;
	//m_gameObjects = m_copyGameObjects;
	std::sort(m_gameObjects.begin(), m_gameObjects.end(), Champion::SortManager());
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (!m_Break) m_gameObjects[i]->Update(dt);
		else break;
		if (m_gameObjects[i]->GetIsWin())
		{
			PlayState::m_Break = true;
			Engine::GetInstance()->getStateMachine()->ChangeState(new MainMenuState());
			break;
		}
	}
	for (int i = m_gameObjects.size() - 1; i >= 0; i--)
	{
		if (m_gameObjects[i]->CheckIsDead())
		{
			m_gameObjects.erase(m_gameObjects.begin() + i);
		}
	}

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		//std::cout << m_gameObjects[i]->GetName() << ": ISTURN: " << m_gameObjects[i]->GetIsTurn() <<  " - ISENDTURN: " << m_gameObjects[i]->GetIsEndTurn() << std::endl;
		if (!m_gameObjects[i]->GetIsTurn() && m_gameObjects[i]->GetIsEndTurn())
		{
			int k = i + 1;
			if (k >= m_gameObjects.size())
			{
				k = 0;
				for (int j = 0; j < m_gameObjects.size(); j++)
				{
					m_gameObjects[j]->SetIsEndTurn(false);
				}
			}
			if (!m_gameObjects[k]->GetIsTurn() && !m_gameObjects[k]->GetIsEndTurn()) m_gameObjects[k]->SetIsTurn(true);
		}
		else if (!m_gameObjects[i]->GetIsTurn() && !m_gameObjects[i]->GetIsEndTurn())
		{
			noTurnNum++;
			if (noTurnNum >= m_gameObjects.size() - 1)
			{
				m_gameObjects[0]->SetIsTurn(true);
			}
		}
	}
}
void PlayState::Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList)
{
	for (int i = 0; i < textureList.size(); i++)
	{
		if (textureList[i].pros != nullptr)
		{
			TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
		}
		else
		{
			TextureManager::GetInstance()->Load(textureList[i].textureID, textureList[i].fileAddress);
		}
	}
}
bool PlayState::OnEnter()
{
	AutoSetPostionInBattle();
	SoundManager::GetInstance()->PlayMusic("battle");
	
	m_textureList =
	{
		{"background", "assets/bg.png", "", nullptr},
		{"dice", "assets/dice.png", "", nullptr},
		{"skill_layer", "assets/skill_layer.png", "", nullptr},
		{"target", "assets/target.png", "", nullptr},
		{"force_dice", "assets/force_dice.png", "", nullptr},
		{"heath_bar", "assets/heathbar.png", "", nullptr},
		{"ap_bar", "assets/apbar.png", "", nullptr},
		{"skill_infor_bg", "assets/skilldetailBack.png", "", nullptr}
	};
	Handle_LoadedTexture_Object(m_textureList);
	
	//Init GameObject to draw and manager
	for (int i = 0; i < NUMBER_OF_TEAM; i++)
	{
		for (int j = 0; j < NUMBER_OF_CHAMPION_IN_A_TEAM; j++)
		{
			m_pTeamList[i][j]->InitAdditionProperties();
			m_gameObjects.push_back(m_pTeamList[i][j]); 
		}
	}
	//Sort by speed
	std::sort(m_gameObjects.begin(), m_gameObjects.end(), Champion::SortManager());
	m_copyGameObjects = m_gameObjects;
	//Set first champion in list isTurn = true
	m_gameObjects[0]->SetIsTurn(true);
	
	std::cout << "BATTLE LOG:" << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;

	return true;
}
bool PlayState::OnExit()
{
	AdditionEffect::GetInstance()->Clean();
	//AdditionEffect::GetInstance()->Clean();
	for (int i = 0; i < m_textureList.size(); i++)
	{
		TextureManager::GetInstance()->Drop(m_textureList[i].textureID);
	}
	for (int i = m_gameObjects.size() -1 ; i >= 0; i--)
	{
		m_gameObjects[i]->Clean();
		delete m_gameObjects[i];
		//delete m_copyGameObjects[i];
	}
	
	m_textureList.clear();
	m_gameObjects.clear();
	m_copyGameObjects.clear();
	m_pTeamList.clear();
	
	//std::vector<TexttureFileHandler>().swap(m_textureList);
	//std::vector<std::vector<Champion*>>().swap(m_pTeamList);
	//std::vector<Champion*>().swap( m_gameObjects);
	//std::vector<Callback>().swap(m_callbacks);
	//std::vector<Champion*>().swap(m_copyGameObjects);

	//m_textureList.shrink_to_fit();
	//m_gameObjects.shrink_to_fit();
	//m_copyGameObjects.shrink_to_fit();
	//m_pTeamList.shrink_to_fit();

	//reset isBreak for 2 gasme state: Picking n Menu
	MainMenuState::m_Break = false;
	PickingPhase::m_Break = false;
	PlayState::m_Break = false;
	return true;
}
void PlayState::AutoSetPostionInBattle()
{
	for (int i = 0; i < NUMBER_OF_TEAM; i++)
	{
		for (int j = 0; j < NUMBER_OF_CHAMPION_IN_A_TEAM; j++)
		{
			//auto set flip
			m_pTeamList[NUMBER_OF_TEAM - 1][j]->SetBackFlip();

			//auto set distance
			m_pTeamList[i][j]->SetPIB_X(DISTANCE_STATER * (i + 1) + DISTANCE_K * (j) * (2*i-1) );
			m_pTeamList[i][j]->SetPIB_Y(m_pTeamList[0][j]->GetX()*m_pTeamList[0][j]->GetX()*(0.018) - 8.232*m_pTeamList[0][j]->GetX() + 936.192);

			//Auto set attacker and defender
			m_pTeamList[i][j]->SetAttackTeam(m_pTeamList[i]);
			if (i + 1 >= NUMBER_OF_TEAM)
			{
				m_pTeamList[i][j]->SetDefendTeam(m_pTeamList[0]);
			}
			else
			{
				m_pTeamList[i][j]->SetDefendTeam(m_pTeamList[i + 1]);
			}
		}
	}
}
void PlayState::setCallbacks(const std::vector<Callback>& callbacks)
{

}