#include "pch.h"



#include "CMinotauros.h"
#include "CFSMScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>

#include <Engine\CAnimation2D.h>
#include  "CHitScript.h"
#include <Engine\CScript.h>
#include <Engine\CCollider2D.h>
#include "CPlayerScript.h"
#include "CObjState.h"
#include "CMonsterScript.h"
CMinotauros::CMinotauros() :CScript((int)SCRIPT_TYPE::MINOTAUROS)
, m_fDistance(0.f)
, m_vTargetDir(0.f, 0.f)
, m_vRushSetDir(0.f, 0.f)
, m_State(MinoState::IDLE)
, m_DIR(DIR::DOWN)
, m_Pattern(Pattern::START)
, m_AinmOn(false)
, m_fTime(0.f)
, m_fMaxTime(0.f)
, m_fSpeed(300.f)
, m_RushNum(0)
, m_ObjState(nullptr)
{
	m_eColliderDir.b_DOWN = false;
	m_eColliderDir.b_LEFT = false;
	m_eColliderDir.b_RIGHT = false;
	m_eColliderDir.b_UP = false;
}

CMinotauros::~CMinotauros()
{

}

void CMinotauros::awake()
{
	 m_Attack1= CResMgr::GetInst()->FindRes<CPrefab>(L"MinoFireball");
	 m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"MinoWave"); 
	 m_ObjState = (CObjState*)GetGameObject()->GetScript(L"CObjState");
	 CMonsterScript* Monster = (CMonsterScript*)GetGameObject()->GetScript(L"CMonsterScript");
	 Monster->SetmMonster(Monster::MINO);
	 //m_Attack3;

}

void CMinotauros::OnCollisionEnter(CGameObject* _pOther)
{
	if (_pOther->GetScript(L"CTileCollsion"))
	{

		float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
		float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
		float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
		float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
		if (cleft < cdown && cleft < cright && cleft < cup)
		{
			m_eColliderDir.b_LEFT = true;
		}
		else if (cdown < cleft && cdown < cright && cdown < cup)
		{
			m_eColliderDir.b_DOWN = true;
		}
		else if (cright < cdown && cright < cleft && cright < cup)
		{
			m_eColliderDir.b_RIGHT = true;
		}
		else if (cup < cdown && cup < cright && cup < cleft)
		{
			m_eColliderDir.b_UP = true;
		}

		

	}
	else if (_pOther->GetScript(L"CPlayerScript"))
	{
		CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
		if (Player->GetAuto() == 0)
		{
			float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
			float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
			float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
			float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
			if (cleft < cdown && cleft < cright && cleft < cup)
			{
				m_eColliderDir.b_LEFT = true;
			}
			else if (cdown < cleft && cdown < cright && cdown < cup)
			{
				m_eColliderDir.b_DOWN = true;
			}
			else if (cright < cdown && cright < cleft && cright < cup)
			{
				m_eColliderDir.b_RIGHT = true;
			}
			else if (cup < cdown && cup < cright && cup < cleft)
			{
				m_eColliderDir.b_UP = true;
			}
			if (m_State == MinoState::ATTACKRUSH && m_Pattern == Pattern::PLAY)
			{
				Player->SetPlayerState(PLAYER_STATE::CRASH);
				Player->SetHit(true);
				m_Pattern = Pattern::START;
				m_State = MinoState::IDLE;
				m_RushNum = 0;
				m_vRushSetDir.x = 0;
				m_vRushSetDir.y = 0;
				CObjState* m_State = Player->GetObjState();
				int Hp = m_State->GetHp() - m_ObjState->GetATK() * 2.f;
				m_State->SetHp(Hp);
				
			}
			
		}
	}

}

void CMinotauros::OnCollisionExit(CGameObject* _pOther)
{
	if (_pOther->GetScript(L"CTileCollsion"))
	{
		m_eColliderDir.b_RIGHT = false;

		m_eColliderDir.b_LEFT = false;

		m_eColliderDir.b_UP = false;

		m_eColliderDir.b_DOWN = false;

	}
	else if (_pOther->GetScript(L"CPlayerScript"))
	{
		CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
		if (Player->GetAuto() == 0)
		{
			m_eColliderDir.b_RIGHT = false;

			m_eColliderDir.b_LEFT = false;

			m_eColliderDir.b_UP = false;

			m_eColliderDir.b_DOWN = false;
		}
	}

}

