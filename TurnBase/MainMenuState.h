#pragma once
#include"GameState.h"
#include <vector>
#include "TextureManager.h"
#include "MenuButton.h"
#include "Engine.h"
#include "MenuState.h"
#include "PickingPhase.h"

class MainMenuState : public MenuState
{
public:
	static bool m_Break;
	virtual void Update(float dt);
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual void Handle_LoadedTexture_Object(std::vector<TexttureFileHandler> textureList);
	virtual std::string GetStateID() const { return s_menuID; }
private:
	
	static const std::string s_menuID;
	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_MenuToPlay(int index);
	static void s_ExitFromMenu(int index);

	std::vector<GameObject*> m_gameObjects;
};

