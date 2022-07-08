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
void CPlayerScript::EvaAttack()
{
    if (m_eCurState == PLAYER_STATE::SKILL)
    {
        CGameObject* pObject = nullptr;
        Vec3 Pos = Transform()->GetLocalPos();

        if (m_ISkillNum == 1)
        {
            if (m_State->m_CoolTimeMax <= m_State->m_CoolTime)
            {
                Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_skill0");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
                pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_skill1");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
                pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_skill2");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
                pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_skill3");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
                pObject = m_Skill1->Instantiate();
                CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_Target != nullptr)
                {
                    pObject->Transform()->SetLocalPos(m_Target->Transform()->GetLocalPos());
                }
                else
                    pObject->Transform()->SetLocalPos(Pos);
                Hit->SetiDamage(m_State->GetATK() * 1.5f);

                pObject->Transform()->SetLocalScaleX(128.f * 4.f);
                pObject->Transform()->SetLocalScaleY(128.f * 4.f);
                //pObject->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
                pObject->Animator2D()->PlayAnimation(L"Skill", false);

                m_State->m_CoolTime = 0.f;


                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);
            }

        }

    }
    if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
    {

        CGameObject* pObject = nullptr;
        Vec3 Pos = Transform()->GetLocalPos();

        if (m_CurrentCombo == 1 || m_CurrentCombo == 2)
        {
            pObject = m_Attack1->Instantiate();
            if (m_CurrentCombo == 1)
            {
                Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_attack1");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            }
            else if (m_CurrentCombo == 2)
            {
                Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_attack2");
                pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            }

            CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            if (m_iPartyNum == 0)
            {
                Hit->SetPlayer(true);
            }
            else
            {
                Hit->SetPlayer(false);
            }
            Hit->SetiDamage(m_State->GetATK());
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
            Hit->Seteffect(effect);
            switch (m_AnimDir)
            {
            case DIR::UP:
            {
                Pos.y += 45.f;
                pObject->Transform()->SetLocalPos(Pos);
                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");

                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UP);

                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);
            }
            break;
            case DIR::DOWN:
            {
                Pos.y -= 45.f;
                pObject->Transform()->SetLocalPos(Pos);

                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");

                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::DOWN);

                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);
            }
            break;
            case DIR::RIGHT:
            {
                Pos.x += 45.f;
                pObject->Transform()->SetLocalPos(Pos);
                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");

                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::RIGHT);

                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);
            }
            break;
            case DIR::LEFT:
            {
                Pos.x -= 45.f;
                Pos.y += 10.f;
                pObject->Transform()->SetLocalPos(Pos);
                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");

                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::LEFT);

                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);
            }
            break;
            }
        }
        else if (m_CurrentCombo == 3)
        {
            pObject = m_Attack2->Instantiate();
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eva_attack3");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            switch (m_AnimDir)
            {
            case DIR::UP:
            {
                Pos.y += 45.f;
                CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Transform()->SetLocalPos(Pos);

                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UP);
                pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, 50.f));  //0 35
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));  // y x
                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);

                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //=============
                pObject = m_Attack2->Instantiate();

                Pos.y += 20.f;
                Pos.x -= 20.f;
                pObject->Transform()->SetLocalRot(Vec3(0, 0, 4.7f - atan2f(1, -1)));
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UPLEFT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);

                pObject->Collider2D()->SetvOffsetPos(Vec2(-35.f, 30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //===========
                pObject = m_Attack2->Instantiate();
                Pos = Transform()->GetLocalPos();
                pObject->Transform()->SetLocalRot(Vec3(0, 0, 4.7f - atan2f(1, 1)));
                Pos.y += 20.f;
                Pos.x += 20.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UPRIGHT);


                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Collider2D()->SetvOffsetPos(Vec2(30.f, 30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);



            }
            break;
            case DIR::DOWN:   /////////////////*************************************************************** 수정
            {
                Pos.y -= 45.f;
                pObject->Transform()->SetLocalPos(Pos);

                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else

                    hook->SetDir(DIR::DOWN);




                pObject->Collider2D()->SetvOffsetPos(Vec2(0.f, -40.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));




                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);

                CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);

                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //down
                pObject = m_Attack2->Instantiate();
                Pos.y += 45.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::DOWNLEFT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);

                pObject->Collider2D()->SetvOffsetPos(Vec2(-30.f, -30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //UPRIGHT
                pObject = m_Attack2->Instantiate();
                Pos = Transform()->GetLocalPos();
                Pos.y += 30.f;
                Pos.x += 30.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::DOWNRIGHT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);

                pObject->Collider2D()->SetvOffsetPos(Vec2(30.f, -30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

            }
            break;
            case DIR::RIGHT:
            {
                Pos.x += 45.f;
                pObject->Transform()->SetLocalPos(Pos);

                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::RIGHT);
                CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5);
                Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Collider2D()->SetvOffsetPos(Vec2(40.f, 0.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);

                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);


                //=============
                pObject = m_Attack2->Instantiate();
                Pos.y += 20.f;
                Pos.x += 20.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UPRIGHT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Collider2D()->SetvOffsetPos(Vec2(30.f, 30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));
                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //===========
                pObject = m_Attack2->Instantiate();
                Pos = Transform()->GetLocalPos();
                Pos.y -= 20.f;
                Pos.x += 20.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::DOWNRIGHT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Collider2D()->SetvOffsetPos(Vec2(30.f, -30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);




            }
            break;
            case DIR::LEFT:
            {
                Pos.x -= 45.f;
                Pos.y += 10.f;
                pObject->Transform()->SetLocalPos(Pos);

                CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::LEFT);

                CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);
                pObject->Collider2D()->SetvOffsetPos(Vec2(-40.f, 0.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.4f));
                CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
                Missile->SetTime(2.f);

                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //=============
                pObject = m_Attack2->Instantiate();
                Pos.y += 30.f;
                Pos.x -= 20.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::UPLEFT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);

                pObject->Collider2D()->SetvOffsetPos(Vec2(-35.f, 30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);

                //===========
                pObject = m_Attack2->Instantiate();
                Pos = Transform()->GetLocalPos();
                Pos.y -= 30.f;
                Pos.x -= 20.f;
                pObject->Transform()->SetLocalPos(Pos);

                hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
                if (m_Target != nullptr)
                {
                    Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                    hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
                }
                else
                    hook->SetDir(DIR::DOWNLEFT);

                Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
                if (m_iPartyNum == 0)
                {
                    Hit->SetPlayer(true);
                }
                else
                {
                    Hit->SetPlayer(false);
                }
                Hit->SetiDamage(m_State->GetATK() * 1.5f);
                effect = CResMgr::GetInst()->FindRes<CPrefab>(L"EvaAttackeffect");
                Hit->Seteffect(effect);


                pObject->Collider2D()->SetvOffsetPos(Vec2(-30.f, -30.f));
                pObject->Collider2D()->SetvOffsetScale(Vec2(0.4f, 0.5f));

                even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
                even.wParam = (DWORD_PTR)30;
                CEventMgr::GetInst()->AddEvent(even);


            }
            break;
            }

        }


        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObject;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);

        m_PreCombo = m_CurrentCombo;
    }
}