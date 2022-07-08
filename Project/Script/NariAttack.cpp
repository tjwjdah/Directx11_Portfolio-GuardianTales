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
void CPlayerScript::NariAttack()
{
    if (m_eCurState == PLAYER_STATE::SKILL)
    {
        CGameObject* pObject = nullptr;
        Vec3 Pos = Transform()->GetLocalPos();

        if (m_State->m_CoolTimeMax <= m_State->m_CoolTime)
        {
            m_State->m_CoolTime = 0.f;
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"nari_skill1");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            pSound = CResMgr::GetInst()->FindRes<CSound>(L"nari_skill0");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            //UP
            pObject = m_Skill1->Instantiate();

            Pos.y += 45.f;
            pObject->Transform()->SetLocalPos(Pos);

            CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::UP);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, 20.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
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
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            tEvent even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //DOWN
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.y -= 45.f;
            Pos.x -= 10.f;

            pObject->Transform()->SetLocalPos(Pos);

            hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::DOWN);
            pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, -20.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

            Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            if (m_iPartyNum == 0)
            {
                Hit->SetPlayer(true);
            }
            else
            {
                Hit->SetPlayer(false);
            }
            Hit->SetiDamage(m_State->GetATK() * 1.5f);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //RIGHT
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.x += 45.f;
            Pos.y -= 10.f;
            pObject->Transform()->SetLocalPos(Pos);
            hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::RIGHT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(20.f, 10.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
            Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            if (m_iPartyNum == 0)
            {
                Hit->SetPlayer(true);
            }
            else
            {
                Hit->SetPlayer(false);
            }
            Hit->SetiDamage(m_State->GetATK() * 1.5f);

            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);


            //LEFT
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.x -= 45.f;

            pObject->Transform()->SetLocalPos(Pos);
            hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::LEFT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, -10.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
            Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            if (m_iPartyNum == 0)
            {
                Hit->SetPlayer(true);
            }
            else
            {
                Hit->SetPlayer(false);
            }
            Hit->SetiDamage(m_State->GetATK() * 1.5f);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //UPLEFT
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.y += 30.f;
            Pos.x -= 30.f;
            pObject->Transform()->SetLocalPos(Pos);

            hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::UPLEFT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, 10.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
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
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //UPRIGHT
            pObject = m_Skill1->Instantiate();
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
                hook->SetDir(DIR::UPRIGHT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, 30.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

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
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //DOWNLEFT
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.y -= 30.f;
            Pos.x -= 30.f;
            pObject->Transform()->SetLocalPos(Pos);

            hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::DOWNLEFT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, -30.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));

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
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttackeffect3");
            Hit->Seteffect(effect);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            //DOWNRIGHT
            pObject = m_Skill1->Instantiate();
            Pos = Transform()->GetLocalPos();
            Pos.y -= 30.f;
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
            pObject->Collider2D()->SetvOffsetPos(Vec2(25.f, -20.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
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
            effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttack3");
            Hit->Seteffect(effect);
            even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)pObject;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);
        }
    }
    if (m_CurrentCombo != m_PreCombo && m_CurrentCombo != 0 && PLAYER_STATE::ATTACK == m_eCurState)
    {
        CGameObject* pObject = nullptr;
        Vec3 Pos = Transform()->GetLocalPos();



        srand((unsigned int)time(NULL));
        int n = rand() % 10;
        if (n < 3)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"nari_attack2");
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            pObject = m_Attack2->Instantiate();

            CHitScript* Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
            if (m_iPartyNum == 0)
            {
                Hit->SetPlayer(true);
            }
            else
            {
                Hit->SetPlayer(false);
            }
            Hit->SetiDamage(m_State->GetATK() * 2);
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttackeffect2");
            Hit->Seteffect(effect);
        }
        else
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"nari_attack1");
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            pObject = m_Attack1->Instantiate();
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
            Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"NariAttackeffect");
            Hit->Seteffect(effect);

        }
        switch (m_AnimDir)
        {
        case DIR::UP:
        {
            Pos.y += 45.f;
            pObject->Transform()->SetLocalPos(Pos);

            CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::UP);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-10.f, 20.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
            Missile->SetTime(2.f);
        }
        break;
        case DIR::DOWN:
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
            pObject->Collider2D()->SetvOffsetPos(Vec2(10.f, -20.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
            Missile->SetTime(2.f);
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
            pObject->Collider2D()->SetvOffsetPos(Vec2(20.f, 10.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
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
            if (m_Target != nullptr)
            {
                Vec3 TargetPos = m_Target->Transform()->GetLocalPos();
                hook->SetTarget(Vec2(TargetPos.x, TargetPos.y));
            }
            else
                hook->SetDir(DIR::LEFT);
            pObject->Collider2D()->SetvOffsetPos(Vec2(-20.f, -10.f));
            pObject->Collider2D()->SetvOffsetScale(Vec2(0.5f, 1.f));
            CMissileScript* Missile = (CMissileScript*)pObject->GetScript(L"CMissileScript");
            Missile->SetTime(2.f);
        }
        break;
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