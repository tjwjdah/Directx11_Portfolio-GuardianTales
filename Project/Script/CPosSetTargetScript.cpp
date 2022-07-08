#include "pch.h"
#include "CPosSetTargetScript.h"

#include <Engine\CEventMgr.h>



CPosSetTargetScript::CPosSetTargetScript() :CScript((int)SCRIPT_TYPE::POSSETTARGETSCRIPT),
m_TargetPos(Vec3(0.f, 0.f, 0.f)),
m_fSpeed(200.f),
m_Dir(Vec2(0.f, 0.f))
{

}

CPosSetTargetScript::~CPosSetTargetScript()
{

}
void CPosSetTargetScript::update()
{
	if (GetGameObject()->IsDead())
		return;
	Vec3 Pos = Transform()->GetLocalPos();

	Vec2 DistPos;
	DistPos.x =  m_TargetPos.x - Pos.x;
	DistPos.y =  m_TargetPos.y - Pos.y;
	float m_fDistance = DistPos.Length();
	Pos.x += m_Dir.x * fDT * m_fSpeed;
	Pos.y += m_Dir.y * fDT * m_fSpeed;

	
	Transform()->SetLocalPos(Pos);
	if (m_Dir.x > 0.f && m_Dir.y >0.f)
	{
		if (Pos.x > m_TargetPos.x && Pos.y > m_TargetPos.y)
		{
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);
		}
	}
	else if (m_Dir.x > 0.f && m_Dir.y < 0.f)
	{
		if (Pos.x > m_TargetPos.x && Pos.y < m_TargetPos.y)
		{
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);
		}
	}
	else if (m_Dir.x < 0.f && m_Dir.x > 0.f)
	{
		if (Pos.x < m_TargetPos.x && Pos.y > m_TargetPos.y)
		{
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);
		}
	}
	else if (m_Dir.x < 0.f && m_Dir.x < 0.f)
	{
		if (Pos.x < m_TargetPos.x && Pos.y < m_TargetPos.y)
		{
			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);
		}
	}
	
}

void CPosSetTargetScript::awake()
{
	Vec3 Pos = Transform()->GetLocalPos();
	m_Dir.x = m_TargetPos.x - Pos.x;
	m_Dir.y = m_TargetPos.y - Pos.y;
	m_Dir.Normalize();
}