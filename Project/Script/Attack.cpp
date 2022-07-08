#include "pch.h"
#include "CBugMonsterScript.h"

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

#include "CPlayerPosSetScript.h"
#include "CDropMissileScript.h"
#include "CHitScript.h"
#include "CObjState.h"
void CBugMonsterScript::Attack()
{
	if (Animator2D()->GetCurAnim()->IsFinish())
	{
		Animator2D()->ChangeAnimation(L"IDLE");

		////¶¥¿¡ ¶³¾îÁø Åä»ç¹° ÀÌÆåÆ®
		//if (!m_effectaniflag)
		//{
		//	pObject = m_Attack11->Instantiate();
		//	pObject->Transform()->SetLocalPos(m_savepos);
		//	pObject->Transform()->SetLocalScaleX(128.f * 2.f);
		//	pObject->Transform()->SetLocalScaleY(128.f * 2.f);
		//	//pObject->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
		//	pObject->Animator2D()->PlayAnimation(L"Attack11", false);

		//	//CPlayerPosSetScript* PlayerPosSetScript = (CPlayerPosSetScript*)pObject->GetScript(L"CPlayerPosSetScript");
		//	//PlayerPosSetScript->SetTarget(GetGameObject());

		//	tEvent even = {};
		//	even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		//	even.lParam = (DWORD_PTR)pObject;
		//	//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		//	even.wParam = (DWORD_PTR)30;
		//	CEventMgr::GetInst()->AddEvent(even);

		//	m_effectaniflag = true;
		//}

		m_atime = 0.f;
		m_maxtime = 0.6f;
		m_pattern = Pattern::LOOP;
		m_aniflag = false;
		m_didattack = false;
	}

	//if (m_atime > m_maxtime)
	//{
	//	m_atime = 0.f;
	//	m_maxtime = 1.f;
	//	m_pattern = Pattern::LOOP;
	//	m_aniflag = false;
	//}

}