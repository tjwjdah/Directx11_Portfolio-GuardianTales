#include "pch.h"
#include "CMissileScript.h"

#include <Engine\CTimeMgr.h>
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
CMissileScript::CMissileScript()
	: CScript((int)SCRIPT_TYPE::MISSILESCRIPT)
	, m_fMaxTime(0.f)
	, m_fTime(0.f)
{

}

CMissileScript::~CMissileScript()
{

}


void CMissileScript::update()
{
	if (GetGameObject()->IsDead())
		return;


	m_fTime += fDT;

	if (m_fMaxTime < m_fTime)
	{
		m_fTime = 0;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	
	}
}