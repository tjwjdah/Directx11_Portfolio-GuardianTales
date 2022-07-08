#include "pch.h"
#include "CSapa.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CEventMgr.h>
#include "CHitScript.h"
#include "CObjState.h"
void CSapa::ATTACKJINGAK()
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
                Animator2D()->PlayAnimation(L"JINGAK_UP", false);
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"JINGAK_DOWN", false);
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"JINGAK_RIGHT", false);
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"JINGAK_LEFT", false);
                break;
            }
            m_AinmOn = true;
        }

        if (Animator2D()->GetCurAnim()->GetAnimFrmRatio() > 0.6) {
            Vec3 Pos = Transform()->GetLocalPos();
            CGameObject* Obj = m_Jin->Instantiate();
            Obj->Transform()->SetLocalPos(Pos);

            CHitScript* Hit = (CHitScript*)Obj->GetScript(L"CHitScript");
            int Damage = m_ObjState->GetATK() * 2;
            Hit->SetiDamage(Damage);


            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sapa_jingak");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)


            tEvent even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)Obj;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            m_Pattern = Pattern::PLAY;
            m_AinmOn = false;
            m_fMaxTime = 0.5f;

        }


        if (Animator2D()->GetCurAnim()->IsFinish())
        {







        }

    }
    break;
    case Pattern::LOOP:
    {



    }
    break;
    case Pattern::PLAY:
    {


        //프리펩 추가

        m_fTime += fDT;
        if (m_fMaxTime < m_fTime)
        {
            m_fMaxTime = 0.5;
            m_fTime = 0;
            m_Pattern = Pattern::END;
        }

    }
    break;
    case Pattern::END:
    {

        m_Pattern = Pattern::START;
        m_State = SapaState::IDLE;

    }
    break;
    }


}