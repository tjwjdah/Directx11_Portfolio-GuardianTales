#include "pch.h"
#include "CBugMonsterScript.h"
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

#include "CPlayerScript.h"
#include "CFSMScript.h"
#include "CState_Idle.h"

#include "CDropMissileScript.h"
#include "CState_Trace.h"

#include "CTargetToAuto.h"
#include "CObjState.h"

#include "CHitScript.h"
#include "CMonsterScript.h"
CBugMonsterScript::CBugMonsterScript()
    : CScript((int)SCRIPT_TYPE::BUGMONSTERSCRIPT)
    , m_speed(100.f)
    , m_curstate(BUG_STATE::IDLE)
    , m_prestate(BUG_STATE::IDLE)
    , m_attacknum(0)
    , m_pattern(Pattern::NONE)
    , m_atime(0.f)
    , m_maxtime(3.f)
    , m_aniflag(false)
    , m_nextaniflag(false)
    , m_preattacknum(0)
    , m_effectaniflag(false)
    , m_didattack(false)
    , m_spinatime(0.f)
    , m_spincount(2)
    , m_fInOutTime(0.f)
    , m_InOutState(BUG_STATE::NONE)
    , m_ObjState(nullptr)
{
    m_eColliderDir.b_DOWN = false;
    m_eColliderDir.b_LEFT = false;
    m_eColliderDir.b_RIGHT = false;
    m_eColliderDir.b_UP = false;
}

CBugMonsterScript::~CBugMonsterScript() {}

void CBugMonsterScript::awake()
{
    m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"BugAttack1");
    m_Attack11 = CResMgr::GetInst()->FindRes<CPrefab>(L"BugAttack11");
    m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"BugAttack2");
    m_ObjState = (CObjState*)GetGameObject()->GetScript(L"CObjState");

    m_curstate = BUG_STATE::IDLE;
    m_atime = 0.f;
    m_maxtime = 3.f;
    m_pattern = Pattern::NONE;
    m_aniflag = false;
    CMonsterScript* Monster = (CMonsterScript*)GetGameObject()->GetScript(L"CMonsterScript");
    Monster->SetmMonster(Monster::BUG);
}

void CBugMonsterScript::update()
{
    if (m_ObjState->GetHp() > 0)
    {
        checkstate();
    }
    else
    {
        m_curstate = BUG_STATE::IDLE;
    }
    switch (m_curstate)
    {
    case BUG_STATE::IDLE:
    {
        m_InOutState = BUG_STATE::IDLE;
        idle();
        break;
    }
    case BUG_STATE::ATTACK:
    {
        m_InOutState = BUG_STATE::ATTACK;
        attack();
        break;
    }
    case BUG_STATE::DEAD:
    {
        break;
    }
    }



    playani();

}
void CBugMonsterScript::checkstate()
{

}

void CBugMonsterScript::idle() //3초
{
    m_atime += fDT;
    if (m_atime > m_maxtime)
    {
        m_atime = 0.f;
        m_maxtime = 1.f;
        m_prestate = BUG_STATE::IDLE;
        m_curstate = BUG_STATE::ATTACK;
        m_pattern = Pattern::START;
        m_aniflag = false;
        m_speed = 100.f;
        m_effectaniflag = false;
        m_spincount = 2;
        m_spinatime = 0.f;
        m_didattack = false;

        m_preattacknum = m_attacknum;

        srand((unsigned int)time(NULL));
        m_attacknum = rand() % 3;

        if (m_attacknum == m_preattacknum)
        {
            m_attacknum += 1;
            if (m_attacknum > 2) m_attacknum = 0;
        }

        //m_attacknum = 0; //회전
        //m_attacknum = 1; //토사물
        //m_attacknum = 2; //inout

    }
}

void CBugMonsterScript::attack() //회전
{
    m_atime += fDT;

    switch (m_pattern)
    {
    case Pattern::START: //1
    {
        if (Animator2D()->GetCurAnim()->IsFinish() && m_atime > m_maxtime)
        {
            m_atime = 0.f;
            m_maxtime = 5.f;
            m_pattern = Pattern::PLAY;
            m_aniflag = false;
        }
        break;
    }
    case Pattern::PLAY: //5
    {
        if (0 == m_attacknum) {
            m_InOutState = BUG_STATE::SPIN;
            Spin();
        }
        else if (1 == m_attacknum) Attack();
        else if (2 == m_attacknum) {
            m_InOutState = BUG_STATE::INOUT;
            InOut();
        }
        break;
    }
    case Pattern::LOOP://1
    {
        if (1 == m_attacknum)  AttackEffect(1);

        if (Animator2D()->GetCurAnim()->IsFinish() && m_atime > m_maxtime)
        {
            if (1 == m_attacknum) AttackEffect(2);

            m_pattern = Pattern::END;
            m_aniflag = false;
        }

        break;
    }
    case Pattern::END:
    {
        m_prestate = BUG_STATE::ATTACK;
        m_curstate = BUG_STATE::IDLE;
        m_atime = 0.f;
        m_maxtime = 3.f;
        m_pattern = Pattern::NONE;
        m_aniflag = false;
        break;
    }
    }


}

