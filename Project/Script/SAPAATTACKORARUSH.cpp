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
void CSapa::ATTACKORARUSH()
{
    switch (m_Pattern)
    {
    case Pattern::START:
    {
        if (!m_AinmOn)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sapa_fist");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            switch (m_DIR)
            {
            case DIR::UP:
                Animator2D()->PlayAnimation(L"DEATHFIST_UP", false);
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"DEATHFIST_DOWN", false);
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"DEATHFIST_RIGHT", false);
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"DEATHFIST_LEFT", false);
                break;
            }
            m_AinmOn = true;
        }


        if (Animator2D()->GetCurAnim()->IsFinish())
        {
            m_Pattern = Pattern::PLAY;
            m_AinmOn = false;
            m_fMaxTime = 1.0f;
        }

    }
    break;
    case Pattern::LOOP:
    {

    }
    break;
    case Pattern::PLAY:
    {
        if (!m_AinmOn)
        {

            switch (m_DIR)
            {
            case DIR::UP:
                Animator2D()->PlayAnimation(L"ORARUSH_UP");
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"ORARUSH_DOWN2");
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"ORARUSH_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"ORARUSH_LEFT");
                break;
            }
            m_AinmOn = true;
            m_fTime = 0;

            CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
            m_vTargetDir.x = pPlayer->Transform()->GetWorldPos().x - Transform()->GetWorldPos().x;
            m_vTargetDir.y = pPlayer->Transform()->GetWorldPos().y - Transform()->GetWorldPos().y;
            m_vTargetDir.Normalize();


            m_OraObj = m_Ora->Instantiate();
            CHitScript* Hit = (CHitScript*)m_OraObj->GetScript(L"CHitScript");
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"AttackHit");
            int Damage = m_ObjState->GetATK();

            Hit->SetiDamage(Damage);
            Hit->Seteffect(effect);
            tEvent even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)m_OraObj;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

        }

        m_fTime += fDT;
        Vec3 vSapaPos = Transform()->GetLocalPos();
        vSapaPos.x += m_vTargetDir.x * fDT * m_fSpeed / 1.5f;
        vSapaPos.y += m_vTargetDir.y * fDT * m_fSpeed / 1.5f;

        if (m_OraObj != nullptr)
        {
            switch (m_DIR)
            {
            case DIR::UP:
                m_OraObj->Transform()->SetLocalScale(Vec3(128.f, 192.f, 1.f));
                m_OraObj->Transform()->SetLocalPos(Vec3(vSapaPos.x, vSapaPos.y + 160.f, vSapaPos.z));
                break;
            case DIR::DOWN:
                m_OraObj->Transform()->SetLocalScale(Vec3(128.f, 192.f, 1.f));
                m_OraObj->Transform()->SetLocalPos(Vec3(vSapaPos.x, vSapaPos.y - 160.f, vSapaPos.z));
                break;
            case DIR::RIGHT:
                m_OraObj->Transform()->SetLocalScale(Vec3(192.f, 128.f, 1.f));
                m_OraObj->Transform()->SetLocalPos(Vec3(vSapaPos.x + 160.f, vSapaPos.y, vSapaPos.z));
                break;
            case DIR::LEFT:
                m_OraObj->Transform()->SetLocalScale(Vec3(192.f, 128.f, 1.f));
                m_OraObj->Transform()->SetLocalPos(Vec3(vSapaPos.x - 160.f, vSapaPos.y, vSapaPos.z));
                break;
            }

        }

        Transform()->SetLocalPos(vSapaPos);

        if (m_fMaxTime < m_fTime)
        {
            m_Pattern = Pattern::END;
            m_AinmOn = false;
            m_fMaxTime = 0.5f;
            m_fTime = 0;

            if (m_OraObj != nullptr)
            {
                tEvent _temp = {};
                _temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
                _temp.lParam = (DWORD_PTR)m_OraObj;
                CEventMgr::GetInst()->AddEvent(_temp);
                m_OraObj = nullptr;
            }
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