#include "Mage.h"
static Register<Mage> s_register("MAGE");
Mage::Mage(const Properties* pProperties) : Champion(pProperties)
{
	m_Att = new CharacterAttributes("MAGE", 10, 20, 3, 15, 2, 0, 2);
	m_DmgDealer[NORMAL_ATTACK] = new CharacterSpell(0, this->m_Att->m_ATK * 0.8, 0, 0, false, true, 0, 0, 0);
	m_DmgDealer[SKILL_1] = new CharacterSpell(0, 0, 0, 0, false, m_DmgDealer[SKILL_1]->m_IsReady, 2, 0, 3);
	m_DmgDealer[SKILL_2] = new CharacterSpell(0, 0, 0, 0, false, m_DmgDealer[SKILL_2]->m_IsReady, 5, 0, 4);
	m_DmgDealer[SP_SKILL] = new CharacterSpell(0, 2, 0, 0, false, m_DmgDealer[SP_SKILL]->m_IsReady, 5, 0, 5);
	m_DmgDealer[PASS_TURN] = new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, -3);
	// Init Skill's explain
	SetSkillDetail();
	// Init champion's sound effect
	SoundManager::GetInstance()->LoadSoundEffect("mage_atk", "sound/Mage/mage atk.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("mage_pre", "sound/Mage/mage pre.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("mage_s1", "sound/Mage/mage skill 1.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("mage_s2", "sound/Mage/mage skill 2.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("mage_sp", "sound/Mage/mage sp skill.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("mage_pt", "sound/Mage/mage pt.ogg");
}
bool Mage::DoAttack()
{
	switch (m_nDice)
	{
	case 1: //Mage need 2 Ap to do this. He gain 40% magic penetration
		if (m_Att->m_AP < 2) return false;
		m_DmgDealer[NORMAL_ATTACK]->m_SpellPen = 40;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 1;
		break;
	case 3: //Mage need 4 AP. He deal more magic dmg = 20% his lost ap to enemy
		if (m_Att->m_AP < 4) return false;
		m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg += 0.2 * (m_Att->m_MAXAP - m_Att->m_AP);
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 3;
		break;
	case 5: //Mage need 5 AP. He deal more magic dmg = 20% his current ap to enemy
		if (m_Att->m_AP < 5) return false;
		m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg += 0.2 * m_Att->m_AP;
		m_DmgDealer[NORMAL_ATTACK]->m_APCost += 4;
		break;
	default:
		if (m_Att->m_AP < 1) return false;
		m_Att->m_AP -= 1;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[NORMAL_ATTACK]->m_APCost;
	m_frameCount = 11;
	SoundManager::GetInstance()->PlaySoundEffect("mage_pre");
	SoundManager::GetInstance()->PlaySoundEffect("mage_atk");
	Champion::DoAttack();
	//delete m_DmgDealer[NORMAL_ATTACK];
	return true;
}
bool Mage::DoSkill_1()
{
	switch (m_nDice)
	{
	case 2:
		if (m_Att->m_AP < 4) return false;
		m_DmgDealer[SKILL_1]->m_MagicDmg = 0.5*abs(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP - m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP);
		m_DmgDealer[SKILL_1]->m_APCost += 1;
		break;
	default:
		if (m_Att->m_AP < 3) return false;
		m_DmgDealer[SKILL_1]->m_MagicDmg = 0.5 * abs(m_Att->m_HP - m_Att->m_AP);
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_1]->m_APCost;
	m_frameCount = 9;
	SoundManager::GetInstance()->PlaySoundEffect("mage_s1");
	Champion::DoSkill_1();
	return true;
}
bool Mage::DoSkill_2()
{
	switch (m_nDice)
	{
	case 6:
		if (m_Att->m_AP < 6) return false;
		m_Att->m_HP += m_Att->m_AP * 0.15;
		m_Att->m_SP_Amp += 10;
		m_DmgDealer[SKILL_2]->m_APCost += 2;
		break;
	default:
		if (m_Att->m_AP < 4) return false;
		m_Att->m_HP += m_Att->m_AP * 0.3;
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_2]->m_APCost;
	m_frameCount = 9;
	SoundManager::GetInstance()->PlaySoundEffect("mage_s2");
	m_pAnimation->SetPros(m_textureID, DO_SKILL_2, m_frameCount, m_animationSpeed, m_flip);
	//Champion::DoSkill_2();
	return true;
}
bool Mage::DoUltimateSkill()
{
	//Mage deal magic dmg = 44% how his Ap much more than his target ap or how his target much more than him
	switch (m_nDice)
	{
	case 4: //Mage heal 50% his magic damge
		if (m_Att->m_AP < 9) return false;
		m_DmgDealer[SP_SKILL]->m_MagicDmg = 0.44 * abs((m_Att->m_AP - m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_AP));
		m_Att->m_HP += 0.5 * m_DmgDealer[SKILL_2]->m_MagicDmg;
		m_DmgDealer[SP_SKILL]->m_APCost += 4;
		break;
	default:
		if (m_Att->m_AP < 5) return false;
		m_DmgDealer[SP_SKILL]->m_MagicDmg = 0.44 * abs((m_Att->m_AP - m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_AP));
		break;
	}
	m_Att->m_AP -= m_DmgDealer[SP_SKILL]->m_APCost;
	m_frameCount = 15;
	SoundManager::GetInstance()->PlaySoundEffect("mage_sp");
	Champion::DoUltimateSkill();
	return true;
}
void Mage::DoPassTurn()
{
	m_frameCount = 15;
	switch (m_nDice)
	{
	case 1:
		m_Att->m_AP += m_Att->m_HP*0.2;
		m_Att->m_HP *= 0.8;
		break;
	default:
		m_Att->m_AP -= m_DmgDealer[PASS_TURN]->m_APCost;
		break;
	}
	SoundManager::GetInstance()->PlaySoundEffect("mage_sp");
	Champion::DoPassTurn();
}
float Mage::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetHit(attacker, DMG_Receive);
}

void Mage::Draw()
{
	Champion::Draw();
}
void Mage::Update(float dt)
{
	Champion::Update(dt);
}
void Mage::Clean()
{
	Champion::Clean();
}
void Mage::ResetSkill()
{
	m_DmgDealer[NORMAL_ATTACK]->m_MagicDmg = this->m_Att->m_ATK * 0.8;
	m_DmgDealer[NORMAL_ATTACK]->m_APCost = 0;
	m_DmgDealer[NORMAL_ATTACK]->m_SpellPen = 0;

	m_DmgDealer[SKILL_1]->m_APCost = 3;
	m_DmgDealer[SKILL_1]->m_MagicDmg = 0;

	m_DmgDealer[SKILL_2]->m_APCost = 4;

	m_DmgDealer[PASS_TURN]->m_APCost = -3;

	m_DmgDealer[SP_SKILL]->m_MagicDmg = 2;
	m_DmgDealer[SP_SKILL]->m_APCost = 5;
}
void Mage::SetSkillDetail()
{
	m_DmgDealer[NORMAL_ATTACK]->m_explain =
		  "Deal magic damage to enemy."
		  "\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.8, 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2)
		+ "\n> Dice 1: Gain Magic Penetration = " "40%"
		+ ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 1)"
		"\n> Dice 3: Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.8, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((m_Att->m_MAXAP - m_Att->m_AP)* 0.2, 2)
		+ "[=20% His Ap lost])" ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 3)"
		+ "\n> Dice 5: Deal Magic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.8, 2) + " + " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_AP * 0.2, 2)
		+ "[=20% Current Ap]" ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 4)";
	
	if (m_pTeam_Defender.size() != NULL)
	{
		m_DmgDealer[SKILL_1]->m_explain =
			"Deal magic damage to enemy."
			"\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.5 * abs(m_Att->m_HP - m_Att->m_AP), 2)
			+ "[=50% The difference between his current HP and current Ap]" ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2)
			+ "\n> Dice 2: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.5 * abs(m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_HP - m_pTeam_Defender[m_DmgDealer[SKILL_1]->m_TargetPos]->GetAttributes()->m_AP), 2)
			+ "[=50% The difference between target's current HP and target's current Ap]" ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2)+ " + 1)";
	}
	m_DmgDealer[SKILL_2]->m_explain =
		  "Restore HP base on his current AP"
		  "\n> Default: Restore hp = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_AP*0.3, 2)
		+ "[=30% Current AP]" ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2)
		+ "\n> Dice 6: Restore hp = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_AP * 0.15, 2)
		+ "[=15% Current AP]" ". Spell Amp + 10" ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2) + " + 2)";
	if (m_pTeam_Defender.size() != NULL)
	{
		m_DmgDealer[SP_SKILL]->m_explain =
			"Deal magic damage to enemy."
			"\n Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.44 * abs(m_Att->m_AP - m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_AP), 2)
			+ "[=44% The difference between his current AP and target current Ap]" ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2)
			+"\n Dice 4: Like Default, But he heal 50% his Magic damage dealed" ". Restore HP = " +  FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.5 * 0.44 * abs(m_Att->m_AP - m_pTeam_Defender[m_DmgDealer[SP_SKILL]->m_TargetPos]->GetAttributes()->m_AP), 2)
			+ ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2) + " + 4)";
	}
	m_DmgDealer[PASS_TURN]->m_explain =
		"Restore AP"
		"\n> Default: Restore AP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((0 - m_DmgDealer[PASS_TURN]->m_APCost), 2)
		+ "\n> Dice 1: Consumed 20% HP, Resotre AP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(0.2 * m_Att->m_HP, 2)
		+ "[=20% Current HP]";
}
void Mage::SetTarget()
{
	Champion::SetTarget();
}
