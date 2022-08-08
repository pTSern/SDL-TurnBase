#include "Timer.h"
Timer*  Timer::s_pInstance = nullptr;
void Timer::Tick()
{
	m_DeltaTime = (SDL_GetTicks() - m_LastTick) / 1000.0f * TARGET_FPS;
	if (m_DeltaTime > TARGET_DELTATIME) m_DeltaTime = TARGET_DELTATIME;
	m_LastTick = SDL_GetTicks();
}