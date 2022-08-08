#pragma once
#include "GameObject.h"
#include <vector>
//#include "Properties.h"

enum DebuffStatus
{
	GOOD, //can do everything
	SILENCE, //cant use skill but can attack and pass turn
	DISARMS, //cant attack but can pass turn n use skill
	 
	EXHAUSTED, //no restore AP
	SLOW, //REDUCE SPEED
	STUN // cant do anything even pass turn
};
enum BuffStatus
{
	NONE, //No buff
	HASTED, //x5 speed
	PIERC, //Damage throw armor
	CRIT, //x2 DAMAGE
	SPELL_IMMU, //spell imnunity
	IMMUNITY //immunity to all of damage type
	
};

struct CharacterStatus
{
public:
	CharacterStatus(enum DebuffStatus DebuffSTT, enum BuffStatus BuffSTT, int debuff, int buff)
	{
		m_TheDebuffStatus = DebuffSTT;
		m_TheBuffStatus = BuffSTT;
		m_EffectDebuffTurn = debuff;
		m_EffectBuffTurn = buff;
	};

	enum DebuffStatus m_TheDebuffStatus;
	enum BuffStatus m_TheBuffStatus;
	int m_EffectDebuffTurn, m_EffectBuffTurn;
};

struct CharacterAttributes
{
public:
	CharacterAttributes(std::string name, float MAX_HP, float MAX_AP,float ATK, float SP_Amp, float ARMOR, float SP_Res, float SPD, int LIFE = 0)
	{
		m_Name = name;
		m_HP = m_MAXHP = MAX_HP;
		m_AP = m_MAXAP = MAX_AP;
		m_ATK = ATK;
		m_SP_Amp = SP_Amp;
		m_ARMOR = ARMOR;
		m_SP_Res = SP_Res;
		m_SPD = SPD;
		m_LIFE = LIFE;
	};
	void AutoValidAttributes()
	{
		if (m_HP > m_MAXHP) m_HP = m_MAXHP;
		if (m_AP < 0) m_AP = 0;
		if (m_AP > m_MAXAP) m_AP = m_MAXAP;
	}
	
	std::string m_Name;
	float m_HP, m_MAXHP;
	float m_AP, m_MAXAP;
	float m_ATK, m_SP_Amp;
	float m_ARMOR, m_SP_Res;
	float m_SPD;
	int m_LIFE;
};

struct CharacterSpell
{
public:
	CharacterSpell(float PhysicDmg, float MagicDmg, float ArmorPen, float SpellPen, bool IsCrit, bool IsReady, int CD_NEED, int targetPos, float AP_Cost, std::string Explain = "") :
		m_PhysicDmg(PhysicDmg),
		m_MagicDmg(MagicDmg),
		m_ArmorPen(ArmorPen),
		m_SpellPen(SpellPen),
		m_IsCrit(IsCrit),
		m_IsReady(IsReady),
		m_CD_NEED(CD_NEED),
		m_TargetPos(targetPos),
		m_APCost(AP_Cost),
		//m_Spell(Spell)
		m_explain(Explain)
	{
		m_CD = m_CD_NEED;
	};
	//void (Champion::*m_Spell) ();
	//std::vector<int> m_TargetPos;
	float m_PhysicDmg, m_MagicDmg, m_APCost;
	float m_ArmorPen, m_SpellPen; //Penetration//Penetration
	bool m_IsCrit, m_IsReady;
	int m_CD, m_CD_NEED; //Cooldown
	int m_TargetPos;
	std::string m_explain;
};

class Character : public GameObject
{
public:
	Character(const Properties* pProperties) : GameObject(pProperties) {};
	virtual void Draw() { GameObject::Draw(); }
	virtual void Update(float dt) { GameObject::Update(dt); }
	virtual void Clean() 
	{ 
		delete m_Status;
		delete m_Att;
		for (int i = m_DmgDealer.size() - 1; i >= 0; i--)
		{
			delete m_DmgDealer[i];
		}
		m_DmgDealer.clear();
		GameObject::Clean(); 
	}

	inline void SetPositionInBattle(int pos) { m_nPosInBattle = pos; };
	inline int GetPositionInBattle() { return m_nPosInBattle; }
	inline void SetBackFlip() { m_flip = SDL_FLIP_HORIZONTAL; }
	inline void SetPIB_X(float pos) { m_pTransform->SetX(pos); };
	inline void SetPIB_Y(float pos) { m_pTransform->SetY(pos); };
	inline float GetX() { return m_pTransform->X; }
	inline bool GetIsTurn() { return m_bTurn; }
	inline void SetIsTurn(bool b) { m_bTurn = b; }
	inline bool GetIsEndTurn() {return m_bEndTurn; };
	inline void SetIsEndTurn(bool b) { m_bEndTurn = b; };
	inline bool GetIsWin() { return m_bWin; }
	inline bool CheckIsDead() { if (m_Att->m_LIFE < 0) return true; else return false; }
	//Transform* GetTransform() { return m_pTransform; };

protected:
	bool m_bTurn, m_bEndTurn, m_bWin; 
	int m_nPosInBattle;
	CharacterStatus* m_Status; 
	CharacterAttributes* m_Att;
	std::vector<CharacterSpell*> m_DmgDealer;

};