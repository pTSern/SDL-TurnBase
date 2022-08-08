#include "Samurai.h"
static Register<Samurai> s_register("SAMURAI");
Samurai::Samurai(const Properties* pProperties) : Champion(pProperties)
{
	// Init champion's attributes
	m_Att = new CharacterAttributes("SAMURAI", 18, 6, 5, 0, 4, 0, 7, 0);
	// Init skill
	m_DmgDealer[NORMAL_ATTACK] = new CharacterSpell(this->m_Att->m_ATK, 0, 0, 0, false, true, 0, 0, 0);
	m_DmgDealer[SKILL_1] = new CharacterSpell(0, 2, 0, 0, false, true, 2, 0, 2);
	m_DmgDealer[SKILL_2] = new CharacterSpell(0, 3, 0, 0, false, true, 3, 0, 2);
	m_DmgDealer[SP_SKILL] = new CharacterSpell(0, 2, 0, 0, false, true, 5, 0, 3);
	m_DmgDealer[PASS_TURN] = new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, -2);
	// Init Skill's explain
	SetSkillDetail();
	// Init champion's sound effect
	SoundManager::GetInstance()->LoadSoundEffect("sam_atk", "sound/Samurai/sam atk.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("sam_pre", "sound/Samurai/sam pre.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("sam_s1", "sound/Samurai/sam skill 1.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("sam_s2", "sound/Samurai/sam skill 2.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("sam_sp", "sound/Samurai/sam sp skill.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("sam_pt", "sound/Samurai/sam pt.ogg");
}
bool Samurai::DoAttack()
{
	//Reset
	
	//m_DmgDealer[NORMAL_ATTACK]->m_TargetPos = AutoSetTarget();

	switch (m_nDice)
	{
	case 2: // Samurai need more than 1 AP to do this. He deal more 2 damage then reduce 1 AP
		if (m_Att->m_AP < 1) return false; 
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg += 2;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 1 ;
		break;
	case 3: // Samurai restore 1 Ap but deal 80% his phy dmg
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.8;
		m_Att->m_AP += 1;
		break;
	case 4: // Samurai need more than 1 AP to do this. He deal more 2 damage then reduce 1 AP
		if (m_Att->m_AP < 1) return false;
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg += 2;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 1;
		break;
	case 5:// Samurai restore 1 Ap but deal 80% his phy dmg
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.8;
		m_Att->m_AP += 1;
		break;
	default: //Samurai deal his phy dmg to target
		break;
	}
	//Set attack animation
	m_frameCount = 10 ;
	//Reduce champion AP
	m_Att->m_AP -= m_DmgDealer[NORMAL_ATTACK]->m_APCost;
	//Turn on sound
	SoundManager::GetInstance()->PlaySoundEffect("sam_pre");
	SoundManager::GetInstance()->PlaySoundEffect("sam_atk");
	//Call CHAMPION's acction
	Champion::DoAttack();
	return true;
}
bool Samurai::DoSkill_1()
{
	//Reset
	

	switch (m_nDice)
	{
	case 3:
		if (m_Att->m_AP < 2) return false;
		m_DmgDealer[SKILL_1]->m_MagicDmg += 2;
		break;
	case 1:
		if (m_Att->m_AP < 3) return false;
		m_DmgDealer[SKILL_1]->m_MagicDmg += (0.8*m_Att->m_ATK);
		m_DmgDealer[SKILL_1]->m_APCost += 1;
		break;
	default:
		if (m_Att->m_AP < 2) return false;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_1]->m_APCost;
	m_frameCount = 13;
	SoundManager::GetInstance()->PlaySoundEffect("sam_s1");
	Champion::DoSkill_1();
	return true;
}
bool Samurai::DoSkill_2()
{
	
	switch (m_nDice)
	{
	case 2:
		if (m_Att->m_AP < 2) return false;
		m_Att->m_HP *= 0.9;
		m_DmgDealer[SKILL_2]->m_MagicDmg += m_Att->m_HP*0.2;
		break;
	case 4:
		if (m_Att->m_AP < 4) return false;
		m_DmgDealer[SKILL_2]->m_MagicDmg += m_DmgDealer[SKILL_2]->m_MagicDmg * (m_DmgDealer[SKILL_2]->m_TargetPos*0.4);
		m_DmgDealer[SKILL_2]->m_APCost += 2;
		break;
	default:
		if (m_Att->m_AP < 2) return false;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_2]->m_APCost;
	m_frameCount = 7;
	SoundManager::GetInstance()->PlaySoundEffect("sam_s2");
	Champion::DoSkill_2();
	return true;
}
bool Samurai::DoUltimateSkill()
{
	//Reset 
	

	switch (m_nDice)
	{
	case 1:
		if (m_Att->m_AP < 5) return false; 
		m_Att->m_HP *= 0.5;
		m_Att->m_ATK += m_Att->m_HP*0.45;
		m_DmgDealer[SP_SKILL]->m_MagicDmg += 2;
		m_DmgDealer[SP_SKILL]->m_APCost += 3;
		break;
	default:
		if (m_Att->m_AP < 3)  return false; 
		m_DmgDealer[SP_SKILL]->m_MagicDmg += m_Att->m_ATK;
		break;
	}

	m_Att->m_AP -= m_DmgDealer[SP_SKILL]->m_APCost;
	m_frameCount = 18;
	SoundManager::GetInstance()->PlaySoundEffect("sam_sp");
	Champion::DoUltimateSkill();
	return true;
}
void Samurai::DoPassTurn()
{
	switch (m_nDice)
	{
	case 1:
		m_Att->m_HP *= 1.2;
		break;
	default:
		m_Att->m_AP -= m_DmgDealer[PASS_TURN]->m_APCost;
		break;
	}
	m_frameCount = 13;
	SoundManager::GetInstance()->PlaySoundEffect("sam_pt");
	Champion::DoPassTurn();
}
float Samurai::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetHit(attacker, DMG_Receive);
}
float Samurai::GetSpell(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetSpell(attacker, DMG_Receive);
}
void Samurai::Draw()
{
	Champion::Draw();
}
void Samurai::Update(float dt)
{
	Champion::Update(dt);
}
void Samurai::Clean()
{
	Champion::Clean();
}
void Samurai::ResetSkill()
{
	m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg = this->m_Att->m_ATK;
	m_DmgDealer[NORMAL_ATTACK]->m_APCost = 0;


	m_DmgDealer[SKILL_1]->m_MagicDmg = 2;
	m_DmgDealer[SKILL_1]->m_APCost = 2;

	m_DmgDealer[SKILL_2]->m_MagicDmg = 3;
	m_DmgDealer[SKILL_2]->m_APCost = 2;

	m_DmgDealer[SP_SKILL]->m_MagicDmg = 2;
	m_DmgDealer[SP_SKILL]->m_APCost = 3;

	m_DmgDealer[PASS_TURN]->m_APCost = -2;
	//for (int i = NORMAL_ATTACK; i < PASS_TURN + 1; i++)
	//{
	//	delete m_DmgDealer[i];
	//}
	
}
void Samurai::SetSkillDetail()
{
	m_DmgDealer[NORMAL_ATTACK]->m_explain =
		  "Deal physic damage to enemy."
		  "\n> Default: Deal Physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK, 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2)
		+ "\n> Dice 2/4: Deal Physic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK, 2) + " + 2)"
		+ ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 1)"
		  "\n> Dice 3/5: Deal 80% Physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.8, 2)
		+ ". Restore: 1 Ap";

	m_DmgDealer[SKILL_1]->m_explain =
		  "Deal magic damage to enemy."
		  "\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_MagicDmg, 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2)
		+ "\n> Dice 1: Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_MagicDmg, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.8, 2)
		+ "[=80% Current ATK]). Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2) + " + 1)"
		+ "\n> Dice 3: Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_MagicDmg, 2) + " + 2)"
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2);

	m_DmgDealer[SKILL_2]->m_explain =
	   	  "Deal magic damage to enemy."
		  "\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_MagicDmg, 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2)
		+ "\n> Dice 2: Consume 50% current HP. Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_MagicDmg, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_HP * 0.2 * 0.9, 2)
		+ "[=20% * 90% current HP])" ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2)
		+ "\n> Dice 4: Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_MagicDmg, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_TargetPos * 0.4 * m_DmgDealer[SKILL_2]->m_MagicDmg, 2)
		+ "[=Pos of Enemy * 40% * base magic dmg])" ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2) + " + " + " 2)";
	
	m_DmgDealer[SP_SKILL]->m_explain =
		  "Deal magic damage to enemy."
		  "\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_MagicDmg, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK, 2)
		+ "[=Current ATK]. Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2)
		+ "\n> Dice 1: Consume 50% current HP. Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_MagicDmg, 2) + " + 2. "
		+ "Increase ATK = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.5 * 0.45 * m_Att->m_HP, 2) + "[=45% HP affter consumed]"
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2) + " + 3";

	m_DmgDealer[PASS_TURN]->m_explain =
		  "Restore AP or HP"
		  "\n> Default: Restore AP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((0 - m_DmgDealer[PASS_TURN]->m_APCost), 2)
		+ "\n> Dice 1: Resotre HP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.2 * m_Att->m_HP,2)
		+ "[=20% Current HP]";
}
void Samurai::SetTarget()
{
	Champion::SetTarget();
}
