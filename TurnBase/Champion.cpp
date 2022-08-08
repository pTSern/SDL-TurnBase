#include "Champion.h"
#include "TextureManager.h"
#include "Input.h"
Champion::Champion(const Properties* pProperties) : Character(pProperties)
{
	m_Status = new CharacterStatus(GOOD, NONE, 0, 0);
	m_Att = new CharacterAttributes("", 0, 0, 0, 0, 0, 0, 0);
	m_DmgDealer = 
	{
		{new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, 0)}, //Normal Attack
		{new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, 0)}, //Skill 1
		{new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, 0)}, //Skill 2
		{new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, 0)}, //Special Skill
		{new CharacterSpell(0, 0, 0, 0, false, true, 0, 0, 0)}  //Pass turn
	};
	m_bTurn = false;
	m_bEndTurn = false;
	m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);
}
void Champion::Draw()
{
	GameObject::Draw();
	Dice::GetInstance()->Draw();
	
	if (m_Att->m_LIFE >= 0) AdditionEffect::GetInstance()->DrawHeathAPBar(m_Att, m_pTransform->X + 34, m_pTransform->Y);
	if (m_bTurn && m_Att->m_LIFE >= 0)
	{
		AdditionEffect::GetInstance()->DrawSkillLayer(m_textureID, m_DmgDealer);
		AdditionEffect::GetInstance()->DrawFontsAttributes(m_Att);
		AdditionEffect::GetInstance()->DrawFontsCD(m_DmgDealer);
		AdditionEffect::GetInstance()->DrawTarget(m_pTransform->X, m_pTransform->Y);
		this->MouseEvent();
	}
	if (p_bCastSence && !p_bPassturn)
	{
		if (p_nPhyDmgRecive > 0) FontsManager::GetInstance()->Draw("minecraft", m_pTeam_Defender[m_DmgDealer[p_nAttackType]->m_TargetPos]->m_pTransform->X + 36 , m_pTeam_Defender[m_DmgDealer[p_nAttackType]->m_TargetPos]->m_pTransform->Y + 36, 64, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(p_nPhyDmgRecive, 3), 250, 50, 50);
		if (p_nMgDmgRecive > 0) FontsManager::GetInstance()->Draw("minecraft", m_pTeam_Defender[m_DmgDealer[p_nAttackType]->m_TargetPos]->m_pTransform->X + 36 , m_pTeam_Defender[m_DmgDealer[p_nAttackType]->m_TargetPos]->m_pTransform->Y + 56, 64, 16, FontsManager::GetInstance()->ConvertFloatToString_Lesser(p_nMgDmgRecive, 3), 50, 50, 250);
	}
}

void Champion::Update(float dt)
{
	AutoCheck_IsDead();
	//target = new GameObject(new Properties(m_pTransform->X, m_pTransform->Y, 168, 168, 1, "target", SDL_FLIP_NONE, 0, 0, 1, 0));
	if (this->m_Att->m_LIFE >= 0)
	{
		if (m_bTurn && !m_bEndTurn && m_Status->m_TheDebuffStatus != STUN && !p_bCastSence)
		{
			SetTarget();
			ResetSkill();
			SetSkillDetail();
			AutoSetStatus();
			m_nDice = Dice::GetInstance()->RollDice();
			if (Dice::GetInstance()->GetIsDice()) { ReadKey_DoSkill(); }
		}
		else if (m_bTurn && m_Status->m_TheDebuffStatus == STUN)
		{
			AutoSetStatus();
			AutoSkillCoolDown();
			m_bTurn = false;
			m_bEndTurn = true;
		}
		else if (p_bCastSence)
		{
			if (m_pAnimation->IsReachLastFrame(dt))
			{
				m_bTurn = false;
				m_bEndTurn = true;
				p_bCastSence = false;
				if (!p_bPassturn) AfterEnemyGetDamage(p_nAttackType);
				else p_bPassturn = false;

				ResetProperties();
			}
		}
	}
	else
	{
		m_frameCount = 1;
		m_pAnimation->SetPros(m_textureID, DEAD, m_frameCount, m_animationSpeed, m_flip);
		m_bTurn = false;
		m_bEndTurn = false;
	}
	
	m_pRigidBody->Update(dt);
	m_pTransform->TranslateX(m_pRigidBody->GetPosition().getX());
	m_pAnimation->Update();
	Dice::GetInstance()->Update(dt);
	this->m_Att->CharacterAttributes::AutoValidAttributes();
}

