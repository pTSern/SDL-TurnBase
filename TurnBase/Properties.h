#pragma once
#include <string>
#include <SDL.h>
class Properties
{
public:
	
	Properties(float x, float y, int width, int height, int frameCount ,std::string textureID, SDL_RendererFlip flip, int callBackID = 0, int index = 0, int currentRow = 1, int currentFrame = 0) :
		m_x(x), m_y(y),
		m_width(width), 
		m_height(height), 
		m_frameCount(frameCount),
		m_textureID(textureID), 
		m_flip(flip),
		m_callBackID(callBackID),
		m_index(index),
		m_currentRow(currentRow),
		m_currentFrame(currentFrame)
		{};
	
	float getX() const { return m_x; }
	float getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getFrameCount() const { return m_frameCount; }
	int getCallBackID() const { return m_callBackID; }
	int getIndex() const { return m_index; }
	int getCurrentRow() const {return m_currentRow; }
	int getCurrentFrame() const { return m_currentFrame; }
	SDL_RendererFlip getFlip() const { return m_flip; };
	std::string getTextureID() const { return m_textureID; }
private:
	int m_width, m_height;
	int m_frameCount;
	//Champion* (*m_pCallBack) ();
	int m_callBackID, m_index, m_currentRow, m_currentFrame;
	float m_x, m_y;
	std::string m_textureID;
	SDL_RendererFlip m_flip;
};