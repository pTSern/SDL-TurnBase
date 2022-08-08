#include "Dice.h"
Dice* Dice::s_pInstance = nullptr;
int Dice::s_spriteRow = 8;

bool Dice::m_IsRoll = false;
bool Dice::m_IsPressSpace = false;

const int MAX_DICENUM = 6;
void Dice::ResetDice()
{
	m_IsRoll = false;
	m_IsPressSpace = false;
}
bool Dice::GetIsDice()
{
	return m_IsRoll;
}
int Dice::RollDice()
{
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && Input::GetInstance()->KeyDown() && !m_IsRoll)
	{
		//s_spriteRow = 1;
		m_currentRow = 1;
		m_DiceNum++;
		m_IsPressSpace = true;
		if (m_DiceNum == 738) m_DiceNum = 0;
		//this->Draw();
	}
	if (Input::GetInstance()->KeyUp() && !m_IsRoll && m_IsPressSpace && !Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
	{
		m_IsRoll = true;
		//s_spriteRow = (MAX_DICENUM - (m_DiceNum % MAX_DICENUM)) + 1;
		m_currentRow = (MAX_DICENUM - (m_DiceNum % MAX_DICENUM)) + 1;
	}
	//return s_spriteRow - 1;
	return m_currentRow - 1;
}
void Dice::Draw()
{
	//m_pAnimation->Draw(512, 150 , 64, 64);
	GameObject::Draw();
	AdditionEffect::GetInstance()->DrawForceOfDice(m_DiceNum);
}
void Dice::Update(float dt)
{
	GameObject::Update(dt);
}
void Dice::Clean()
{
	GameObject::Clean();
}