#pragma once
#include <vector>
#include <map>
#include "GameObject.h"
#include "Character.h"
#include "FontsManager.h"
#include "Input.h"
const int NULBER_SKILL_LAYER = 5;
const int STARTER_SKILL_LAYER_X = 328;
const int STARTER_SKILL_LAYER_Y = 563;
const int DISTANCE_S = 128;
class AdditionEffect
{
public:
	inline static AdditionEffect* GetInstance()
	{
		return s_pInstance = (s_pInstance != nullptr) ? s_pInstance : new AdditionEffect();
	}
	void LoadSkillLayer(std::string textureID);
	void DrawSkillLayer(std::string textureID, std::vector<CharacterSpell*> DmgDealer);
	void DrawSkillInformation(int x, int y, CharacterSpell* DmgDealer);

	void DrawFontsAttributes(CharacterAttributes* Att);

	void DrawForceOfDice(int diceNum);

	void DrawFontsCD(std::vector<CharacterSpell*> DmgDealer);

	void DrawHeathAPBar(CharacterAttributes* Att, int x, int y);
	void DrawTarget(int x, int y);
	void Clean();
private:
	AdditionEffect() {};
	static AdditionEffect* s_pInstance;
	std::map<std::string, std::vector<GameObject*>> m_skillLayer;
	std::map<std::string, std::vector<Animation*>> m_xskillLayer;
};