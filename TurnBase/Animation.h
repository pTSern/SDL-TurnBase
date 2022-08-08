#pragma once
#include "SDL.h"
#include <string>
#include "timer.h"
class Animation
{
public:
	void Update();
	void SetPros(std::string textureID, int spriteRow, int frameCount = 1, int animateSpeed = 80, SDL_RendererFlip flip = SDL_FLIP_NONE, int currentFrame = 0);
	void Draw(float x, float y, int width, int height);
	bool IsReachLastFrame(float dt);
	
private:
	int m_SpriteRow, m_FrameCount, m_AnimateSpeed, m_SpriteFrame;
	std::string m_TextureID;
	SDL_RendererFlip m_Flip;
	float m_zeroTimmer;
	bool m_bSpecialDraw;
};

