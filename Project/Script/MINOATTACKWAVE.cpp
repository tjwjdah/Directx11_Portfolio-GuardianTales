#include "pch.h"



#include "CMinotauros.h"
#include "CFSMScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CCollider2D.h>
#include "CRadianDIRScript.h"

#include <Engine\CEventMgr.h>
#include "CHitScript.h"
#include "CObjState.h"
void CMinotauros::ATTACKWAVE()
{
    switch (m_Pattern)
    {
    case Pattern::START:
    {
        if (!m_AinmOn)
        {
            switch (m_DIR)
            {
            case DIR::UP:
                Animator2D()->PlayAnimation(L"ATTACKREADY_UP", false);
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"ATTACKREADY_DOWN", false);
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"ATTACKREADY_RIGHT", false);
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"ATTACKREADY_LEFT", false);
                break;
            }
            m_AinmOn = true;
        }


        if (Animator2D()->GetCurAnim()->IsFinish())
        {
            m_Pattern = Pattern::LOOP;
            m_AinmOn = false;
            m_fMaxTime = 0.5f;

        }

    }
    break;
    case Pattern::LOOP:
    {
        if (!m_AinmOn)
        {
            switch (m_DIR)
            {
            case DIR::UP:
                Animator2D()->PlayAnimation(L"ATTACKREADYLOOP_UP");
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"ATTACKREADYLOOP_DOWN");
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"ATTACKREADYLP_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"ATTACKREADYLP_LEFT");
                break;
            }
            m_AinmOn = true;
        }

        m_fTime += fDT;

        if (m_fTime > m_fMaxTime)
        {
            m_Pattern = Pattern::PLAY;
            m_fTime = 0;
            m_AinmOn = false;
        }


    }
    break;
    case Pattern::PLAY:
    {
        if (!m_AinmOn)
        {
            CGameObject* pObject = m_Attack2->Instantiate();
            Vec3 Pos = Transform()->GetLocalPos();
            CRadianDIRScript* Dir;


            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"mino_shout");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"AttackHit");
            int Damage = m_ObjState->GetATK() * 2;
            Hit->SetiDamage(Damage);
            Hit->Seteffect(effect);
            switch (m_DIR)
            {
            case DIR::UP:
            {
                Animator2D()->PlayAnimation(L"ATTACK_UP", false);
                Pos.y += 80;
                pObject->Transform()->SetLocalPos(Pos);
                pObject->Animator2D()->PlayAnimation(L"WaveUp");
                Dir = (CRadianDIRScript*)pObject->GetScript(L"CRadianDIRScript");
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.2f));
                pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, 96.0f));
                Dir->SetDir(DIR::UP);
            }
            break;
            case DIR::DOWN:
            {
                Animator2D()->PlayAnimation(L"ATTACK_DOWN", false);
                Pos.y -= 80;
                pObject->Transform()->SetLocalPos(Pos);
                pObject->Animator2D()->PlayAnimation(L"WaveDown");
                Dir = (CRadianDIRScript*)pObject->GetScript(L"CRadianDIRScript");
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.2f));
                pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, -96.0f));
                Dir->SetDir(DIR::DOWN);
            }
            break;
            case DIR::RIGHT:
            {
                Animator2D()->PlayAnimation(L"ATTACK_RIGHT", false);
                Pos.x += 80;
                pObject->Transform()->SetLocalPos(Pos);
                pObject->Animator2D()->PlayAnimation(L"WaveRight");
                Dir = (CRadianDIRScript*)pObject->GetScript(L"CRadianDIRScript");
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.4f));
                pObject->Collider2D()->SetvOffsetPos(Vec2(96.f, 0.0f));
                Dir->SetDir(DIR::RIGHT);
            }
            break;
            case DIR::LEFT:
            {
                Animator2D()->PlayAnimation(L"ATTACK_LEFT", false);
                Pos.x -= 80;
                pObject->Transform()->SetLocalPos(Pos);
                pObject->Animator2D()->PlayAnimation(L"WaveLeft");
                Dir = (CRadianDIRScript*)pObject->GetScript(L"CRadianDIRScript");
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.4f));
                pObject->Collider2D()->SetvOffsetPos(Vec2(-96.f, .0f));
                Dir->SetDir(DIR::LEFT);


            }
            break;
            }
            m_AinmOn = true;
            tEvent even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);
        }

        if (Animator2D()->GetCurAnim()->IsFinish())
        {
            m_Pattern = Pattern::END;
            m_AinmOn = false;
            m_fMaxTime = 0.5f;
        }


    }
    break;
    case Pattern::END:
    {

        m_Pattern = Pattern::START;
        m_State = MinoState::IDLE;

    }
    break;
    }
}