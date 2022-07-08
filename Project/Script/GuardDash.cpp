#include "pch.h"
#include "CInvaderScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CTransform.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CEventMgr.h>

#include "CPlayerPosSetScript.h"

#include "CHitScript.h"
#include "CObjState.h"
void CInvaderScript::GuardDash()
{
	m_attackdashspeed += 0.2f;
	if (m_attackdashspeed > m_maxspeed) m_attackdashspeed = m_maxspeed;

	
	Vec3 monpos = Transform()->GetLocalPos();


	if (m_eColliderDir.b_UP == true)
	{
		if (m_dashdir.y > 0.f)
			m_dashdir.y = 0.f;
	}
	if (m_eColliderDir.b_DOWN == true)
	{
		if (m_dashdir.y < 0.f)
			m_dashdir.y = 0.f;
	}
	if (m_eColliderDir.b_RIGHT == true)
	{
		if (m_dashdir.x > 0.f)
			m_dashdir.x = 0.f;
	}
	if (m_eColliderDir.b_LEFT == true)
	{
		if (m_dashdir.x < 0.f)
			m_dashdir.x = 0.f;
	}
	


	monpos.x += m_dashdir.x * fDT * m_attackdashspeed;
	monpos.y += m_dashdir.y * fDT * m_attackdashspeed;
	Transform()->SetLocalPos(monpos);

	if (/*dlen < 5.f ||*/ m_atime > 1.0f) // /*또는 벽에 부딪히면*/
	{
		m_atime = 0.f;
		m_maxtime = 2.f;

		m_attackdashspeed = 1000.f;
		m_speed = 100.f;
		m_aniflag = false;

		if (m_dashcount == 1)
		{
			m_pattern = Pattern::LOOP;
		}
		else
		{
			m_pattern = Pattern::START;
			m_dashcount -= 1;
		}
	}


}