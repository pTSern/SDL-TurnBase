#pragma once
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>

#define FREQ 44100
#define CHUNK_SIZE 2048

class SoundManager
{
public:
	inline static SoundManager* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new SoundManager();
	}
	void Clean();
	void CleanSoundEffect();
	void PlayMusic(std::string id);
	bool LoadMusic(std::string id, std::string fileName);

	void PlaySoundEffect(std::string id);
	bool LoadSoundEffect(std::string id, std::string fileName);
private:
	SoundManager();
	static SoundManager* s_pInstance;
	std::map<std::string, Mix_Music*> m_pMusicMap;
	std::map<std::string, Mix_Chunk*> m_pSoundEffectMap;

};

