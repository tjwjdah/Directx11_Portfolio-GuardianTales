#include "pch.h"
#include "CBugMonsterScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CTransform.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CAnimation2D.h>
#include "CHitScript.h"
#include "CObjState.h"
void CBugMonsterScript::InOut()
{
	m_speed += 1.f;

	CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
	if (pPlayer == nullptr) return;
	Vec3 monpos = Transform()->GetLocalPos();
	Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
	Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
	
	m_fInOutTime += fDT;
	dir.Normalize();

	if (m_eColliderDir.b_UP == true)
	{
		if (dir.y > 0.f)
			dir.y = 0.f;
	}
	if (m_eColliderDir.b_DOWN == true)
	{
		if (dir.y < 0.f)
			dir.y = 0.f;
	}
	if (m_eColliderDir.b_RIGHT == true)
	{
		if (dir.x > 0.f)
			dir.x = 0.f;
	}
	if (m_eColliderDir.b_LEFT == true)
	{
		if (dir.x < 0.f)
			dir.x = 0.f;
	}

	monpos.x += dir.x * fDT * m_speed;
	monpos.y += dir.y * fDT * m_speed;
	Transform()->SetLocalPos(monpos);

	if (m_fInOutTime > 1.5f)
	{
		//튀어나오는 애니로 변경
		m_fInOutTime = 0.f;
		m_atime = 0.f;
		m_maxtime = 1.f;
		m_pattern = Pattern::LOOP;
		m_aniflag = false;
	}


	//if (m_atime > m_maxtime)
	//{
	//	m_atime = 0.f;
	//	m_maxtime = 1.f;
	//	m_pattern = Pattern::LOOP;
	//	m_aniflag = false;
	//}

}