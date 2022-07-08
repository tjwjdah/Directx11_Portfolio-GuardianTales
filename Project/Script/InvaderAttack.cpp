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

#include "CPlayerPosSetScript.h"
#include "CMissileScript.h"
#include "CHitScript.h"
#include "CObjState.h"
void CInvaderScript::Attack()
{

    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr) return;
    Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
    Vec3 Monpos = Transform()->GetLocalPos();
    Vec2 dir = Vec2((playerpos.x - Monpos.x), (playerpos.y - Monpos.y));

    if (!m_attackflag)
    {


        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"invader_attack");  //*********************
        pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

        m_AttackObj = m_Attack2->Instantiate();
        Vec3 Pos = Transform()->GetLocalPos();
        switch (m_anidir)
        {
        case DIR::UP:
        {
            Pos.y += 36.f;
            m_AttackObj->Transform()->SetLocalPos(Pos);
            m_AttackObj->Transform()->SetLocalScaleX(256.f);
            m_AttackObj->Transform()->SetLocalScaleY(105.f);


        }
        break;
        case DIR::DOWN:
        {
            Pos.y -= 36.f;
            m_AttackObj->Transform()->SetLocalPos(Pos);
            m_AttackObj->Transform()->SetLocalScaleX(256.f);
            m_AttackObj->Transform()->SetLocalScaleY(105.f);

        }
        break;
        case DIR::RIGHT:
        {
            Pos.x += 36.f;
            m_AttackObj->Transform()->SetLocalPos(Pos);
            m_AttackObj->Transform()->SetLocalScaleX(105.f);
            m_AttackObj->Transform()->SetLocalScaleY(256.f);

        }
        break;
        case DIR::LEFT:
        {
            Pos.x -= 36.f;
            m_AttackObj->Transform()->SetLocalPos(Pos);
            m_AttackObj->Transform()->SetLocalScaleX(105.f);
            m_AttackObj->Transform()->SetLocalScaleY(256.f);

        }
        break;
        }
        CHitScript* Hit = (CHitScript*)m_AttackObj->GetScript(L"CHitScript");
        Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"AttackHit");
        int Damage = m_ObjState->GetATK();

        Hit->SetiDamage(Damage);
        Hit->Seteffect(effect);

        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)m_AttackObj;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);
        m_attackflag = true;
        m_AttackDir = m_anidir;
    }
    float dlen = dir.Length();

    dir.Normalize();

    if (m_eColliderDir.b_UP == true)
    {
        if (dir.y > 0.f)
            dir.y = 0.f;
    }
    if (m_eColliderDir.b_DOWN == true)
    {
        if (dir.y < 0.f)
            dir.y = 0.f;
    }
    if (m_eColliderDir.b_RIGHT == true)
    {
        if (dir.x > 0.f)
            dir.x = 0.f;
    }
    if (m_eColliderDir.b_LEFT == true)
    {
        if (dir.x < 0.f)
            dir.x = 0.f;
    }



    Monpos.x += dir.x * fDT * m_speed;
    Monpos.y += dir.y * fDT * m_speed;
    Transform()->SetLocalPos(Monpos);

    if (m_AttackObj != nullptr)
    {
        switch (m_AttackDir)
        {
        case DIR::UP:

            m_AttackObj->Transform()->SetLocalPos(Vec3(Monpos.x, Monpos.y + 115.f, Monpos.z));
            break;
        case DIR::DOWN:

            m_AttackObj->Transform()->SetLocalPos(Vec3(Monpos.x, Monpos.y - 115.f, Monpos.z));
            break;
        case DIR::RIGHT:

            m_AttackObj->Transform()->SetLocalPos(Vec3(Monpos.x + 115.f, Monpos.y, Monpos.z));
            break;
        case DIR::LEFT:

            m_AttackObj->Transform()->SetLocalPos(Vec3(Monpos.x - 115.f, Monpos.y, Monpos.z));
            break;
        }

    }



    //공격 충돌체 , effect 추가







    if (Animator2D()->GetCurAnim()->IsFinish()) //애니 한번만 재생 후 play패턴에서 바로 idle상태로
    {
        m_prestate = MON_STATE::ATTACK;
        m_curstate = MON_STATE::IDLE;
        m_atime = 0.f;
        m_maxtime = 2.f;
        m_pattern = Pattern::NONE;
        m_aniflag = false;
        m_attackflag = false;
        m_attackdashspeed = 1000.f;

        if (m_AttackObj != nullptr)
        {
            tEvent _temp = {};
            _temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
            _temp.lParam = (DWORD_PTR)m_AttackObj;
            CEventMgr::GetInst()->AddEvent(_temp);
            m_AttackObj = nullptr;
        }
    }

}
