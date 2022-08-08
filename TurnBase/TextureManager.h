#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include <iostream>

class TextureManager
{
public:
	inline static TextureManager* GetInstance() 
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new TextureManager();
	}

	bool Load(std::string id, std::string fileName);
	void Drop(std::string id);
	void Clean();
	void Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip);
	void DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip);
	void Infor() {
		for (auto it = m_pTextureMap.begin(); it != m_pTextureMap.end(); ++it)
		{
			std::cout << it->first << " - " << it->second << std::endl;
		}
	}
private:
	TextureManager() {};
	std::map<std::string, SDL_Texture*> m_pTextureMap;
	static TextureManager* s_pInstance;
};

