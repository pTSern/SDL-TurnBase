#include "AdditionEffect.h"
AdditionEffect* AdditionEffect::s_pInstance = nullptr;
void AdditionEffect::LoadSkillLayer(std::string textureID)
{
	for (int i = 0; i < NULBER_SKILL_LAYER; i++)
	{
		m_skillLayer[textureID].push_back(new GameObject(new Properties(STARTER_SKILL_LAYER_X + (i * DISTANCE_S), STARTER_SKILL_LAYER_Y, 168, 168, NULBER_SKILL_LAYER, textureID, SDL_FLIP_NONE, 0, 0, 9, i)));
	}
}
void AdditionEffect::DrawSkillLayer(std::string textureID, std::vector<CharacterSpell*> DmgDealer)
{
	for (int i = 0; i < (m_skillLayer[textureID]).size(); i++)
	{
		m_skillLayer[textureID][i]->Draw();
		if (i < (m_skillLayer[textureID]).size() - 1) FontsManager::GetInstance()->Draw("minecraft", STARTER_SKILL_LAYER_X + (i * DISTANCE_S) + 16, STARTER_SKILL_LAYER_Y + 40, 48,  24, "> " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(DmgDealer[i]->m_APCost, 2), 150, 150, 250);
	}
}
void AdditionEffect::DrawFontsAttributes(CharacterAttributes* Att)
{
	FontsManager::GetInstance()->Draw("minecraft", 255, 525, Att->m_Name.length() * 32, 32, Att->m_Name, 250, 250, 250);

	FontsManager::GetInstance()->Draw("minecraft", 267, 666, 288, 32, std::to_string(Att->m_HP) + "/" + std::to_string(Att->m_MAXHP), 150, 250, 150);
	FontsManager::GetInstance()->Draw("minecraft", 685, 666, 288, 32, std::to_string(Att->m_AP) + "/" + std::to_string(Att->m_MAXAP), 150, 150, 250);

	FontsManager::GetInstance()->Draw("minecraft", 55, 529, 48, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(Att->m_ATK, 2), 250, 250, 250);
	FontsManager::GetInstance()->Draw("minecraft", 55, 568, 48, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(Att->m_SP_Amp, 2), 250, 250, 250);
	FontsManager::GetInstance()->Draw("minecraft", 55, 607, 48, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(Att->m_ARMOR, 2), 250, 250, 250);
	FontsManager::GetInstance()->Draw("minecraft", 55, 646, 48, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(Att->m_SP_Res, 2), 250, 250, 250);
	FontsManager::GetInstance()->Draw("minecraft", 55, 685, 48, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(Att->m_SPD, 2), 250, 250, 250);
	FontsManager::GetInstance()->Draw("minecraft", 55, 724, std::to_string(Att->m_LIFE + 1).length() * 16, 16, std::to_string(Att->m_LIFE + 1), 250, 250, 250);
}
void AdditionEffect::DrawForceOfDice(int diceNum)
{
	Animation* m_pForceOfDice = new Animation();
	m_pForceOfDice->SetPros("force_dice", 1, 1, 80, SDL_FLIP_NONE);
	m_pForceOfDice->Draw(247, 740, diceNum, 16);
	delete m_pForceOfDice;
}

void AdditionEffect::DrawFontsCD(std::vector<CharacterSpell*> DmgDealer)
{
	for (int i = 0; i < DmgDealer.size(); i++)
	{
		if (!DmgDealer[i]->m_IsReady) FontsManager::GetInstance()->Draw("minecraft", STARTER_SKILL_LAYER_X + 8 + (i * DISTANCE_S), STARTER_SKILL_LAYER_Y + 8, 48, 48, std::to_string(DmgDealer[i]->m_CD + 1), 250, 10, 10);
	}
}

void AdditionEffect::DrawHeathAPBar(CharacterAttributes* Att, int x, int y)
{
	Animation* pBackHeathBar = new Animation();
	Animation* pFrontHeathBar = new Animation();
	pBackHeathBar->SetPros("heath_bar", 1, 1, 10, SDL_FLIP_NONE);
	pFrontHeathBar->SetPros("heath_bar", 2, 1, 10, SDL_FLIP_NONE);
	pBackHeathBar->Draw(x, y + 2, 100, 12);
	pFrontHeathBar->Draw(x, y + 2, 100*(Att->m_HP / Att->m_MAXHP), 12);

	delete pBackHeathBar;
	delete pFrontHeathBar;

	Animation* pBackAPBar = new Animation();
	Animation* pFrontAPBar = new Animation();
	pBackAPBar->SetPros("ap_bar", 1, 1, 10, SDL_FLIP_NONE);
	pFrontAPBar->SetPros("ap_bar", 2, 1, 10, SDL_FLIP_NONE);
	pBackAPBar->Draw(x, y + 12 + 2, 100, 6);
	pFrontAPBar->Draw(x, y + 12 + 2, 100 * (Att->m_AP / Att->m_MAXAP), 6);

	delete pBackAPBar;
	delete pFrontAPBar;
}
void AdditionEffect::DrawTarget(int x, int y)
{
	Animation* m_pTarget = new Animation();
	m_pTarget->SetPros("target", 1, 1, 10, SDL_FLIP_NONE);
	m_pTarget->Draw(x, y, 168, 168);
	delete m_pTarget;
}
void AdditionEffect::DrawSkillInformation(int x, int y, CharacterSpell* DmgDealer)
{
	Animation* pSkill_Infor_Bg = new Animation();
	pSkill_Infor_Bg->SetPros("skill_infor_bg", 1, 1, 0, SDL_FLIP_NONE);
	int l = (DmgDealer->m_explain.length() / 48 + 1) * 36;
	pSkill_Infor_Bg->Draw(x + ((512 / x) - 1)*480 + 16, y + (768/(y+l) - 1)*l, 480, (DmgDealer->m_explain.length() / 48 + 1) * 32);
	FontsManager::GetInstance()->DrawBreakLine("minecraft", x + ((512 / x) - 1) * 480 + 16, y + (768 / (y + l) - 1) * l, 480, (DmgDealer->m_explain.length() / 48 + 1) * 32, DmgDealer->m_explain, 250, 250, 250, 480);
	delete pSkill_Infor_Bg;
}
void AdditionEffect::Clean()
{
	for (auto it = m_skillLayer.begin(); it != m_skillLayer.end(); ++it)
	{
		for (int i = it->second.size()-1; i>=0; i--)
		{
			it->second[i]->Clean();
			delete it->second[i];
		}
	}
	m_skillLayer.clear();
}