void Champion::ReadKey_DoSkill()
{
	//Champion cant atk while disarmed
	if (this->m_Status->m_TheDebuffStatus != DISARMS )
	{
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A) || p_nDoAction == NORMAL_ATTACK)
		{
			if (DoAttack())
			{
				p_nAttackType = NORMAL_ATTACK;
				p_bCastSence = true;
				Dice::GetInstance()->ResetDice();
				AutoSkillCoolDown();
			}
		}
	}
	//Champion cant cast skill while silence
	if (this->m_Status->m_TheDebuffStatus != SILENCE)
	{
		if (m_DmgDealer[SKILL_1]->m_IsReady)
		{
			if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_Q) || p_nDoAction == SKILL_1)
			{
				if (DoSkill_1())
				{
					p_nAttackType = SKILL_1;
					p_bCastSence = true;
					m_DmgDealer[SKILL_1]->m_IsReady = false;
					Dice::GetInstance()->ResetDice();
					AutoSkillCoolDown();
				}
			}		
		}
		if (m_DmgDealer[SKILL_2]->m_IsReady)
		{
			if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W) || p_nDoAction == SKILL_2)
			{
				if (DoSkill_2())
				{
					p_nAttackType = SKILL_2;
					p_bCastSence = true;
					m_DmgDealer[SKILL_2]->m_IsReady = false;
					Dice::GetInstance()->ResetDice();
					AutoSkillCoolDown();
				}
			}
		}
		if (m_DmgDealer[SP_SKILL]->m_IsReady)
		{
			if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_E) || p_nDoAction == SP_SKILL)
			{
				if (DoUltimateSkill())
				{
					p_nAttackType = SP_SKILL;
					p_bCastSence = true;
					m_DmgDealer[SP_SKILL]->m_IsReady = false;
					Dice::GetInstance()->ResetDice();
					AutoSkillCoolDown();
				}
			}
		}
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S) || p_nDoAction == PASS_TURN)
	{
		DoPassTurn();
		p_bCastSence = true;
		p_bPassturn = true;
		Dice::GetInstance()->ResetDice();
		AutoSkillCoolDown();
	}
}

bool Champion::DoAttack()
{
	this->AttackEnemy(NORMAL_ATTACK, DO_ATTACK);
	return true;
}
bool Champion::DoSkill_1()
{
	AttackEnemy(SKILL_1, DO_SKILL_1);
	return true;
}
bool Champion::DoSkill_2()
{
	AttackEnemy(SKILL_2, DO_SKILL_2);
	return true;
}
bool Champion::DoUltimateSkill()
{
	AttackEnemy(SP_SKILL, DO_SP_SKILL);
	return true;
}
void Champion::DoPassTurn()
{
	m_pAnimation->SetPros(m_textureID, DO_PASSTURN, m_frameCount, m_animationSpeed, m_flip);
}
float Champion::GetHit(Champion* attacker, CharacterSpell* DMG_Receive)
{
	float DmgRecive = DMG_Receive->m_PhysicDmg * (1 - (BALANCE_NUMBER * (this->m_Att->m_ARMOR - DMG_Receive->m_ArmorPen) / (1 + (BALANCE_NUMBER * (abs(m_Att->m_ARMOR - DMG_Receive->m_ArmorPen))))));
	this->m_Att->m_HP -= DmgRecive;
	return DmgRecive;
}
float Champion::GetSpell(Champion* attacker, CharacterSpell* DMG_Receive)
{
	float DmgRecive = (DMG_Receive->m_MagicDmg + DMG_Receive->m_MagicDmg * (attacker->GetAttributes()->m_SP_Amp / 100)) * (1 - (this->m_Att->m_SP_Res / 100));
	this->m_Att->m_HP -= DmgRecive;
	return DmgRecive;
}
void Champion::AttackEnemy(int attackType, int attackAnimation)
{
	int index = m_DmgDealer[attackType]->m_TargetPos;
	switch (m_pTeam_Defender[index]->m_Status->m_TheBuffStatus)
	{
	case IMMUNITY:
		p_nPhyDmgRecive = 0; 
		p_nMgDmgRecive = 0;
		break;
	case SPELL_IMMU:
		p_nPhyDmgRecive = m_pTeam_Defender[index]->GetHit(m_pTeam_Attacker[m_nPosInBattle], m_DmgDealer[attackType]);
		p_nMgDmgRecive = 0;
		break;
	default:
		p_nPhyDmgRecive = m_pTeam_Defender[index]->GetHit(m_pTeam_Attacker[m_nPosInBattle], m_DmgDealer[attackType]);
		p_nMgDmgRecive = m_pTeam_Defender[index]->GetSpell(m_pTeam_Attacker[m_nPosInBattle], m_DmgDealer[attackType]);
		break;
	}
	m_pTransform->SetX(m_pTeam_Defender[index]->m_pTransform->X + (2 * m_flip - 1) * 90);
	m_pTransform->SetY(m_pTeam_Defender[index]->m_pTransform->Y);
	m_pAnimation->SetPros(m_textureID, attackAnimation, m_frameCount, m_animationSpeed, m_flip);
	m_pTeam_Defender[index]->m_pAnimation->SetPros(m_pTeam_Defender[index]->m_textureID, GET_HIT, 1, m_pTeam_Defender[index]->m_animationSpeed, m_pTeam_Defender[index]->m_flip);
}
void Champion::AfterEnemyGetDamage(int attackType)
{
	int targetIndex = m_DmgDealer[attackType]->m_TargetPos;
	std::cout << m_pTeam_Attacker[m_nPosInBattle]->m_Att->m_Name << " > HIT > " << m_pTeam_Defender[targetIndex]->m_Att->m_Name << std::endl;
	std::cout << "DAMAGE: " << p_nPhyDmgRecive << " SPELL: " << p_nMgDmgRecive
		<< " HP: " << m_pTeam_Defender[targetIndex]->m_Att->m_HP << "/" << m_pTeam_Defender[targetIndex]->m_Att->m_LIFE << " - " << m_nDice << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;

	//Set champion animation to idle
	m_pTeam_Defender[targetIndex]->m_pAnimation->SetPros(m_pTeam_Defender[targetIndex]->m_textureID, IDLE, m_pTeam_Defender[targetIndex]->m_frameCount, m_pTeam_Defender[targetIndex]->m_animationSpeed, m_pTeam_Defender[targetIndex]->m_flip);
}

