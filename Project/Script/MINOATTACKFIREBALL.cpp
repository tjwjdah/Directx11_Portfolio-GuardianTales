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
#include <Engine\CEventMgr.h>
#include "CMissileScript.h"
#include "CRadianDIRScript.h"
#include "CHitScript.h"
#include "CObjState.h"
#include <Engine\CCollider2D.h>
void CMinotauros::ATTACKFIREBALL()
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
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"mino_walk");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)


            CGameObject* pObject[15];
            Vec3 Pos = Transform()->GetLocalPos();
            CRadianDIRScript* Dir;
            CHitScript* Hit;
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"FireHit");
            switch (m_DIR)
            {
            case DIR::UP:
            {
                Animator2D()->PlayAnimation(L"ATTACK_UP", false);
                Pos.y += 80;
                for (int i = 0; i < 13; i++)
                {
                    pObject[i] = m_Attack1->Instantiate();

                    pObject[i]->Transform()->SetLocalPos(Pos);

                    Dir = (CRadianDIRScript*)pObject[i]->GetScript(L"CRadianDIRScript");
                    Dir->SetRadian(3.26 + 6.f * i);
                    Hit = (CHitScript*)pObject[i]->GetScript(L"CHitScript");
                    int Damage = m_ObjState->GetATK();
                    Hit->SetiDamage(Damage);
                    Hit->Seteffect(effect);
                }


            }
            break;
            case DIR::DOWN:
            {
                Animator2D()->PlayAnimation(L"ATTACK_DOWN", false);
                Pos.y -= 80;
                for (int i = 0; i < 13; i++)
                {
                    pObject[i] = m_Attack1->Instantiate();

                    pObject[i]->Transform()->SetLocalPos(Pos);
                    Dir = (CRadianDIRScript*)pObject[i]->GetScript(L"CRadianDIRScript");
                    Dir->SetRadian(0.13 + 6.f * i);
                    Hit = (CHitScript*)pObject[i]->GetScript(L"CHitScript");
                    int Damage = m_ObjState->GetATK();
                    Hit->SetiDamage(Damage);
                    Hit->Seteffect(effect);
                }

            }
            break;
            case DIR::RIGHT:
            {
                Animator2D()->PlayAnimation(L"ATTACK_RIGHT", false);
                Pos.x += 80;
                for (int i = 0; i < 13; i++)
                {
                    pObject[i] = m_Attack1->Instantiate();

                    pObject[i]->Transform()->SetLocalPos(Pos);
                    Dir = (CRadianDIRScript*)pObject[i]->GetScript(L"CRadianDIRScript");
                    Dir->SetRadian(1.7 + 6.f * i);
                    Hit = (CHitScript*)pObject[i]->GetScript(L"CHitScript");
                    int Damage = m_ObjState->GetATK();
                    Hit->SetiDamage(Damage);
                    Hit->Seteffect(effect);
                }

            }
            break;
            case DIR::LEFT:
            {
                Animator2D()->PlayAnimation(L"ATTACK_LEFT", false);
                Pos.x -= 80;
                for (int i = 0; i < 13; i++)
                {
                    pObject[i] = m_Attack1->Instantiate();

                    pObject[i]->Transform()->SetLocalPos(Pos);
                    Dir = (CRadianDIRScript*)pObject[i]->GetScript(L"CRadianDIRScript");
                    Dir->SetRadian(4.86 + 6.f * i);
                    Hit = (CHitScript*)pObject[i]->GetScript(L"CHitScript");
                    int Damage = m_ObjState->GetATK();
                    Hit->SetiDamage(Damage);
                    Hit->Seteffect(effect);
                }
            }
            break;
            }
            m_AinmOn = true;


            for (int i = 0; i < 13; i++)
            {
                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject[i];
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);
            }
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