#include "pch.h"
#include "CTouchScript.h"

#include <Engine\CTimeMgr.h>
CTouchScript::CTouchScript() :CScript((int)SCRIPT_TYPE::TOUCHSCRIPT)
, m_Time(0.f)
, m_Show(true)
{

}

CTouchScript::~CTouchScript()
{
}
void CTouchScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	m_Time += fDT;
	if (m_Time > 0.5f)
	{
		if (m_Show == false)
			m_Show = true;
		else
			m_Show = false;
		m_Time = 0;
	}
	if (m_Show)
	{
		Transform()->SetLocalScaleX(350.f);
	}
	else
		Transform()->SetLocalScaleX(0.f);
}

