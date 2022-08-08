#include "TextureManager.h"
#include "Engine.h"

TextureManager* TextureManager::s_pInstance = nullptr;

bool TextureManager::Load(std::string id, std::string fileName)
{
	SDL_Surface* pSurface = IMG_Load(fileName.c_str());//c_str() convert string type of cpp to string type of C 
	if (pSurface == nullptr)
	{
		SDL_Log("Falied to load texture: %s", fileName.c_str());
		SDL_Log("Message: %s", SDL_GetError());
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), pSurface);
	if (pTexture == nullptr)
	{
		SDL_Log("Falied to load texture: %s", SDL_GetError());
		return false;
	}

	m_pTextureMap[id] = pTexture;
	SDL_FreeSurface(pSurface);
	return true;
}
void TextureManager::Drop(std::string id)
{
	SDL_DestroyTexture(m_pTextureMap[id]);
	m_pTextureMap.erase(id);
}
void TextureManager::Clean()
{
	std::map<std::string, SDL_Texture*>::iterator it;
	for (it = m_pTextureMap.begin(); it != m_pTextureMap.end(); ++it)
	{
		SDL_DestroyTexture(it->second);
	}
	m_pTextureMap.clear();
	std::map<std::string, SDL_Texture*>().swap(m_pTextureMap);
}

void TextureManager::Draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect sourceRect = {0, 0, width, height }; 
	SDL_Rect demesionRect = {x,y, width, height};

	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_pTextureMap[id], &sourceRect, &demesionRect, 0, nullptr, flip);
}
void TextureManager::DrawFrame(std::string id, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect sourceRect = { width*frame, height*(row-1), width, height };
	SDL_Rect demesionRect = { x,y, width, height};
	SDL_RenderCopyEx(Engine::GetInstance()->GetRenderer(), m_pTextureMap[id], &sourceRect, &demesionRect, 0, nullptr, flip);
}
