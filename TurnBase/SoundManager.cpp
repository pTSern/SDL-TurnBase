#include "SoundManager.h"
SoundManager* SoundManager::s_pInstance = nullptr;

SoundManager::SoundManager()
{
	if (Mix_OpenAudio(FREQ, MIX_DEFAULT_FORMAT, 2, CHUNK_SIZE) < 0)
	{
		SDL_Log("Could not Init SDL_mixer.h, Error: %s", Mix_GetError());
	}
}

void SoundManager::PlayMusic(std::string id)
{
	if (Mix_PlayMusic(m_pMusicMap[id], -1) == -1)
	{
		SDL_Log("Could not play music. ID: %s", id.c_str());
		SDL_Log("Message: %s", Mix_GetError());
	}
}
bool SoundManager::LoadMusic(std::string id, std::string fileName)
{
	Mix_Music* pMusic = Mix_LoadMUS(fileName.c_str());
	if (pMusic == nullptr)
	{
		SDL_Log("Could not load music: %s at %s", id.c_str(), fileName.c_str());
		SDL_Log("Message: %s", Mix_GetError());
		return false;
	}
	m_pMusicMap[id] = pMusic;
	return true;
}

void SoundManager::PlaySoundEffect(std::string id)
{
	if (Mix_PlayChannel(-1, m_pSoundEffectMap[id], 0) == -1)
	{
		SDL_Log("Could not play sound effect. ID: %s", id.c_str());
		SDL_Log("Message: %s", Mix_GetError());
	}
}

bool SoundManager::LoadSoundEffect(std::string id, std::string fileName)
{
	Mix_Chunk* pEffect = Mix_LoadWAV(fileName.c_str());
	if (pEffect == nullptr)
	{
		SDL_Log("Could not load music: %s at %s", id.c_str(), fileName.c_str());
		SDL_Log("Message: %s", Mix_GetError());
		return false;
	}
	m_pSoundEffectMap[id] = pEffect;
	return true;
}

void SoundManager::Clean()
{

	for (auto it = m_pMusicMap.begin(); it != m_pMusicMap.end(); it++)
	{
		Mix_FreeMusic(it->second);
	}
	for (auto it = m_pSoundEffectMap.begin(); it != m_pSoundEffectMap.end(); it++)
	{
		Mix_FreeChunk(it->second);
	}
	m_pMusicMap.clear();
	m_pSoundEffectMap.clear();

}
void SoundManager::CleanSoundEffect()
{
	for (auto it = m_pSoundEffectMap.begin(); it != m_pSoundEffectMap.end(); it++)
	{
		Mix_FreeChunk(it->second);
	}
	m_pSoundEffectMap.clear();
}
