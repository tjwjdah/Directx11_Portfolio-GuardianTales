#include "pch.h"
#include "CPlayerPosSetScript.h"



CPlayerPosSetScript::CPlayerPosSetScript():CScript((int)SCRIPT_TYPE::PLAYERPOSSETSCRIPT)
, m_TargetObj(nullptr)
{

}

CPlayerPosSetScript::~CPlayerPosSetScript()
{
}
void CPlayerPosSetScript::update()
{
	if (m_TargetObj ==nullptr)
		return;

	Vec3 Pos = m_TargetObj->Transform()->GetLocalPos();
	Transform()->SetLocalPos(Pos);
}