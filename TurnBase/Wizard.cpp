#include "Wizard.h"
static Register<Wizard> s_register("WIZARD");
Wizard::Wizard(const Properties* pProperties) : Champion(pProperties)
{
	m_Att = new CharacterAttributes("WIZARD", 10, 20, 3, 15, 2, 0, 2);

	m_DmgDealer[NORMAL_ATTACK] = new CharacterSpell(this->m_Att->m_ATK, this->m_Att->m_ATK * 0.2, 0, 0, false, true, 0, 0, 0);
	m_DmgDealer[SKILL_1] = new CharacterSpell(0, 2, 0, 0, false, true, 2, 0, 0);
	m_DmgDealer[SKILL_2] = new CharacterSpell(0, 5, 0, 0, false, true, 2, 0, 5);
	m_DmgDealer[SP_SKILL] = new CharacterSpell(0, 2, 0, 0, false, true, 2, 0, 10);
	m_DmgDealer[PASS_TURN] = new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, -3);
	SetSkillDetail();
	SoundManager::GetInstance()->LoadSoundEffect("wz_atk", "sound/Wizard/wz atk.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("wz_pre", "sound/Wizard/wz pre.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("wz_s1", "sound/Wizard/wz skill 1.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("wz_s2", "sound/Wizard/wz skill 2.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("wz_sp", "sound/Wizard/wz sp skill.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("wz_pt", "sound/Wizard/wz pt.ogg");
}
bool Wizard::DoAttack()
{
	//Wizard deal mg dmg = her 20% phy dmg
	switch (m_nDice)
	{
	case 1://Wizard deal 50% her phy dmg, restore 20% her current AP
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.5;
		m_Att->m_AP *= 1.2;
		break;
	case 3://Wizard increase her spell amp by 5
		m_Att->m_SP_Amp += 5;
		break;
	case 5://Wizard need 3 AP to do this. Wizard inscre her spell amp by her 20% current AP
		if (m_Att->m_AP < 3) return false;
		m_Att->m_SP_Amp += (m_Att->m_AP*0.2);
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 3;
		break;
	case 6://Wizard deal 50% her phy dmg, restore 2 AP
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.5;
		m_Att->m_AP += 2;
		break;
	default:
		break;
	}
	m_Att->m_AP -= m_DmgDealer[NORMAL_ATTACK]->m_APCost;
	m_frameCount = 13;
	SoundManager::GetInstance()->PlaySoundEffect("wz_pre");
	SoundManager::GetInstance()->PlaySoundEffect("wz_atk");
	Champion::DoAttack();
	//delete m_DmgDealer[NORMAL_ATTACK];
	return true;
}
bool Wizard::DoSkill_1()
{
	switch (m_nDice)
	{
	case 1://Wizard deal 50% her phy dmg, restore 20% her current AP
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.5;
		m_Att->m_AP *= 1.2;
		break;
	case 3://Wizard increase her spell amp by 5
		m_Att->m_SP_Amp += 5;
		break;
	case 5://Wizard need 3 AP to do this. Wizard inscre her spell amp by her 20% current AP
		if (m_Att->m_AP < 3) return false;
		m_Att->m_SP_Amp += (m_Att->m_AP * 0.2);
		m_DmgDealer[SKILL_1]->m_APCost += 3;
		break;
	case 6://Wizard deal 50% her phy dmg, restore 2 AP
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.5;
		m_Att->m_AP += 2;
		break;
	default:
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_1]->m_APCost;
	m_frameCount = 18;
	SoundManager::GetInstance()->PlaySoundEffect("wz_s1");
	Champion::DoSkill_1();
	return true;
}
bool Wizard::DoSkill_2()
{
	m_Att->m_AP -= m_DmgDealer[SKILL_2]->m_APCost;
	m_frameCount = 15;
	SoundManager::GetInstance()->PlaySoundEffect("wz_s2");
	Champion::DoSkill_2();
	return true;
}
bool Wizard::DoUltimateSkill()
{
	m_Att->m_AP -= m_DmgDealer[SP_SKILL]->m_APCost;
	m_frameCount = 15;
	SoundManager::GetInstance()->PlaySoundEffect("wz_sp");
	Champion::DoUltimateSkill();
	return true;
}
void Wizard::DoPassTurn()
{
	SoundManager::GetInstance()->PlaySoundEffect("wz_pt");
	Champion::DoPassTurn();
}
float Wizard::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetHit(attacker, DMG_Receive);
}

void Wizard::Draw()
{
	Champion::Draw();
}
void Wizard::Update(float dt)
{
	Champion::Update(dt);
}
void Wizard::Clean()
{
	Champion::Clean();
}
void Wizard::ResetSkill()
{

}
void Wizard::SetSkillDetail()
{

}
void Wizard::SetTarget()
{
	Champion::SetTarget();
}

