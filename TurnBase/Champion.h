#pragma once
#include "Character.h"
#include "Animation.h"
#include "RigidBody.h"
#include "Dice.h"
#include <vector>
#include <map>
#include "SoundManager.h"
#include "AdditionEffect.h"
#include "ChampionExtention.h"
#include "FontsManager.h"

const int NUMBER_OF_TEAM  = 2;
const int NUMBER_OF_CHAMPION_IN_A_TEAM = 2;
const float BALANCE_NUMBER = 0.06;

class Champion :public Character
{
public:
	Champion(const Properties* pProperties);

	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	virtual float GetHit(Champion* attacker, CharacterSpell* DMG_Receive);
	virtual float GetSpell(Champion* attacker, CharacterSpell* DMG_Receive);

	void AfterEnemyGetDamage(int index);
	void SetAttackTeam(std::vector<Champion*> pTeam_Attacker) { m_pTeam_Attacker = pTeam_Attacker; };
	void SetDefendTeam(std::vector<Champion*> pTeam_Defender) { m_pTeam_Defender = pTeam_Defender; };
	inline std::string GetName() { return m_Att->m_Name; };
	inline float GetSPD() { return m_Att->m_SPD; }
	void UpdateAnimation() { m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip); };
	void InitAdditionProperties() 
	{ 
		AdditionEffect::GetInstance()->LoadSkillLayer(m_textureID);
		m_pAdditionProperties = new Properties(m_pTransform->X, m_pTransform->Y, m_width, m_height, m_frameCount, m_textureID, m_flip);
		m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);
	};
	inline CharacterAttributes* GetAttributes() { return m_Att; }

	struct SortManager
	{
		inline bool operator() (const Champion* lhs, const Champion* rhs)
		{
			return lhs->m_Att->m_SPD > rhs->m_Att->m_SPD;
		}
	};
protected:
	virtual bool DoAttack();
	virtual bool DoSkill_1();
	virtual bool DoSkill_2();
	virtual void DoPassTurn();
	virtual bool DoUltimateSkill();
	virtual void SetTarget();
	virtual void ResetSkill() = 0;
	virtual void SetSkillDetail() = 0;

	int AutoSetTarget(); //auto set new target if current target is dead

	std::vector<Champion*> m_pTeam_Attacker; //Create attacker team
	std::vector<Champion*> m_pTeam_Defender; //Create defender team
	int m_nDice; //store dice number
private:
	void AutoCheck_IsDead(); //auto check if champion is dead
	
	void AutoSetStatus(); //auto recaculate status turn, then effect the right status to champion
	void ReadKey_DoSkill(); //read key to do skill
	void AutoEffectStatus(); //Auto effect status 
	void AutoSkillCoolDown();
	void AttackEnemy(int attackType, int attackAnimation);
	const Properties* m_pAdditionProperties; //store beginer properties
	void ResetProperties();
	void MouseEvent();

	int p_nAttackType, p_nDoAction;
	bool p_bCastSence, p_bPassturn; //if champion is casting an animation
	float p_nPhyDmgRecive, p_nMgDmgRecive;
};