void CMinotauros::OnCollision(CGameObject* _pOther)
{
	if (_pOther->GetScript(L"CTileCollsion") )
	{

		float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
		float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
		float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
		float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
		if (cleft < cdown && cleft < cright && cleft < cup)
		{
			m_eColliderDir.b_LEFT = true;
		}
		else if (cdown < cleft && cdown < cright && cdown < cup)
		{
			m_eColliderDir.b_DOWN = true;
		}
		else if (cright < cdown && cright < cleft && cright < cup)
		{
			m_eColliderDir.b_RIGHT = true;
		}
		else if (cup < cdown && cup < cright && cup < cleft)
		{
			m_eColliderDir.b_UP = true;
		}

	}
	else if (_pOther->GetScript(L"CPlayerScript"))
	{
		CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
		if (Player->GetAuto() == 0)
		{
			float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
			float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
			float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
			float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
			if (cleft < cdown && cleft < cright && cleft < cup)
			{
				m_eColliderDir.b_LEFT = true;
			}
			else if (cdown < cleft && cdown < cright && cdown < cup)
			{
				m_eColliderDir.b_DOWN = true;
			}
			else if (cright < cdown && cright < cleft && cright < cup)
			{
				m_eColliderDir.b_RIGHT = true;
			}
			else if (cup < cdown && cup < cright && cup < cleft)
			{
				m_eColliderDir.b_UP = true;
			}
		}
	}

}



void CMinotauros::update()
{

	CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
	if (pPlayer == nullptr)
		return;
	
	m_vTargetDir.x= pPlayer->Transform()->GetWorldPos().x - Transform()->GetWorldPos().x;
	m_vTargetDir.y= pPlayer->Transform()->GetWorldPos().y - Transform()->GetWorldPos().y;
	m_fDistance = m_vTargetDir.Length();
	
	m_vTargetDir.Normalize();
	

	if (m_eColliderDir.b_UP == true)
	{
		if (m_vTargetDir.y > 0.f)
			m_vTargetDir.y = 0.f;
	}
	if (m_eColliderDir.b_DOWN == true)
	{
		if (m_vTargetDir.y < 0.f)
			m_vTargetDir.y = 0.f;
	}
	if (m_eColliderDir.b_RIGHT == true)
	{
		if (m_vTargetDir.x > 0.f)
			m_vTargetDir.x = 0.f;
	}
	if (m_eColliderDir.b_LEFT == true)
	{
		if (m_vTargetDir.x < 0.f)
			m_vTargetDir.x = 0.f;
	}

	if (m_ObjState->GetHp() > 0)
	{
		StateChange();
	}
	else {
		m_State = MinoState::IDLE;
		m_DIR = DIR::DOWN;
		m_Pattern = Pattern::START;
	}

	

	switch (m_State)
	{
	case MinoState::IDLE:
	{
		IDLE();
	}
		break;
	case MinoState::WALK:
	{
		WALK();
	}
		break;
	case MinoState::ATTACKFIREBALL:
	{
		ATTACKFIREBALL();
	}
		break;
	case MinoState::ATTACKWAVE:
	{
		ATTACKWAVE();
	}
		break;
	case MinoState::ATTACKRUSH:
	{
			ATTACKRUSH();
	}
		break;
	}
	
	
	
	// 2. 플레이어를 추적함,  몬스터의 위치를 플레이어를 향해서 이동	
	/*vDir.normalize();

	Vec2 vMonPos = pMonster->GetPos();
	vMonPos += vDir * fDT * pMonster->GetSpeed();
	pMonster->SetPos(vMonPos);
	*/
	
}

void CMinotauros::StateChange()
{
	
	if (m_Pattern == Pattern::NONE )
	{
		
		SetDir();

		if (m_fDistance > 400.f)
		{
			m_State = MinoState::WALK;
		}
		else
		{
			srand((unsigned int)time(NULL));
			int n = rand() % 3;
			if (n == 0)
				m_State = MinoState::ATTACKWAVE;
			else if (n == 1)
				m_State = MinoState::ATTACKFIREBALL;
			else if (n == 2)
				m_State = MinoState::ATTACKRUSH;
		}
		m_Pattern = Pattern::START;
	}

}

