#include "pch.h"
#include "CSapa.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CEventMgr.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CMeshRender.h>
#include <Engine\CCollider2D.h>
#include  "CHitScript.h"
#include <Engine\CScript.h>

#include "CPlayerScript.h"
#include "CObjState.h"
#include "CMonsterScript.h"
CSapa::CSapa() :CScript((int)SCRIPT_TYPE::SAPA)
, m_fDistance(0.f)
, m_vTargetDir(0.f, 0.f)
, m_vRushSetDir(0.f, 0.f)
, m_State(SapaState::IDLE)
, m_DIR(DIR::DOWN)
, m_Pattern(Pattern::START)
, m_AinmOn(false)
, m_fTime(0.f)
, m_fMaxTime(0.f)
, m_fSpeed(300.f)
, m_BobmNum(0)
, m_vTelpoPos(0.f, 0.f, 0.f)
, m_OraObj(nullptr)
{
    m_eColliderDir.b_DOWN = false;
    m_eColliderDir.b_LEFT = false;
    m_eColliderDir.b_RIGHT = false;
    m_eColliderDir.b_UP = false;
}

CSapa::~CSapa()
{
}

void CSapa::awake()
{
    m_TelPo = CResMgr::GetInst()->FindRes<CPrefab>(L"Telpo");
    m_BobmStart = CResMgr::GetInst()->FindRes<CPrefab>(L"BobmStart");
    m_Bobm = CResMgr::GetInst()->FindRes<CPrefab>(L"Bobm");
    m_Jin = CResMgr::GetInst()->FindRes<CPrefab>(L"Jin");
    m_Ora = CResMgr::GetInst()->FindRes<CPrefab>(L"Ora");
    m_ObjState = (CObjState*)GetGameObject()->GetScript(L"CObjState");
    CMonsterScript* Monster = (CMonsterScript*)GetGameObject()->GetScript(L"CMonsterScript");
    Monster->SetmMonster(Monster::SAPA);
}

void CSapa::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTileCollsion"))
    {


        float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
        float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
        float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
        float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
        if (cleft < cdown && cleft < cright && cleft < cup)
        {
            m_eColliderDir.b_LEFT = true;
        }
        else if (cdown < cleft && cdown < cright && cdown < cup)
        {
            m_eColliderDir.b_DOWN = true;
        }
        else if (cright < cdown && cright < cleft && cright < cup)
        {
            m_eColliderDir.b_RIGHT = true;
        }
        else if (cup < cdown && cup < cright && cup < cleft)
        {
            m_eColliderDir.b_UP = true;
        }



    }
    else if (_pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        if (Player->GetAuto() == 0)
        {
            float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
            float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
            float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
            float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
            if (cleft < cdown && cleft < cright && cleft < cup)
            {
                m_eColliderDir.b_LEFT = true;
            }
            else if (cdown < cleft && cdown < cright && cdown < cup)
            {
                m_eColliderDir.b_DOWN = true;
            }
            else if (cright < cdown && cright < cleft && cright < cup)
            {
                m_eColliderDir.b_RIGHT = true;
            }
            else if (cup < cdown && cup < cright && cup < cleft)
            {
                m_eColliderDir.b_UP = true;
            }
        }
    }

}

void CSapa::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTileCollsion"))
    {
        m_eColliderDir.b_RIGHT = false;

        m_eColliderDir.b_LEFT = false;

        m_eColliderDir.b_UP = false;

        m_eColliderDir.b_DOWN = false;

    }
    else if (_pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        if (Player->GetAuto() == 0)
        {
            m_eColliderDir.b_RIGHT = false;

            m_eColliderDir.b_LEFT = false;

            m_eColliderDir.b_UP = false;

            m_eColliderDir.b_DOWN = false;
        }
    }

}

void CSapa::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTileCollsion"))
    {

        float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
        float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
        float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
        float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
        if (cleft < cdown && cleft < cright && cleft < cup)
        {
            m_eColliderDir.b_LEFT = true;
        }
        else if (cdown < cleft && cdown < cright && cdown < cup)
        {
            m_eColliderDir.b_DOWN = true;
        }
        else if (cright < cdown && cright < cleft && cright < cup)
        {
            m_eColliderDir.b_RIGHT = true;
        }
        else if (cup < cdown && cup < cright && cup < cleft)
        {
            m_eColliderDir.b_UP = true;
        }
    }
    else if (_pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        if (Player->GetAuto() == 0)
        {
            float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
            float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
            float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
            float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);
            if (cleft < cdown && cleft < cright && cleft < cup)
            {
                m_eColliderDir.b_LEFT = true;
            }
            else if (cdown < cleft && cdown < cright && cdown < cup)
            {
                m_eColliderDir.b_DOWN = true;
            }
            else if (cright < cdown && cright < cleft && cright < cup)
            {
                m_eColliderDir.b_RIGHT = true;
            }
            else if (cup < cdown && cup < cright && cup < cleft)
            {
                m_eColliderDir.b_UP = true;
            }
        }
    }

}




