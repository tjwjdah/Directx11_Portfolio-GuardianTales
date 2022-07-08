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

#include "CPlayerScript.h"
#include "CDropMissileScript.h"
#include "CTargetToAuto.h"
#include "CPlayerPosSetScript.h"

#include "CHitScript.h"
#include "CObjState.h"
void CInvaderScript::Thunder()
{

	CGameObject* pObject = nullptr;
	CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
	if (pPlayer == nullptr) return;
	Vec3 PlayerPos = pPlayer->Transform()->GetLocalPos();

	if (!m_attackflag)
	{
		m_savepos = PlayerPos;
		////effect =======================
		//¶³¾îÁö´Â°Í
		pObject = m_Attack11->Instantiate();
		pObject->Transform()->SetLocalPos(PlayerPos);
		pObject->Transform()->SetLocalScaleX(250.f);
		pObject->Transform()->SetLocalScaleY(450.f);
		pObject->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.3f));
		pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, -30.f));
		pObject->Animator2D()->PlayAnimation(L"Attack1", false);
		CDropMissileScript* tar = (CDropMissileScript*)pObject->GetScript(L"CDropMissileScript");
		tar->SetSpeed(450.f);

		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)pObject;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)30;
		CEventMgr::GetInst()->AddEvent(even);

		
		m_attackflag = true;

	}

	/*if (!m_attackflag2)
	{
		m_fThunderTime += fDT;
		if (m_fThunderTime > 0.3) {
			pObject = m_Attack1->Instantiate();
			pObject->Transform()->SetLocalPos(m_savepos);
			pObject->Transform()->SetLocalScaleX(128.f * 4.f);
			pObject->Transform()->SetLocalScaleY(128.f * 3.f);
			pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 0.5f));
			pObject->Animator2D()->PlayAnimation(L"Attack2", false);
			tEvent even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)pObject;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);
			m_attackflag2 = true;
			m_fThunderTime = 0.f;
		}
	}
	*/
	if (Animator2D()->GetCurAnim()->IsFinish())
	{
	

		m_atime = 0.f;
		m_pattern = Pattern::LOOP;
		m_aniflag = false;
		m_attackflag = false;
	}
}