void CMinotauros::IDLE()
{

	switch (m_Pattern)
	{
	case Pattern::START:
	{
		if (!m_AinmOn)
		{
			switch (m_DIR)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"IDLE_UP");
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"IDLE_DOWN");
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"IDLE_RIGHT");
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"IDLE_LEFT");
				break;
			}
			m_AinmOn = true;
			m_fMaxTime = 1.5f;
		}

		m_fTime += fDT;

		if (m_fTime > m_fMaxTime)
		{
			m_Pattern = Pattern::NONE;
			m_fTime = 0;
			m_AinmOn = false;
		}

	}
		break;
	case Pattern::END:
	{
		
	}
		break;
	case Pattern::NONE:
	{

	}
		break;
	}
}

void CMinotauros::WALK()
{
	switch (m_Pattern)
	{
	case Pattern::START:
	{
		

		if (!m_AinmOn)
		{
			switch (m_DIR)
			{
			case DIR::UP:
				Animator2D()->PlayAnimation(L"WALK_UP");
				break;
			case DIR::DOWN:
				Animator2D()->PlayAnimation(L"WALK_DOWN");
				break;
			case DIR::RIGHT:
				Animator2D()->PlayAnimation(L"WALK_RIGHT");
				break;
			case DIR::LEFT:
				Animator2D()->PlayAnimation(L"WALK_LEFT");
				break;
				
			}
			
			m_Pattern = Pattern::PLAY;
			m_fMaxTime = 1.5f;
			m_fTime = 0.f;
			m_vRushSetDir = m_vTargetDir;
		}

	}
	break;
	case Pattern::LOOP:
	{

	}
	break;
	case Pattern::PLAY:
	{
		
		
		Vec3 vMinoPos = Transform()->GetLocalPos();

		if (m_eColliderDir.b_UP == true)
		{
			if (m_vRushSetDir.y > 0.f)
				m_vRushSetDir.y = 0.f;
		}
		if (m_eColliderDir.b_DOWN == true)
		{
			if (m_vRushSetDir.y < 0.f)
				m_vRushSetDir.y = 0.f;
		}
		if (m_eColliderDir.b_RIGHT == true)
		{
			if (m_vRushSetDir.x > 0.f)
				m_vRushSetDir.x = 0.f;
		}
		if (m_eColliderDir.b_LEFT == true)
		{
			if (m_vRushSetDir.x < 0.f)
				m_vRushSetDir.x = 0.f;
		}


		vMinoPos.x += m_vRushSetDir.x * fDT * m_fSpeed;
		vMinoPos.y += m_vRushSetDir.y * fDT * m_fSpeed;
		Transform()->SetLocalPos(vMinoPos);
		
		m_fTime += fDT;
		if (m_fMaxTime < m_fTime)
		{
			m_Pattern = Pattern::END;
			m_fTime = 0;
		}

	}
	break;
	case Pattern::END:
	{	
		m_vRushSetDir.x = 0;
		m_vRushSetDir.y = 0;
		SetDir();
		srand((unsigned int)time(NULL));
		int n = rand() % 3;
		if (n == 0)
			m_State = MinoState::ATTACKFIREBALL;
		else if (n == 1)
			m_State = MinoState::ATTACKWAVE;
		else if (n == 2)
			m_State = MinoState::ATTACKRUSH;
		m_Pattern = Pattern::START;
	}
	break;
	case Pattern::NONE:
	{

	}
	break;
	}
}



void CMinotauros::SetDir()
{
	if (m_vTargetDir.y >= 0)
	{
		if (m_vTargetDir.y > fabs(m_vTargetDir.x)) {
			m_DIR = DIR::UP;
		}
		else
		{
			if (m_vTargetDir.x > 0)
			{
				m_DIR = DIR::RIGHT;
			}
			else
			{
				m_DIR = DIR::LEFT;
			}
		}
	}
	else
	{
		if (fabs(m_vTargetDir.y) > fabs(m_vTargetDir.x)) {
			m_DIR = DIR::DOWN;
		}
		else
		{
			if (m_vTargetDir.x > 0)
			{
				m_DIR = DIR::RIGHT;
			}
			else
			{
				m_DIR = DIR::LEFT;
			}
		}
	}

}
