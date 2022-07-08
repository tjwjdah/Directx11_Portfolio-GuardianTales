#include "pch.h"
#include "CHiteffectScript.h"


#include <Engine\CAnimation2D.h>
#include <Engine\CAnimator2D.h>


#include <Engine\CEventMgr.h>

CHiteffectScript::CHiteffectScript():CScript((int)SCRIPT_TYPE::HITEFFECTSCRIPT)
{
}

CHiteffectScript::~CHiteffectScript()
{
}



void CHiteffectScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	if (Animator2D()->GetCurAnim()->IsFinish())
	{
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}
}

void CHiteffectScript::awake()
{

}

