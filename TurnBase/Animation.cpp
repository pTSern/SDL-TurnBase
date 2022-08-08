#include "Animation.h"
#include "TextureManager.h"
#include <iostream>
void Animation::SetPros(std::string textureID, int spriteRow, int frameCount, int animateSpeed, SDL_RendererFlip flip, int currentFrame)
{
	m_TextureID = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_AnimateSpeed = animateSpeed;
	m_Flip = flip;
	m_SpriteFrame = currentFrame;
}
void Animation::Update()
{
	//Fix unknown m_AnimateSpeed = 0 or m_FrameCount = 0
	m_AnimateSpeed = (m_AnimateSpeed != 0) ? m_AnimateSpeed : 80;
	m_FrameCount = (m_FrameCount != 0) ? m_FrameCount : 1;
	m_SpriteFrame = ((int)(SDL_GetTicks() / m_AnimateSpeed)) % m_FrameCount;
}
bool Animation::IsReachLastFrame(float dt)
{
	m_bSpecialDraw = true;
	if (((int)(m_zeroTimmer / m_AnimateSpeed) % (m_FrameCount + 1)) == (m_FrameCount))
	{
		m_bSpecialDraw = false;
		m_zeroTimmer = 0;
		return true;
	}
	m_zeroTimmer += dt * 1000 / TARGET_FPS;
	return false;
}
void Animation::Draw(float x, float y, int width, int height)
{
	if (!m_bSpecialDraw) TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, m_SpriteFrame, m_Flip);
	else TextureManager::GetInstance()->DrawFrame(m_TextureID, x, y, width, height, m_SpriteRow, ((int)(m_zeroTimmer / m_AnimateSpeed) % m_FrameCount), m_Flip);
}