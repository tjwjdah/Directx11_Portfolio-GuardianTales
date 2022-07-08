#include "pch.h"
#include "CTargetToAuto.h"

#include <Engine\CTimeMgr.h>
#include <Engine\CEventMgr.h>
#include <Engine\CGameObject.h>
#include <Engine/CCollider2D.h>

CTargetToAuto::CTargetToAuto() :CScript((int)SCRIPT_TYPE::TARGETTOAUTO)
, m_fSpeed(0.f)
, m_DIR(DIR::NONE)
, m_Target(Vec2(0.f, 0.f))
, m_TargetDir(Vec2(0.f, 0.f))
{
}

CTargetToAuto::~CTargetToAuto()
{
}

void CTargetToAuto::awake()
{
	if (m_DIR != DIR::NONE)
	{
		switch (m_DIR)
		{
		case DIR::UP:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 3.f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * 0, m_ColliderPos.y * 1));
			m_TargetDir = Vec2(0.f, 1.f);
		}
		break;
		case DIR::DOWN:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 1.f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * 0, m_ColliderPos.y * -1));
			m_TargetDir = Vec2(0.f, -1.f);
		}
		break;
		case DIR::RIGHT:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 2.f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * 1, m_ColliderPos.y * 0));
			m_TargetDir = Vec2(1.f, 0.f);
		}
		break;
		case DIR::LEFT:
		{
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * -1, m_ColliderPos.y * 0));
			m_TargetDir = Vec2(-1.f, 0.f);
		}
		break;
		case DIR::UPRIGHT:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 2.5f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * 1, m_ColliderPos.y * 1));
			m_TargetDir = Vec2(0.5f, 0.5f);
		}
		break;
		case DIR::UPLEFT:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 3.5f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * -1, m_ColliderPos.y * 1));
			m_TargetDir = Vec2(-0.5f, 0.5f);
		}
		break;
		case DIR::DOWNRIGHT:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 1.5f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * 1, m_ColliderPos.y * -1));
			m_TargetDir = Vec2(0.5f, -0.5f);
		}
		break;
		case DIR::DOWNLEFT:
		{
			Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.58f * 0.5f));
			Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * -1, m_ColliderPos.y * -1));
			m_TargetDir = Vec2(-0.5f, -0.5f);
		}
		break;
		}
	}
	else
	{
		m_TargetDir = m_Target - Transform()->GetLocalPos();
		m_TargetDir.Normalize();

		float m_angle = -atan2f(m_TargetDir.y, m_TargetDir.x);	//접선의 기울기
		Transform()->SetLocalRot(Vec3(0, 0, 3.14f - m_angle));

		Collider2D()->SetvOffsetPos(Vec2(m_ColliderPos.x * m_TargetDir.x, m_ColliderPos.y * m_TargetDir.y)); // 포즈를 나중에 조정해줄때 콜라이더 위치도 타겟방향으로 조절해줌
	}
}

void CTargetToAuto::update()
{
	if (GetGameObject()->IsDead())
		return;

	Vec3 vPos = Transform()->GetLocalPos();
	//test (타겟 : 마우스포즈)
	if (m_DIR != DIR::NONE) //정해준 방향이 있다면 그 방향으로 나가도록
	{
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
	}
	else if (m_DIR == DIR::NONE)  // 방향이 없으면 타겟 방향으로 공격이 나가도록
	{



		vPos.x += fDT * m_TargetDir.x * m_fSpeed;
		vPos.y += fDT * m_TargetDir.y * m_fSpeed;



	}





	Transform()->SetLocalPos(vPos);
}
