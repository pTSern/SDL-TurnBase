#pragma once
#include <string>
#include <iomanip>
#include <sstream>
#include <map>
#include <SDL.h>
#include <SDL_ttf.h>
class FontsManager
{
public:
	inline static FontsManager* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new FontsManager();
	}
	bool Load(std::string id, std::string fileName, int size);
	void Draw(std::string id, int x, int y, int width, int height, std::string text, int RGB_R, int RGB_G, int RGB_B);
	void Clean();
	void DrawBreakLine(std::string id, int x, int y, int width, int height, std::string text, int RGB_R, int RGB_G, int RGB_B, int warpLength);

	std::string ConvertFloatToString_Lesser(float num, int displayNum);

private:
	FontsManager();
	static FontsManager* s_pInstance;
	std::map<std::string, TTF_Font*> m_pFontsMap;
};