void CSapa::update()
{
    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    m_vTargetDir.x = pPlayer->Transform()->GetWorldPos().x - Transform()->GetWorldPos().x;
    m_vTargetDir.y = pPlayer->Transform()->GetWorldPos().y - Transform()->GetWorldPos().y;
    m_fDistance = m_vTargetDir.Length();

    m_vTargetDir.Normalize();


    if (m_eColliderDir.b_UP == true)
    {
        if (m_vTargetDir.y > 0.f)
            m_vTargetDir.y = 0.f;
    }
    if (m_eColliderDir.b_DOWN == true)
    {
        if (m_vTargetDir.y < 0.f)
            m_vTargetDir.y = 0.f;
    }
    if (m_eColliderDir.b_RIGHT == true)
    {
        if (m_vTargetDir.x > 0.f)
            m_vTargetDir.x = 0.f;
    }
    if (m_eColliderDir.b_LEFT == true)
    {
        if (m_vTargetDir.x < 0.f)
            m_vTargetDir.x = 0.f;
    }

    if (m_ObjState->GetHp() > 0)
    {
        StateChange();
    }
    else {
        m_State = SapaState::IDLE;
        m_DIR = DIR::DOWN;
        m_Pattern = Pattern::START;
    }



    switch (m_State)
    {
    case SapaState::IDLE:
    {
        IDLE();

    }
    break;
    case SapaState::WALK:
    {
        WALK();
    }
    break;
    case SapaState::TELEPORT:
    {
        TELEPORT();
    }
    break;
    case SapaState::ATTACKJINGAK:
    {
        ATTACKJINGAK();

    }
    break;
    case SapaState::ATTACKBOBM:
    {
        ATTACKBOBM();

    }
    break;
    case SapaState::ATTACKORARUSH:
    {
        ATTACKORARUSH();
    }
    break;
    }



}


void CSapa::StateChange()
{
    if (m_Pattern == Pattern::NONE)
    {

        SetDir();

        if (m_fDistance > 300.f)
        {
            m_State = SapaState::TELEPORT;
        }
        else if (m_fDistance > 100.f && m_fDistance < 300.f)
        {
            m_State = SapaState::WALK;
        }
        else
        {
            srand((unsigned int)time(NULL));
            int n = rand() % 3;
            if (n == 0)
                m_State = SapaState::ATTACKBOBM;
            else if (n == 1)
                m_State = SapaState::ATTACKJINGAK;
            else if (n == 2)
                m_State = SapaState::ATTACKORARUSH;
        }
        m_Pattern = Pattern::START;
    }
}

void CSapa::IDLE()
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
                Animator2D()->PlayAnimation(L"IDLE_UP");
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"IDLE_DOWN");
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"IDLE_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"IDLE_LEFT");
                break;
            }
            m_AinmOn = true;
            m_fMaxTime = 1.0f;
        }

        m_fTime += fDT;

        if (m_fTime > m_fMaxTime)
        {
            m_Pattern = Pattern::NONE;
            m_fTime = 0;
            m_AinmOn = false;
        }

    }
    break;
    case Pattern::END:
    {

    }
    break;
    case Pattern::NONE:
    {

    }
    break;
    }
}

void CSapa::WALK()
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
                Animator2D()->PlayAnimation(L"WALK_UP");
                break;
            case DIR::DOWN:
                Animator2D()->PlayAnimation(L"WALK_DOWN");
                break;
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"WALK_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"WALK_LEFT");
                break;

            }

            m_Pattern = Pattern::PLAY;
            m_fMaxTime = 0.5f;
            m_fTime = 0.f;
            m_vRushSetDir = m_vTargetDir;
        }

    }
    break;
    case Pattern::LOOP:
    {

    }
    break;
    case Pattern::PLAY:
    {


        Vec3 vSapaPos = Transform()->GetLocalPos();

        if (m_eColliderDir.b_UP == true)
        {
            if (m_vRushSetDir.y > 0.f)
                m_vRushSetDir.y = 0.f;
        }
        if (m_eColliderDir.b_DOWN == true)
        {
            if (m_vRushSetDir.y < 0.f)
                m_vRushSetDir.y = 0.f;
        }
        if (m_eColliderDir.b_RIGHT == true)
        {
            if (m_vRushSetDir.x > 0.f)
                m_vRushSetDir.x = 0.f;
        }
        if (m_eColliderDir.b_LEFT == true)
        {
            if (m_vRushSetDir.x < 0.f)
                m_vRushSetDir.x = 0.f;
        }

        vSapaPos.x += m_vRushSetDir.x * fDT * m_fSpeed;
        vSapaPos.y += m_vRushSetDir.y * fDT * m_fSpeed;
        Transform()->SetLocalPos(vSapaPos);

        m_fTime += fDT;
        if (m_fMaxTime < m_fTime)
        {
            m_Pattern = Pattern::END;
            m_fTime = 0;
        }

    }
    break;
    case Pattern::END:
    {
        m_vRushSetDir.x = 0;
        m_vRushSetDir.y = 0;
        SetDir();
        srand((unsigned int)time(NULL));
        int n = rand() % 3;
        if (n == 0)
            m_State = SapaState::ATTACKBOBM;
        else if (n == 1)
            m_State = SapaState::ATTACKJINGAK;
        else if (n == 2)
            m_State = SapaState::ATTACKORARUSH;
        m_Pattern = Pattern::START;
    }
    break;
    case Pattern::NONE:
    {

    }
    break;
    }
}

