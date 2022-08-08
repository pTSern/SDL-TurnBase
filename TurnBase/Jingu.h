#pragma once
#pragma once
#include "Champion.h"
#include "GameObjectFactory.h"
class Jingu : public Champion
{
public:
	Jingu(const Properties* pProperties);
	//virtual ~Jingu();
	virtual void Draw();
	virtual void Update(float dt);
	virtual void Clean();
	//virtual void Load(const Properties* prosperties);
	virtual float GetHit(Champion* attacker, CharacterSpell* DMG_Receive);

protected:
	virtual bool DoAttack();
	virtual bool DoSkill_1();
	virtual bool DoSkill_2();
	virtual void DoPassTurn();
	virtual bool DoUltimateSkill();
	virtual void SetTarget();
	virtual void ResetSkill();
	virtual void SetSkillDetail();
};


