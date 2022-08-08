#include "FontsManager.h"
#include "Engine.h"
#include "TextureManager.h"

FontsManager* FontsManager::s_pInstance = nullptr;
FontsManager::FontsManager()
{
    //Init FontsTF
    if (TTF_Init() < 0)
    {
        SDL_Log("Could not initailize SDL2_ttf, error: %s", TTF_GetError());
    }
}
bool FontsManager::Load(std::string id, std::string fileName, int size)
{
    TTF_Font* pFont = TTF_OpenFont(fileName.c_str(), size);
    if (pFont == nullptr)
    {
        SDL_Log("Could not load font: %s at %s", id.c_str(), fileName.c_str());
        SDL_Log("Message: %s", TTF_GetError());
        return false;
    }
    m_pFontsMap[id] = pFont;
    return true;
}
void FontsManager::Draw(std::string id, int x, int y, int width, int height, std::string text, int RGB_R, int RGB_G, int RGB_B)
{
    SDL_Surface* pFontsSurface = TTF_RenderText_Solid(m_pFontsMap[id], text.c_str(), { (unsigned char)RGB_R, (unsigned char)RGB_G,  (unsigned char)RGB_B });
    SDL_Texture* pFontsTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), pFontsSurface);
    
    SDL_Rect demesionRect = { x,y, width, height };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), pFontsTexture, NULL, &demesionRect);
    SDL_FreeSurface(pFontsSurface);
    SDL_DestroyTexture(pFontsTexture);
}
void FontsManager::DrawBreakLine(std::string id, int x, int y, int width, int height, std::string text, int RGB_R, int RGB_G, int RGB_B, int warpLength)
{
    SDL_Surface* pSurface = TTF_RenderText_Solid_Wrapped(m_pFontsMap[id], text.c_str(), { (unsigned char)RGB_R, (unsigned char)RGB_G,  (unsigned char)RGB_B }, warpLength);
    SDL_Texture* pTexture = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRenderer(), pSurface);

    SDL_Rect demesionRect = { x,y, width, height };
    SDL_RenderCopy(Engine::GetInstance()->GetRenderer(), pTexture, NULL, &demesionRect);
    SDL_FreeSurface(pSurface);
    SDL_DestroyTexture(pTexture);
}

std::string FontsManager::ConvertFloatToString_Lesser(float num, int displayNum)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(displayNum) << num;
    std::string s = stream.str();
    return s;
}

void FontsManager::Clean()
{
    std::map<std::string, TTF_Font*>::iterator it;
    for (it = m_pFontsMap.begin(); it != m_pFontsMap.end(); ++it)
    {
        TTF_CloseFont(it->second);
    }
    m_pFontsMap.clear();
    //std::map<std::string, TTF_Font*>().swap(m_pFontsMap);
}