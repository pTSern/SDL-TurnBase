#pragma once
#include <SDL.h>
const int TARGET_FPS = 60;
const float TARGET_DELTATIME = 1.5f;

class Timer
{
public:
	inline static Timer* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new Timer();
	}
	inline float GetDeltaTime() { return m_DeltaTime; }
	void Tick();
private:
	Timer() {};
	static Timer* s_pInstance;
	float m_DeltaTime;
	float m_LastTick;
};

