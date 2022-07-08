#include "pch.h"
#include "CPlayerScript.h"

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

#include "CBreakableStoneScript.h"
#include "CPushStoneScript.h"

#include "CFireBowlScript.h"
#include "CBombFlowerScript.h"
#include "CMissileScript.h"
#include "CPlayerPosSetScript.h"
#include "CTargetToAuto.h"
#include "CHitScript.h"
#include "CObjState.h"
void CPlayerScript::GaramAttack()
{
    if (m_eCurState == PLAYER_STATE::SKILL)
    {

        Vec3 Pos = Transform()->GetLocalPos();

        if (m_ISkillNum == 1)
        {
            if (m_State->m_CoolTimeMax <= m_State->m_CoolTime)
            {
                Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"garam_skill1");  //*********
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

                pSound = CResMgr::GetInst()->FindRes<CSound>(L"garam_skill0");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)


                m_State->m_CoolTime = 0.f;

                CGameObject* pObject2 = nullptr;
                Vec3 Pos = Transform()->GetLocalPos();
                pObject2 = m_Skill2->Instantiate();


                CHitScript* Hit = (CHitScript*)pObject2->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 4);
                Hit->Seteffect(m_Skill1);
                switch (m_AnimDir)
                {
                case DIR::UP:
                {

                    Pos = Transform()->GetLocalPos();
                    Pos.y += 20.f;
                    pObject2->Transform()->SetLocalPos(Pos);
                    CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
                    if (m_Target != nullptr)
                    {
                        Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                        hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));

                    }
                    else
                        hook->SetDir(DIR::UP);

                }
                break;
                case DIR::DOWN:
                {

                    Pos = Transform()->GetLocalPos();
                    Pos.y -= 20.f;
                    pObject2->Transform()->SetLocalPos(Pos);
                    CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
                    if (m_Target != nullptr)
                    {
                        Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                        hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));

                    }
                    else
                        hook->SetDir(DIR::DOWN);

                }
                break;
                case DIR::RIGHT:
                {

                    Pos = Transform()->GetLocalPos();
                    Pos.x += 20.f;
                    pObject2->Transform()->SetLocalPos(Pos);
                    CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
                    if (m_Target != nullptr)
                    {
                        Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                        hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));


                    }
                    else
                        hook->SetDir(DIR::RIGHT);

                }
                break;
                case DIR::LEFT:
                {
                    Pos = Transform()->GetLocalPos();
                    Pos.x -= 20.f;
                    pObject2->Transform()->SetLocalPos(Pos);

                    CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
                    if (m_Target != nullptr)
                    {
                        Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                        hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));


                    }
                    else
                        hook->SetDir(DIR::LEFT);

                }
                break;
                }



                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject2;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);
                m_PreCombo = m_CurrentCombo;

            }
        }
    }

    if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
    {
        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"garam_attack1");
        pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
        CGameObject* pObject = nullptr;
        Vec3 Pos = Transform()->GetLocalPos();
        CGameObject* pObject2 = m_Attack2->Instantiate();
        pObject = m_Attack1->Instantiate();
        switch (m_AnimDir)
        {
        case DIR::UP:
        {
            Pos.y += 20.f;
            pObject->Transform()->SetLocalPos(Pos);

            pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
            pObject->Animator2D()->PlayAnimation(L"Attack_UP1", false);
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");


            Pos = Transform()->GetLocalPos();
            Pos.y += 20.f;
            pObject2->Transform()->SetLocalPos(Pos);
            CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::UP);



        }
        break;
        case DIR::DOWN:
        {
            Pos.y -= 20.f;
            pObject->Transform()->SetLocalPos(Pos);

            pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
            pObject->Animator2D()->PlayAnimation(L"Attack_DOWN1", false);
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");



            Pos = Transform()->GetLocalPos();
            Pos.y -= 20.f;
            pObject2->Transform()->SetLocalPos(Pos);
            CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::DOWN);




        }
        break;
        case DIR::RIGHT:
        {
            Pos.x += 20.f;
            pObject->Transform()->SetLocalPos(Pos);

            pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
            pObject->Animator2D()->PlayAnimation(L"Attack_RIGHT1", false);
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");



            Pos = Transform()->GetLocalPos();
            Pos.x += 20.f;
            pObject2->Transform()->SetLocalPos(Pos);
            CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::RIGHT);




        }
        break;
        case DIR::LEFT:
        {
            Pos.x -= 20.f;
            pObject->Transform()->SetLocalPos(Pos);

            pObject->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));
            pObject->Animator2D()->PlayAnimation(L"Attack_LEFT1", false);
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");



            Pos = Transform()->GetLocalPos();
            Pos.x -= 20.f;
            pObject2->Transform()->SetLocalPos(Pos);
            CTargetToAuto* hook = (CTargetToAuto*)pObject2->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::LEFT);


        }
        break;
        }
        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObject;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);



        CHitScript* Hit = (CHitScript*)pObject2->GetScript(L"CHitScript");
        if (m_iPartyNum == 0)
        {
            Hit->SetPlayer(true);
        }
        else
        {
            Hit->SetPlayer(false);
        }
        Hit->SetiDamage(m_State->GetATK());

        Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"GaramAttackeffect");
        Hit->Seteffect(effect);
        even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObject2;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);
        m_PreCombo = m_CurrentCombo;

    }
}