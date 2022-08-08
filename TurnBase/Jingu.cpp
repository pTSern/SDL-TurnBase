#include "Jingu.h"
static Register<Jingu> s_register("JINGU");
Jingu::Jingu(const Properties* pProperties) : Champion(pProperties)
{
	m_Att = new CharacterAttributes("JINGU", 20, 10, 3, 0, 3, 0, 5);

	m_DmgDealer[NORMAL_ATTACK] = new CharacterSpell(this->m_Att->m_ATK, 0, 0, 0, false, true, 0, 0, 0);
	m_DmgDealer[SKILL_1] = new CharacterSpell(0, 0, 0, 0, false, true, 4, 0, 4);
	m_DmgDealer[SKILL_2] = new CharacterSpell(0, 0, 0, 0, false, true, 4, 0, 5);
	m_DmgDealer[SP_SKILL] = new CharacterSpell(0, this->m_Att->m_ATK*0.6, 0, 0, false, true, 5, 0, 6);
	m_DmgDealer[PASS_TURN] = new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, -2.5);
	SetSkillDetail();
	SoundManager::GetInstance()->LoadSoundEffect("ji_atk", "sound/Jingu/ji atk.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("ji_pre", "sound/Jingu/ji pre.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("ji_s1", "sound/Jingu/ji skill 1.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("ji_s2", "sound/Jingu/ji skill 2.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("ji_sp", "sound/Jingu/ji sp skill.ogg");
	SoundManager::GetInstance()->LoadSoundEffect("ji_pt", "sound/Jingu/ji pt.ogg");
}

bool Jingu::DoAttack()
{
	switch (m_nDice)
	{
		case 1://Jingu need 2 AP to do this. He deal more 2 physic dmg then resotre hp = 30% his physic dmg
			if (m_Att->m_AP < 2) return false;
			m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg += 2;
			m_Att->m_HP += m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg * 0.3;
			m_DmgDealer[NORMAL_ATTACK]->m_APCost += 2;
			break;
		case 4://Jingu need 2 AP to do this. He deal more 20% his physic dmg then resotre hp = 120% his current hp, If current HP > Max Hp. Max hp increase
			if (m_Att->m_AP < 2) return false;
			m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg *= 0.2;
			m_Att->m_HP *= 1.2;
			if (m_Att->m_HP > m_Att->m_MAXHP) m_Att-> m_MAXHP = m_Att->m_HP;
			m_DmgDealer[NORMAL_ATTACK]->m_APCost += 2;
			break;

		default:
			break;
	}
	m_Att->m_AP -= m_DmgDealer[NORMAL_ATTACK]->m_APCost;
	m_frameCount = 6;
	SoundManager::GetInstance()->PlaySoundEffect("ji_pre");
	SoundManager::GetInstance()->PlaySoundEffect("ji_atk");
	Champion::DoAttack();
	//delete m_DmgDealer[NORMAL_ATTACK];
	return true;
}
bool Jingu::DoSkill_1()
{
	switch (m_nDice)
	{
		default:
			if (m_Att->m_AP < m_DmgDealer[SKILL_1]->m_APCost) return false;
			m_DmgDealer[SKILL_1]->m_MagicDmg = (m_Att->m_MAXHP - m_Att->m_HP)*0.5;
			break;
	}
	m_Att->m_AP -= m_DmgDealer[SKILL_1]->m_APCost;
	m_frameCount = 6;
	SoundManager::GetInstance()->PlaySoundEffect("ji_s1");
	Champion::DoSkill_1();
	return true;
}
bool Jingu::DoSkill_2()
{
	switch (m_nDice)
	{
		default:
			if (m_Att->m_AP < m_DmgDealer[SKILL_2]->m_APCost) return false;
			m_Att->m_AP -= m_DmgDealer[SKILL_2]->m_APCost;
			float k = m_Att->m_HP / m_Att->m_MAXHP;
			m_Att->m_MAXHP += m_Att->m_AP;
			m_Att->m_HP = k * m_Att->m_MAXHP;
			m_Att->m_AP = 0;
			break;
	}
	m_frameCount = 5;
	SoundManager::GetInstance()->PlaySoundEffect("ji_s2");
	Champion::DoSkill_2();
	return true;
}
bool Jingu::DoUltimateSkill()
{
	switch (m_nDice)
	{
	default:
		if (m_Att->m_AP < m_DmgDealer[SP_SKILL]->m_APCost) return false;
		m_Status->m_TheBuffStatus = SPELL_IMMU;
		m_Status->m_EffectBuffTurn = 2;
		break;
	}
	m_frameCount = 15;
	m_Att->m_AP -= m_DmgDealer[SP_SKILL]->m_APCost;
	SoundManager::GetInstance()->PlaySoundEffect("ji_sp");
	Champion::DoUltimateSkill();
	return true;
}
void Jingu::DoPassTurn()
{
	m_frameCount = 12;
	m_Att->m_AP -= m_DmgDealer[PASS_TURN]->m_APCost;
	SoundManager::GetInstance()->PlaySoundEffect("ji_pt");
	Champion::DoPassTurn();
}
float Jingu::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	return Champion::GetHit(attacker, DMG_Receive);
}

