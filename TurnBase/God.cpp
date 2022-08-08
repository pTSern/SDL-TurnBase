#include "God.h"
static Register<God> s_register("GOD");
God::God(const Properties* pProperties) : Champion(pProperties)
{
	m_Att = new CharacterAttributes("GOD", 15, 16, 4, 0, 2, 10, 3, 0);

	m_DmgDealer[NORMAL_ATTACK] = new CharacterSpell(this->m_Att->m_ATK * 0.5, this->m_Att->m_ATK * 0.5, 0, 0, false, true, 0, 0, 0);
	m_DmgDealer[SKILL_1] = new CharacterSpell(this->m_Att->m_ATK * 0.5, this->m_Att->m_ATK * 0.5, 0, 0, false, true, 3, 0, 2);
	m_DmgDealer[SKILL_2] = new CharacterSpell(this->m_Att->m_ATK * 0.5, this->m_Att->m_ATK * 0.5, 0, 0, false, true, 3, 0, 3);
	m_DmgDealer[SP_SKILL] = new CharacterSpell(0, 0, 0, 0, false, true, 7, 0, 7);
	m_DmgDealer[PASS_TURN] = new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, -3);
	SetSkillDetail();

	SoundManager::GetInstance()->LoadSoundEffect("god_atk", "sound/God/god atk.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("god_pre", "sound/God/god pre.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("god_s1", "sound/God/god skill 1.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("god_s2", "sound/God/god skill 2.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("god_sp", "sound/God/god sp skill.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("god_pt", "sound/God/god pt.ogg");
}
bool God::DoAttack()
{
	//God deal physic dmg =  50% his atk and magic damage = 50% his atk
	switch (m_nDice)
	{
	case 1: //God need more than 3 AP to do this. He deal 120% physic dmg and Penetration = his enymy's armor
		if (m_Att->m_AP < 3) return false;
		m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 1.2;
		m_DmgDealer[NORMAL_ATTACK]->m_ArmorPen = m_pTeam_Defender[m_DmgDealer[NORMAL_ATTACK]->m_TargetPos]->GetAttributes()->m_ARMOR;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 3;
		break;
	case 2: //God need 5 AP to do this. God deal more magic dmg equal to 30% his current mana.
		if (m_Att->m_AP < 5)
		m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg += m_Att->m_AP * 0.3;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 5;
		break;
	//case 3: //God deal 60% his physic dmg, but healing 30% his phy dmg
	//	m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.6;
	//	m_Att->m_HP += 0.3 * m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg;
	//	break;
	//case 6: //God deal 40% his magic dmg, but restore 2 AP
	//	m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg *= 0.4;
	//	m_Att->m_AP += 2;
	//	break;
	default:
		break;
	}
	m_Att->m_AP -= m_DmgDealer[NORMAL_ATTACK]->m_APCost;
	//Buff base on DICE
	m_frameCount = 13;
	SoundManager::GetInstance()->PlaySoundEffect("god_pre");
	SoundManager::GetInstance()->PlaySoundEffect("god_atk");
	Champion::DoAttack();
	//delete m_DmgDealer[NORMAL_ATTACK];
	return true;
}
bool God::DoSkill_1()
{
	switch (m_nDice)
	{
		case 4:
			if (m_Att->m_AP < m_DmgDealer[SKILL_1]->m_APCost + 2) return false;
			m_DmgDealer[SKILL_1]->m_MagicDmg += m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP * 0.2;
			m_DmgDealer[NORMAL_ATTACK]->m_APCost += 2;
			break;
		case 6:
			if (m_Att->m_AP < m_DmgDealer[SKILL_1]->m_APCost + 2) return false;
			m_DmgDealer[SKILL_1]->m_PhysicDmg += m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP * 0.2;
			m_DmgDealer[NORMAL_ATTACK]->m_APCost += 2;
			break;
		default:
			if (m_Att->m_AP < m_DmgDealer[SKILL_1]->m_APCost) return false;
			m_DmgDealer[SKILL_1]->m_PhysicDmg += m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP * 0.08;
			m_DmgDealer[SKILL_1]->m_MagicDmg += m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP * 0.08;
			break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_1]->m_APCost;
	m_frameCount = 17;
	SoundManager::GetInstance()->PlaySoundEffect("god_s1");
	Champion::DoSkill_1();
	return true;
}
bool God::DoSkill_2()
{
	switch (m_nDice)
	{
	default:
		if (m_Att->m_AP < m_DmgDealer[SKILL_2]->m_APCost) return false;
		m_Att->m_AP += 0.5 * m_DmgDealer[SKILL_2]->m_MagicDmg;
		m_Att->m_HP += 0.5 * m_DmgDealer[SKILL_2]->m_PhysicDmg;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_2]->m_APCost;
	m_frameCount = 15;
	SoundManager::GetInstance()->PlaySoundEffect("god_s2");
	Champion::DoSkill_2();
	return true;
}
bool God::DoUltimateSkill()
{
	switch (m_nDice)
	{
	default:
		if (m_Att->m_AP < m_DmgDealer[SP_SKILL]->m_APCost) return false;
		m_DmgDealer[SP_SKILL]->m_PhysicDmg = m_Att->m_HP * 0.3;
		m_DmgDealer[SP_SKILL]->m_MagicDmg = m_Att->m_AP * 0.3;
		m_Att->m_AP = m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_AP;
		m_Att->m_HP = m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_HP;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SP_SKILL]->m_APCost;
	m_frameCount = 18;
	SoundManager::GetInstance()->PlaySoundEffect("god_sp");
	Champion::DoUltimateSkill();
	return true;
}
void God::DoPassTurn()
{
	m_frameCount = 14;
	m_Att->m_AP += 3;
	SoundManager::GetInstance()->PlaySoundEffect("god_pt");
	Champion::DoPassTurn();
}
float God::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetHit(attacker, DMG_Receive);
}

void God::Draw()
{
	Champion::Draw();
}
void God::Update(float dt)
{
	Champion::Update(dt);
}
void God::Clean()
{
	Champion::Clean();
}
void God::ResetSkill()
{
	m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg = m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg = m_Att->m_ATK * 0.5;
	m_DmgDealer[NORMAL_ATTACK]->m_APCost = 0;

	m_DmgDealer[SKILL_1]->m_PhysicDmg = m_DmgDealer[SKILL_1]->m_MagicDmg = m_Att->m_ATK * 0.5;
	m_DmgDealer[SKILL_1]->m_APCost = 2;

	m_DmgDealer[SKILL_2]->m_PhysicDmg = m_DmgDealer[SKILL_2]->m_MagicDmg = m_Att->m_ATK * 0.5;
	m_DmgDealer[SKILL_2]->m_APCost = 3;

	m_DmgDealer[SP_SKILL]->m_APCost = 7;
	m_DmgDealer[SP_SKILL]->m_PhysicDmg = m_DmgDealer[SP_SKILL]->m_MagicDmg = 0;

	m_DmgDealer[PASS_TURN]->m_APCost = -3;
}
void God::SetSkillDetail()
{
	m_DmgDealer[NORMAL_ATTACK]->m_explain =
		"Deal magic and physic damage to enemy."
		"\n> Default: Deal physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + "[=50% his ATK], "
		"Deal magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + "[=50 % his ATK]."
		". AP Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2)
		+ "\n> Dice 1: Deal physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5 * 1.2, 2) + "[=120% of 50% his ATK], "
		"Deal default magic dmg. " "Armor Penetration = his target armor"
		". AP Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 3"
		+ "\n> Dice 2: Deal magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5 * 1.2, 2) + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_AP * 0.3, 2) + "[=30% his current AP], "
		"Deal default physic dmg."
		". AP Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 5";
	
	if (m_pTeam_Defender.size() != NULL)
	{
		m_DmgDealer[SKILL_1]->m_explain =
			"Deal magic and physic damage to enemy."
			"\n> Default: Deal physic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP * 0.08, 2) + "[8% target's HP])"
			+ ". Deal magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP * 0.08, 2) + "[8% target's AP])"
			". AP Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2)
			+ "\n> Dice 4: Deal magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP * 0.08, 2) + "[20% target's AP])"
			+ ". Deal default physic dmg"
			". AP Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2) + " + 2)"
			+ "\n> Dice 6: Deal physic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP * 0.08, 2) + "[20% target's HP])"
			+ ". Deal default magic dmg" 
			". AP Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2) + " + 2)"
			;
	}
	m_DmgDealer[SKILL_2]->m_explain =
		"Deal magic and physic damage to enemy."
		"\n> Default: Deal physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + "[=50% his ATK], "
		"Deal magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5, 2) + "[=50 % his ATK]."
		"\n Heal HP & AP= " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_ATK * 0.5*0.5, 2) +
		". AP Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2);

	m_DmgDealer[SP_SKILL]->m_explain =
		"Swap his Hp and AP to enemy. Deal Physic and Magic dmg to enemy"
		"\n Physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_HP * 0.3, 2) + "[=50% his current HP]"
	    "\n Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_AP * 0.3, 2) + "[=50% his current AP]"
		"\n AP Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2);
}
void God::SetTarget()
{
	Champion::SetTarget();
}

