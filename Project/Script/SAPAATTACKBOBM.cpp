#include "pch.h"
#include "CSapa.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CPrefab.h>
#include <Engine\CEventMgr.h>
#include "CHitScript.h"
#include "CObjState.h"
#include "CPosSetTargetScript.h"
void CSapa::ATTACKBOBM()
{
	switch (m_Pattern)
	{
	case Pattern::START:
	{
		if (!m_AinmOn)
		{
			Vec3 Pos = Transform()->GetLocalPos();
			CGameObject* Obj = m_BobmStart->Instantiate();
			Obj->Transform()->SetLocalPos(Pos);
			Obj->Transform()->SetLocalPosY(Pos.y+128);
			m_DIR = DIR::DOWN;
			Animator2D()->PlayAnimation(L"BOMBREADY_DOWN", false);
			
			m_AinmOn = true;

			tEvent even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)Obj;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);


		}

		if (Animator2D()->GetCurAnim()->IsFinish())
		{
			m_Pattern = Pattern::LOOP;
			m_AinmOn = false;
			m_fMaxTime = 0.6f;
			m_fTime = 0;
		}
	}
	break;
	case Pattern::LOOP:
	{
		if (!m_AinmOn)
		{

			m_DIR = DIR::DOWN;
			Animator2D()->PlayAnimation(L"BOMBLOOP_DOWN2");

			m_AinmOn = true;



			Vec3 Pos = Transform()->GetLocalPos();
			CGameObject* Obj = m_Bobm->Instantiate();
			Obj->Transform()->SetLocalPos(Pos);
			Obj->Transform()->SetLocalPosY(Pos.y + 128);
			CPosSetTargetScript* Script = (CPosSetTargetScript*)Obj->GetScript(L"CPosSetTargetScript");
			CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
			
			Script->SetTargetPos(pPlayer->Transform()->GetLocalPos());

			m_AinmOn = true;

			CHitScript* Hit = (CHitScript*)Obj->GetScript(L"CHitScript");
			Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"SapaHit");
			int Damage = m_ObjState->GetATK() * 3;
			Hit->SetiDamage(Damage);
			Hit->Seteffect(effect);

			tEvent even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)Obj;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);


		}

		m_fTime += fDT;

		if (m_fTime > m_fMaxTime)
		{
			m_Pattern = Pattern::PLAY;
			m_AinmOn = false;
			m_BobmNum++;
			m_fTime = 0;
		}
	}
	break;
	case Pattern::PLAY:
	{
		//ÇÁ¸®Æé Ãß°¡


		

		if (m_BobmNum < 2)
		{
			
			m_Pattern = Pattern::LOOP;
		}
		else
		{
			m_Pattern = Pattern::END;
		}
		

	}
	break;
	case Pattern::END:
	{
		if (!m_AinmOn)
		{

			m_DIR = DIR::DOWN;
			Animator2D()->PlayAnimation(L"BOMBEND_DOWN",false);




			m_AinmOn = true;

			
		}
		
		if (Animator2D()->GetCurAnim()->IsFinish())
		{
			m_Pattern = Pattern::START;
			m_State = SapaState::IDLE;
			m_BobmNum = 0;


			Vec3 Pos = Transform()->GetLocalPos();
			CGameObject* Obj = m_Bobm->Instantiate();
			Obj->Transform()->SetLocalPos(Pos);
			Obj->Transform()->SetLocalScale(Vec3(640.f, 640.f, 0.f));
			Obj->Transform()->SetLocalPosY(Pos.y + 128);

			CPosSetTargetScript* Script = (CPosSetTargetScript*)Obj->GetScript(L"CPosSetTargetScript");
			CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);

			CHitScript* Hit = (CHitScript*)Obj->GetScript(L"CHitScript");
			Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"SapaHit");
			int Damage = m_ObjState->GetATK() * 3;
			Hit->SetiDamage(Damage);
			Hit->Seteffect(effect);
			Script->SetTargetPos(pPlayer->Transform()->GetLocalPos());

			tEvent even = {};
			even.eEvent = EVENT_TYPE::CREATE_OBJECT;
			even.lParam = (DWORD_PTR)Obj;
			//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
			even.wParam = (DWORD_PTR)30;
			CEventMgr::GetInst()->AddEvent(even);
		}
	}
	break;
	case Pattern::NONE:
	{

	}
	break;

	}

}