void CSapa::TELEPORT()
{
    m_TelPo;
    switch (m_Pattern)
    {
    case Pattern::START:
    {

        Transform()->SetLocalPosX(9999.f);
        Transform()->SetLocalPosY(9999.f);

        m_Pattern = Pattern::LOOP;
        m_fMaxTime = 0.5f;
        m_fTime = 0.f;



    }
    break;
    case Pattern::LOOP:
    {
        if (!m_AinmOn && m_fTime > 0.25f)
        {
            CGameObject* CObj = m_TelPo->Instantiate();
            CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
            switch (m_DIR)
            {
            case DIR::UP:
            {

                m_vTelpoPos = pPlayer->Transform()->GetLocalPos();
                m_vTelpoPos.y -= 100.f;
                //Transform()->SetLocalPos(vSapa);
            }
            break;
            case DIR::DOWN:
            {

                m_vTelpoPos = pPlayer->Transform()->GetLocalPos();
                m_vTelpoPos.y += 100.f;

            }
            break;
            case DIR::RIGHT:
            {

                m_vTelpoPos = pPlayer->Transform()->GetLocalPos();
                m_vTelpoPos.x -= 100.f;

            }
            break;
            case DIR::LEFT:
            {

                m_vTelpoPos = pPlayer->Transform()->GetLocalPos();
                m_vTelpoPos.x += 100.f;

            }
            break;
            }

            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sapa_tel");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            CObj->Transform()->SetLocalPos(Vec3(m_vTelpoPos.x, m_vTelpoPos.y + 64.f, m_vTelpoPos.z));

            tEvent even = {};
            even.eEvent = EVENT_TYPE::CREATE_OBJECT;
            even.lParam = (DWORD_PTR)CObj;
            //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
            even.wParam = (DWORD_PTR)30;
            CEventMgr::GetInst()->AddEvent(even);

            m_AinmOn = true;
        }
        m_fTime += fDT;
        if (m_fMaxTime < m_fTime)
        {
            m_Pattern = Pattern::PLAY;
            m_fTime = 0;
            m_AinmOn = false;
        }


        //번개 이펙트
    }
    break;
    case Pattern::PLAY:
    {
        switch (m_DIR)
        {
        case DIR::UP:
            Animator2D()->PlayAnimation(L"IDLE_UP");
            break;
        case DIR::DOWN:
            Animator2D()->PlayAnimation(L"IDLE_DOWN");
            break;
        case DIR::RIGHT:
            Animator2D()->PlayAnimation(L"IDLE_RIGHT");
            break;
        case DIR::LEFT:
            Animator2D()->PlayAnimation(L"IDLE_LEFT");
            break;
        }

        Transform()->SetLocalPos(m_vTelpoPos);
        m_Pattern = Pattern::END;
    }
    break;
    case Pattern::END:
    {
        SetDir();
        srand((unsigned int)time(NULL));
        int n = rand() % 3;
        if (n == 0)
            m_State = SapaState::ATTACKBOBM;
        else if (n == 1)
            m_State = SapaState::ATTACKJINGAK;
        else if (n == 2)
            m_State = SapaState::ATTACKORARUSH;
        m_Pattern = Pattern::START;
    }
    break;
    case Pattern::NONE:
        break;
    }
}



void CSapa::SetDir()
{
    if (m_vTargetDir.y >= 0)
    {
        if (m_vTargetDir.y > fabs(m_vTargetDir.x)) {
            m_DIR = DIR::UP;
        }
        else
        {
            if (m_vTargetDir.x > 0)
            {
                m_DIR = DIR::RIGHT;
            }
            else
            {
                m_DIR = DIR::LEFT;
            }
        }
    }
    else
    {
        if (fabs(m_vTargetDir.y) > fabs(m_vTargetDir.x)) {
            m_DIR = DIR::DOWN;
        }
        else
        {
            if (m_vTargetDir.x > 0)
            {
                m_DIR = DIR::RIGHT;
            }
            else
            {
                m_DIR = DIR::LEFT;
            }
        }
    }

}