void Jingu::Draw()
{
	Champion::Draw();
}
void Jingu::Update(float dt)
{
	Champion::Update(dt);
}
void Jingu::Clean()
{
	Champion::Clean();
}
void Jingu::ResetSkill()
{
	m_DmgDealer[NORMAL_ATTACK]->m_PhysicDmg = this->m_Att->m_ATK;
	m_DmgDealer[NORMAL_ATTACK]->m_APCost = 0;

	m_DmgDealer[SKILL_1]->m_MagicDmg = 0;
	m_DmgDealer[SKILL_1]->m_APCost = 4;

	m_DmgDealer[SKILL_2]->m_MagicDmg = 0;
	m_DmgDealer[SKILL_2]->m_APCost = 5;

	m_DmgDealer[SP_SKILL]->m_APCost = 6;
	m_DmgDealer[SP_SKILL]->m_MagicDmg = this->m_Att->m_ATK*0.6;
}
void Jingu::SetSkillDetail()
{
	m_DmgDealer[NORMAL_ATTACK]->m_explain =
		"Deal physic damage to enemy."
		"\n> Default: Deal Physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK, 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2)
		+ "\n> Dice 1: Deal Physic dmg = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK, 2) + " + 2)"
		". Restore HP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((this->m_Att->m_ATK + 2) * 0.2, 2) + "[=20% his physic dmg]"
		+ ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 2)"
		"\n> Dice 4: Deal 20% Physic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.2, 2)
		+ ". Increase HP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK * 0.2 * 1.2, 2) + "[=120% his physic dmg]"
		+ ". Ap Cost = (" + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[NORMAL_ATTACK]->m_APCost, 2) + " + 2)";
	m_DmgDealer[SKILL_1]->m_explain =
		"Deal magic damge to enemy."
		"\n> Default: Deal Magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((m_Att->m_MAXHP - m_Att->m_HP) * 0.5, 2) + "[=50% HP Lost]"
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_1]->m_APCost, 2);
	m_DmgDealer[SKILL_2]->m_explain =
		"Consume all current AP. Convert it to HP. Recaculate HP base on current % Hp before converting"
		"New MAX HP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_Att->m_MAXHP + m_Att->m_AP - m_DmgDealer[SKILL_2]->m_APCost, 2)
		+"\nNew HP = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser((m_Att->m_HP/m_Att->m_MAXHP)*(m_Att->m_MAXHP + m_Att->m_AP - m_DmgDealer[SKILL_2]->m_APCost), 2)
		+ ". Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SKILL_2]->m_APCost, 2);
	m_DmgDealer[SP_SKILL]->m_explain =
		"Deal magic damge to enemy."
		"\n> Defalt: Deal magic dmg = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(this->m_Att->m_ATK*0.6, 2)
		+ ". Gain Buff = Spell Immunity in 2 turn. Ap Cost = " + FontsManager::GetInstance()->ConvertFloatToString_Lesser(m_DmgDealer[SP_SKILL]->m_APCost, 2);
}

void Jingu::SetTarget()
{
	Champion::SetTarget();
}