void Champion::AutoCheck_IsDead()
{
	if (this->m_Att->m_HP <= 0)
	{
		this->m_Att->m_LIFE--;
		if (this->m_Att->m_LIFE >= 0) this->m_Att->m_HP = this->m_Att->m_MAXHP;
	}
}
void Champion::SetTarget()
{
	for (int i = NORMAL_ATTACK; i < PASS_TURN; i++)//Pasturn no need target
	{
		m_DmgDealer[i]->m_TargetPos = AutoSetTarget();
	}
}
int Champion::AutoSetTarget()
{
	int defaultPos = 0;
	while (m_pTeam_Defender[defaultPos]->m_Att->m_LIFE < 0)
	{
		defaultPos++;
		//if (defaultPos >= m_pTeam_Defender.size()) defaultPos = 0;
		if (defaultPos >= m_pTeam_Defender.size())
		{
			defaultPos = 0;
			m_bWin = true;
			break;
		}
	}
	return defaultPos;
}

void Champion::AutoSetStatus()
{
	if (m_Status->m_EffectDebuffTurn <= 0) m_Status->m_TheDebuffStatus = GOOD;
	else m_Status->m_EffectDebuffTurn --;

	if (m_Status->m_EffectBuffTurn <= 0) m_Status->m_TheBuffStatus = NONE;
	else m_Status->m_EffectBuffTurn--;
	
}
void Champion::AutoSkillCoolDown()
{
	for (int i = SKILL_1; i < SP_SKILL + 1; i++)
	{
		if (!m_DmgDealer[i]->m_IsReady && m_DmgDealer[i]->m_CD > 0)
		{

			m_DmgDealer[i]->m_CD--;
		}
		else
		{
			m_DmgDealer[i]->m_CD = m_DmgDealer[i]->m_CD_NEED;
			m_DmgDealer[i]->m_IsReady = true;
		}
	}
}
void Champion::AutoEffectStatus() //void* pP
{

}
void Champion::Clean()
{
	SoundManager::GetInstance()->CleanSoundEffect();
	TextureManager::GetInstance()->Drop(this->m_textureID);
	for (int i = m_DmgDealer.size()-1; i>=0; i--)
	{
		delete m_DmgDealer[i];
	}
	m_DmgDealer.clear();
	m_pTeam_Attacker.clear();
	m_pTeam_Defender.clear();

	m_pTeam_Attacker.shrink_to_fit();
	m_pTeam_Defender.shrink_to_fit();
	m_DmgDealer.shrink_to_fit();
	Character::Clean();
}

void Champion::ResetProperties()
{
	m_textureID = m_pAdditionProperties->getTextureID();
	m_width = m_pAdditionProperties->getWidth();
	m_height = m_pAdditionProperties->getHeight();
	m_flip = m_pAdditionProperties->getFlip();
	m_frameCount = m_pAdditionProperties->getFrameCount();
	m_pTransform->SetX(m_pAdditionProperties->getX());
	m_pTransform->SetY(m_pAdditionProperties->getY());
	m_currentRow = IDLE;
	m_currentFrame = 0;
	m_animationSpeed = 80;
	m_pAnimation->SetPros(m_textureID, m_currentRow, m_frameCount, m_animationSpeed, m_flip);
}

void Champion::MouseEvent()
{
	Transform* pMousePos = Input::GetInstance()->GetMousePosition();
	int skillLayer_width = 64;
	int skillLayer_height = 64;
	p_nDoAction = -1;

	for (int i = 0; i < NULBER_SKILL_LAYER; i++)
	{
		if (pMousePos->X < (STARTER_SKILL_LAYER_X + (i * DISTANCE_S) + skillLayer_width)
			&& pMousePos->X > STARTER_SKILL_LAYER_X + (i * DISTANCE_S)
			&& pMousePos->Y < (STARTER_SKILL_LAYER_Y + skillLayer_height)
			&& pMousePos->Y > STARTER_SKILL_LAYER_Y)
		{ 
			if (Input::GetInstance()->GetMouseButtonState(LEFT)) p_nDoAction = i;
			else AdditionEffect::GetInstance()->DrawSkillInformation(pMousePos->X, pMousePos->Y, m_DmgDealer[i]);
			
		}
	}
	
}