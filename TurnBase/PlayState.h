#pragma once
#include "Champion.h"
#include "MenuState.h"
#include "MainMenuState.h"
#include <vector>
#include <algorithm>  
#include "GameObjectFactory.h"
#include "SoundManager.h"

const int DISTANCE_K = 100;
const int DISTANCE_STATER = 312;

class PlayState : public MenuState
{
public:
	static bool m_Break;
	PlayState(std::vector<std::vector<Champion*>> pTeamList) : m_pTeamList(pTeamList) {};
	virtual void Update(float dt);
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual void Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList);
	virtual std::string GetStateID() const { return s_playID; }
private:
	static const std::string s_playID;
	static int s_gameTurn;
	std::vector<Champion*> m_gameObjects;
	std::vector<Champion*> m_copyGameObjects;
	virtual void setCallbacks(const std::vector<Callback>& callbacks);
	std::vector<std::vector<Champion*>> m_pTeamList;
	void AutoSetPostionInBattle();
};
