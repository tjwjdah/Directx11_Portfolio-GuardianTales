#include "pch.h"
#include "CObjState.h"
#include "CPlayerScript.h"
#include "CMonsterScript.h"
CObjState::CObjState():CScript((int)SCRIPT_TYPE::OBJSTATE)
, m_MaxHp(0)
,m_Hp(0)
,m_ATK(0)
,m_TargetRange(0.f)
, m_CCDOWN(0)
, m_CCAIRBORNE(0)
, m_CCINJURE(0)
, m_CoolTime(0.f)
, m_CoolTimeMax(0.f)
, m_CoolTime2(0.f)
, m_CoolTimeMax2(0.f)
{
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "m_MaxHp", &m_MaxHp));
	AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "m_Hp", &m_Hp));
}

CObjState::~CObjState()
{
	
}
void CObjState::awake() {
	if (GetGameObject()->GetScript(L"CPlayerScript"))
	{
		Character Char = ((CPlayerScript*)GetGameObject()->GetScript(L"CPlayerScript"))->GetCharacter();
		switch (Char)
		{
		case Character::NARI:
			m_MaxHp = 9999;
			m_Hp = 9999;
			m_ATK = 20;
			m_TargetRange = 600.f;
			m_CoolTimeMax = 8.f;
			break;
		case Character::MARINA:
			m_MaxHp = 9999;
			m_Hp = 9999;
			m_ATK = 10;
			m_TargetRange = 150.f;
			m_CoolTimeMax = 2.f;
			m_CoolTimeMax2 = 6.f;
			break;
		case Character::GARAM:
			m_MaxHp = 9999;
			m_Hp = 9999;
			m_ATK = 40;
			m_TargetRange = 650.f;
			m_CoolTimeMax = 8.f;
			break;
		case Character::EVA:
			m_MaxHp = 9999;
			m_Hp = 9999;
			m_ATK = 20;
			m_TargetRange = 650.f;
			m_CoolTimeMax = 8.f;
			break;
		}
	}
	else if (GetGameObject()->GetScript(L"CMonsterScript"))
	{	
		Monster Mon = ((CMonsterScript*)GetGameObject()->GetScript(L"CMonsterScript"))->GetmMonster();
		switch (Mon)
		{
		case Monster::SAPA:
			m_MaxHp = 5000;
			m_Hp = 5000;
			m_ATK = 15;
		
			break;
		case Monster::BUG:
			m_MaxHp =5000;
			m_Hp = 5000;
			m_ATK = 15;
		
			break;
		case Monster::MINO:
			m_MaxHp = 5000;
			m_Hp = 5000;
			m_ATK = 10;
		
			break;
		case Monster::INVADER:
			m_MaxHp = 5000;
			m_Hp = 5000;
			m_ATK = 20;
		
			break;
		}
	}

}