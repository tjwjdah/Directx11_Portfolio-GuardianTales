#include "pch.h"
#include "CBugMonsterScript.h"
#include "CSpinBulletScript.h"
#include "CMissileScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CEventMgr.h>
#include <Engine\CTransform.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CAnimation2D.h>



#include "CHitScript.h"
#include "CObjState.h"


void CBugMonsterScript::Spin()
{

	m_spinatime += fDT;
	if (m_spinatime > 1.f && m_spincount >= 1)
	{
		m_spincount -= 1;
		m_spinatime = 0.f;
		m_didattack = false;
	}

	// 플레이어 추격
	CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
	if (pPlayer == nullptr) return;
	Vec3 monpos = Transform()->GetLocalPos();
	Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
	Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
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

	if (!m_didattack)
	{
		createbullet();
		m_didattack = true;
	}

	if (m_atime > m_maxtime)
	{
		m_atime = 0.f;
		m_maxtime = 1.f;
		m_pattern = Pattern::LOOP;
		m_aniflag = false;
		m_didattack = false;
	}

}
void CBugMonsterScript::createbullet()
{
	CGameObject* pObject = nullptr;
	Vec3 vStartPos = Transform()->GetLocalPos();
	float _angle = 0;

	for (int i = 0; i < 10; i++)
	{
		pObject = m_Attack2->Instantiate();
		CSpinBulletScript* tar = (CSpinBulletScript*)pObject->GetScript(L"CSpinBulletScript");
		float _fSpeedX = 20 * cosf(_angle);
		float _fSpeedY = 20 * sinf(_angle);
		float ang = -atan2f(_fSpeedY, _fSpeedX);

		pObject->Transform()->SetLocalRot(Vec3(0, 0, 4.7f - ang));
		pObject->Transform()->SetLocalPos(vStartPos);
		pObject->Transform()->SetLocalScale(Vec3(47.f, 65.f, 1.f));

		CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
		int Damage = m_ObjState->GetATK() * 1.5f;
		Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"RockHit");
		Hit->SetiDamage(Damage);
		Hit->Seteffect(effect);



		tar->SetTime(3.f);
		tar->SetPower(30);
		tar->SetSpeed(Vec2(_fSpeedX, _fSpeedY));

		_angle += 36;

		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)pObject;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)30;
		CEventMgr::GetInst()->AddEvent(even);
	}

}