void CBugMonsterScript::AttackEffect(int _effectnum)
{
    CGameObject* pObject = nullptr;
    if (!m_didattack && _effectnum == 1)
    {

        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr) return;
        m_savepos = pPlayer->Transform()->GetLocalPos();
        // 토하는 이펙트
        pObject = m_Attack1->Instantiate();
        pObject->Transform()->SetLocalPos(m_savepos);
        pObject->Transform()->SetLocalScaleX(190.f);
        pObject->Transform()->SetLocalScaleY(250.f);
        //pObject->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
        pObject->Animator2D()->PlayAnimation(L"Attack1", false);
        CDropMissileScript* tar = (CDropMissileScript*)pObject->GetScript(L"CDropMissileScript");
        tar->Setoffsety(350.f);
        tar->SetSpeed(500.f);

        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObject;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);

        m_didattack = true;
    }

    //땅에 떨어진 토사물 이펙트
    if (!m_effectaniflag && _effectnum == 2)
    {
        CGameObject* pObject = nullptr;
        pObject = m_Attack11->Instantiate();
        pObject->Transform()->SetLocalPos(m_savepos);
        pObject->Transform()->SetLocalScaleX(128.f * 2.5f);
        pObject->Transform()->SetLocalScaleY(128.f * 2.f);
        //pObject->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
        pObject->Animator2D()->PlayAnimation(L"Attack11", false);

        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObject;
        //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
        even.wParam = (DWORD_PTR)30;
        CEventMgr::GetInst()->AddEvent(even);

        m_effectaniflag = true;
    }

}

void CBugMonsterScript::playani()
{
    if (m_prestate != m_curstate && m_aniflag == false)
    {
        switch (m_curstate)
        {
        case BUG_STATE::IDLE:
        {

            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"bug_idle");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            Animator2D()->PlayAnimation(L"IDLE", true);
            break;
        }

        case BUG_STATE::ATTACK:
        {
            if (0 == m_attacknum)
            {
                switch (m_pattern)
                {
                case Pattern::START:
                {
                    Animator2D()->PlayAnimation(L"SPINCASTREADY", false);
                    break;
                }

                case Pattern::PLAY:
                {
                    Animator2D()->PlayAnimation(L"SPIN", true);
                    break;
                }

                case Pattern::LOOP:
                {
                    Animator2D()->PlayAnimation(L"SPINCASTLP", false);
                    break;
                }

                }
            }
            if (1 == m_attacknum)
            {
                switch (m_pattern)
                {
                case Pattern::START:
                {
                    Animator2D()->PlayAnimation(L"ATTACKREADY", false);
                    break;
                }

                case Pattern::PLAY:
                {

                    Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"bug_pos");  //*********************
                    pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

                    Animator2D()->PlayAnimation(L"ATTACK", false); // 토 한번만 -> idle
                    break;
                }

                case Pattern::LOOP:
                {
                    Animator2D()->PlayAnimation(L"ATTACKREADYLOOP", false);
                    break;
                }

                }
            }

            if (2 == m_attacknum)
            {
                switch (m_pattern)
                {
                case Pattern::START:
                {
                    Animator2D()->PlayAnimation(L"IN", false);
                    break;
                }

                case Pattern::PLAY:
                {
                    //Animator2D()->PlayAnimation(L"OUT1", true);
                    break;
                }

                case Pattern::LOOP:
                {
                    Animator2D()->PlayAnimation(L"OUT1", false);
                    break;
                }

                }
            }

            break;
        }
        }
        m_aniflag = true;
    }

}


void CBugMonsterScript::OnCollisionEnter(CGameObject* _pOther)
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
            if (m_InOutState == BUG_STATE::INOUT && m_pattern == Pattern::PLAY)
            {
                Player->SetPlayerState(PLAYER_STATE::CRASH);
                m_fInOutTime = 0.f;
                m_atime = 0.f;
                m_maxtime = 1.f;
                m_pattern = Pattern::LOOP;
                m_aniflag = false;
                CObjState* m_State = Player->GetObjState();
                int Hp = m_State->GetHp() - m_ObjState->GetATK() * 2.f;
                m_State->SetHp(Hp);
                Player->SetHit(true);
            }
            if (m_InOutState == BUG_STATE::SPIN && m_pattern == Pattern::PLAY)
            {
                Player->SetPlayerState(PLAYER_STATE::CRASH);
                CObjState* m_State = Player->GetObjState();
                int Hp = m_State->GetHp() - m_ObjState->GetATK();
                m_State->SetHp(Hp);
                Player->SetHit(true);
            }
        }
    }

}

void CBugMonsterScript::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTileCollsion") || _pOther->GetScript(L"CPlayerScript"))
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

void CBugMonsterScript::OnCollision(CGameObject* _pOther)
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





void CBugMonsterScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}
void CBugMonsterScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}