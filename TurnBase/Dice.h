#pragma once
#include "Input.h"
#include "Animation.h"
#include "GameObject.h"
#include "AdditionEffect.h"
class Dice : public GameObject
{
public:
	inline static Dice* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new Dice(new Properties(512, 150, 64, 64, 30, "dice", SDL_FLIP_NONE));
	}
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	int RollDice();
	void ResetDice();
	bool GetIsDice();
private:
	Dice(const Properties* pProperties) : GameObject(pProperties) 
	{ 
		m_currentRow = 8; 
		m_animationSpeed = 20;
		m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);
	};
	static int s_spriteRow;
	static bool m_IsRoll, m_IsPressSpace;
	int m_DiceNum;
	static Dice* s_pInstance;
	//Animation* m_pAnimation = new Animation();
};

