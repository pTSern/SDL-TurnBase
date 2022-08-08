#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void PushState(GameState* pState);
	void ChangeState(GameState* pState);
	void PopState();
	void Update(float dt);
	void Render();
private:
	std::vector<GameState*> m_pGameStates;
};

