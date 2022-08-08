#pragma once
#include "GameState.h"
#include <vector>
#include "TextureManager.h"
#include "MenuButton.h"
#include "Engine.h"
#include "PlayState.h"
#include "MainMenuState.h"
#include "Champion.h"
#include "AdditionEffect.h"

const int X_DISTANCE_BETWEEN_CHAMPION = 168;
const int Y_DISTANCE_BETWEEN_CHAMPION = 168;

class PickingPhase : public MenuState
{
public:
	static bool m_Break;
	virtual void Update(float dtx);
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual void Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList);
	virtual std::string GetStateID() const { return s_pickingID; }
private:
	static const std::string s_pickingID;
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_Picking(int index);
	static void s_Exit(int index);
	static int m_pickingTime;
	static int m_currentTeam, m_currentChamp;

	std::vector<GameObject*> m_gameObjects;
};

