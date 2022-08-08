#include "StateGameMachine.h"
void GameStateMachine::PushState(GameState* pState)
{
	m_pGameStates.push_back(pState);
	m_pGameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	if (!m_pGameStates.empty())
	{
		if (m_pGameStates.back()->OnExit())
		{
			delete m_pGameStates.back();
			m_pGameStates.pop_back();
		}
	}
}

void GameStateMachine::ChangeState(GameState* pState)
{
	if (!m_pGameStates.empty())
	{
		if (m_pGameStates.back()->GetStateID() == pState->GetStateID())
		{
			return; // do nothing
		}
		if (m_pGameStates.back()->OnExit())
		{
			delete m_pGameStates.back();
			m_pGameStates.pop_back();
		}
	}

	m_pGameStates.push_back(pState);
	// initialise it
	m_pGameStates.back()->OnEnter();
}

void GameStateMachine::Update(float dt)
{
	if (!m_pGameStates.empty())
	{
		m_pGameStates.back()->Update(dt);
	}
}
void GameStateMachine::Render()
{
	if (!m_pGameStates.empty())
	{
		m_pGameStates.back()->Render();
	}
}