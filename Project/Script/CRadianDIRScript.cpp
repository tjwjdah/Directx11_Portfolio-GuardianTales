#include "pch.h"
#include "CRadianDIRScript.h"


CRadianDIRScript::CRadianDIRScript() :CScript((int)SCRIPT_TYPE::RADIANDIRSCRIPT)
, m_fRadian(0.f)
, m_fSpeed(450.f)
, m_DIR(DIR::NONE)
{
}

CRadianDIRScript::~CRadianDIRScript()
{
}
void CRadianDIRScript::update()
{
	//test (타겟 : 마우스포즈)
	/*
	POINT a = CKeyMgr::GetInst()->GetPrevMousePos();
	a.x = a.x - 800;
	a.y = -a.y + 450;
	//test~
	

	
	Vec2 tarpos = Vec2((float)a.x, (float)a.y);
	*/
	Vec3 vPos = Transform()->GetLocalPos();
	if (m_DIR == DIR::NONE)
	{
		Vec2 dir;
		dir.x = cosf(m_fRadian);
		dir.y = sinf(m_fRadian);
		dir.Normalize();

		vPos.x += fDT * dir.x * m_fSpeed;
		vPos.y += fDT * dir.y * m_fSpeed;

		m_angle = -atan2f(dir.y, dir.x);	//접선의 기울기

		Transform()->SetLocalRot(Vec3(0, 0, m_angle));
		Transform()->SetLocalPos(vPos);
	}
	else
	{
		Vec3 vPos = Transform()->GetLocalPos();
		switch (m_DIR)
		{
		case DIR::UP:
		{
			vPos.y += fDT * m_fSpeed;
		}
		break;
		case DIR::DOWN:
		{
			vPos.y -= fDT * m_fSpeed;
		}
		break;
		case DIR::RIGHT:
		{
			vPos.x += fDT * m_fSpeed;
		}
		break;
		case DIR::LEFT:
		{
			vPos.x -= fDT * m_fSpeed;
		}
		break;
		case DIR::UPRIGHT:
		{
			vPos.x += fDT * m_fSpeed / 2;
			vPos.y += fDT * m_fSpeed / 2;
		}
		break;
		case DIR::UPLEFT:
		{
			vPos.x -= fDT * m_fSpeed / 2;
			vPos.y += fDT * m_fSpeed / 2;
		}
		break;
		case DIR::DOWNRIGHT:
		{
			vPos.x += fDT * m_fSpeed / 2;
			vPos.y -= fDT * m_fSpeed / 2;
		}
		break;
		case DIR::DOWNLEFT:
		{
			vPos.x -= fDT * m_fSpeed / 2;
			vPos.y -= fDT * m_fSpeed / 2;
		}
		break;
		}
		Transform()->SetLocalPos(vPos);
	}

	
}
void CRadianDIRScript::awake()
{
}

