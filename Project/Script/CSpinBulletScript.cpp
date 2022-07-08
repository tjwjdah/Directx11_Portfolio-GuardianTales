#include "pch.h"
#include "CSpinBulletScript.h"

#include <Engine\CTimeMgr.h>
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>

#include <Engine/CSceneMgr.h>
#include "CHitScript.h"
#include "CObjState.h"
CSpinBulletScript::CSpinBulletScript()
	:CScript((int)SCRIPT_TYPE::SPINBULLETSCRIPT)
	, m_speed(Vec2(0.f, 0.f))
	, m_power(30)
	, m_atime(0.f)
	, m_maxtime(5.f)
{
}

CSpinBulletScript::~CSpinBulletScript()
{
}

void CSpinBulletScript::awake()
{

}

void CSpinBulletScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	m_atime += fDT;
	if (m_atime > m_maxtime)
	{
		m_atime = 0.f;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}

	Vec3 vPos = Transform()->GetLocalPos();
	//Vec2 vSpeed = m_speed;





	vPos.x += m_speed.x * fDT * m_power;
	vPos.y += m_speed.y * fDT * m_power;


	Transform()->SetLocalPos(vPos);


}
