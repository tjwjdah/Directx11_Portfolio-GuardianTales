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
#include <Engine\CCollider2D.h>

#include <Engine\CScript.h>


#include "CPlayerScript.h"
#include "CTargetToAuto.h"
#include  "CHitScript.h"
#include "CObjState.h"
#include "CMonsterScript.h"
CInvaderScript::CInvaderScript() :
    CScript((int)SCRIPT_TYPE::INVADERSCRIPT)
    , m_Attack1(nullptr)
    , m_Attack11(nullptr)
    , m_Attack111(nullptr)
    , m_curdir(DIR::DOWN)
    , m_predir(DIR::UP)
    , m_curstate(MON_STATE::IDLE)
    , m_prestate(MON_STATE::IDLE)
    , m_pattern(Pattern::NONE)
    , m_atime(0.f)
    , m_attacknum(0)
    , m_maxtime(3.f)
    , m_speed(250.f)
    , m_maxspeed(650.f)
    , m_hp(100)
    , m_walkdir(DIR::DOWN)
    , m_testflag(false)
    , m_dashcount(3)
    , m_attackflag(false)
    , m_effecttime(0.f)
    , m_thundercount(2)
    , m_attackdashspeed(550.f)
    , m_State(InvaState::NONE)
    , m_ObjState(nullptr)
    , m_AttackObj(nullptr)
    , m_AttackDir(DIR::NONE)
    , m_fThunderTime(0.f)
    , m_attackflag2(false)
    , m_Die(false)
{
    m_eColliderDir.b_DOWN = false;
    m_eColliderDir.b_LEFT = false;
    m_eColliderDir.b_RIGHT = false;
    m_eColliderDir.b_UP = false;
}

CInvaderScript::~CInvaderScript() {}

void CInvaderScript::awake()
{
    m_Attack1 = CResMgr::GetInst()->FindRes<CPrefab>(L"InvaderAttack1");
    m_Attack11 = CResMgr::GetInst()->FindRes<CPrefab>(L"InvaderAttack1_effect");
    m_Attack111 = CResMgr::GetInst()->FindRes<CPrefab>(L"InvaderAttack1_four");
    m_Attack2 = CResMgr::GetInst()->FindRes<CPrefab>(L"InvaderAttack2");
    m_ObjState = (CObjState*)GetGameObject()->GetScript(L"CObjState");
    CMonsterScript* Monster = (CMonsterScript*)GetGameObject()->GetScript(L"CMonsterScript");
    Monster->SetmMonster(Monster::INVADER);
}

void CInvaderScript::update()
{
    if (m_ObjState->GetHp() > 0)
    {
        checkdir();

        switch (m_curstate)
        {
        case MON_STATE::IDLE:
        {
            m_State = InvaState::IDLE;
            idle();
            break;
        }
        case MON_STATE::WALK:
        {
            m_State = InvaState::WALK;
            walk();
            break;
        }
        case MON_STATE::ATTACK:
        {
            m_State = InvaState::ATTACK;
            attack();
            break;
        }
        case MON_STATE::DAMAGED:
        {

            break;
        }
        case MON_STATE::DEAD:
        {
            break;
        }
        }
        playani();
    }
    else
    {
        if (!m_Die)
        {

            Animator2D()->PlayAnimation(L"IDLE_DOWN", true);
            m_Die = true;
        }
    }

}

void CInvaderScript::checkdir() {

    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr) return;
    Vec3 monpos = Transform()->GetLocalPos();
    Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
    Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
    dir.Normalize();
    m_walknomal = dir;
    float _x = fabs(dir.x);
    float _y = fabs(dir.y);

    m_predir = m_curdir;

    if (dir.x > 0 && dir.y > 0)
    {
        if (_x > _y) m_curdir = DIR::RIGHT;
        else if (_x < _y) m_curdir = DIR::UP;
        else if (_x == _y) m_curdir = DIR::UPRIGHT;
    }
    else if (dir.x > 0 && dir.y < 0)
    {
        if (_x > _y) m_curdir = DIR::RIGHT;
        else if (_x < _y) m_curdir = DIR::DOWN;
        else if (_x == _y) m_curdir = DIR::DOWNRIGHT;
    }
    else if (dir.x < 0 && dir.y < 0)
    {
        if (_x > _y) m_curdir = DIR::LEFT;
        else if (_x < _y) m_curdir = DIR::DOWN;
        else if (_x == _y) m_curdir = DIR::DOWNLEFT;
    }
    else if (dir.x < 0 && dir.y > 0)
    {
        if (_x > _y) m_curdir = DIR::LEFT;
        else if (_x < _y) m_curdir = DIR::UP;
        else if (_x == _y) m_curdir = DIR::UPLEFT;
    }
    m_anidir = m_curdir;

    if (m_anidir == DIR::UPRIGHT || m_anidir == DIR::DOWNRIGHT) m_anidir = DIR::RIGHT;
    else if (m_anidir == DIR::UPLEFT || m_anidir == DIR::DOWNLEFT) m_anidir = DIR::LEFT;
}

void CInvaderScript::idle()
{
    srand((unsigned int)time(NULL));
    m_atime += fDT;
    if (m_atime > m_maxtime)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;
        Vec3 monpos = Transform()->GetLocalPos();
        Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
        Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
        float dlen = dir.Length();
        dir.Normalize();

        if (dlen > 300.f) { //멀면
            int n = rand() % 3;
            int dashcnt = rand() % 3 + 2;  //2~4 랜덤

            //똑같은 어택 방지
            if (n != 0 && n == m_preattacknum)
            {
                n++;
                if (n > 2) n = 1;
            }

            if (n == 0) //걷기
            {
                m_prestate = MON_STATE::IDLE;
                m_curstate = MON_STATE::WALK;
                m_atime = 0.f;
                m_maxtime = 5.f; //5초 
                m_walknomal = dir;
                m_walkdir = m_curdir;
            }
            else //attack 1,2
            {
                m_attacknum = n;
                m_atime = 0.f;
                m_maxtime = 1.f;
                m_prestate = MON_STATE::IDLE;
                m_curstate = MON_STATE::ATTACK; //next
                m_pattern = Pattern::START;
                m_aniflag = false;
                m_speed = 150.f;
                m_dashcount = dashcnt;  //랜덤?
                m_thundercount = dashcnt;
            }
        }
        else //가까우면
        {
            m_attacknum = rand() % 2;

            //똑같은 어택 방지
            if (m_attacknum == m_preattacknum)
            {
                m_attacknum++;
                if (m_attacknum > 1) m_attacknum = 0;
            }

            if (m_attacknum == 0) //칼질
            {
                m_atime = 0.f;
                m_prestate = MON_STATE::IDLE;
                m_curstate = MON_STATE::ATTACK;
                m_pattern = Pattern::PLAY; // 칼질은 바로 공격
                m_aniflag = false;
                m_speed = 150.f;
            }
            else if (m_attacknum == 1) //선더
            {
                m_atime = 0.f;
                m_prestate = MON_STATE::IDLE;
                m_curstate = MON_STATE::ATTACK;
                m_pattern = Pattern::START;
                m_aniflag = false;
                m_speed = 150.f;
                m_thundercount = 1;
            }
        }
    }
    m_preattacknum = m_attacknum;

    //test
    {
        //m_preattacknum = 1;
        //m_attacknum = 0;////////////////////////////////////////////////////////test
        //m_atime = 0.f;
        //m_prestate = MON_STATE::IDLE;
        //m_curstate = MON_STATE::ATTACK;
        //m_pattern = Pattern::PLAY; // 칼질은 바로 공격
        //m_aniflag = false;
        //m_attackflag = false;
        //m_speed = 100.f;
    }
    {
        //m_preattacknum = 2;
        //m_attacknum = 1;////////////////////////////////////////////////////////test
        //m_atime = 0.f;
        //m_prestate = MON_STATE::IDLE;
        //m_curstate = MON_STATE::ATTACK;
        //m_pattern = Pattern::START;
        //m_aniflag = false;
        //m_attackflag = false;
        //m_speed = 100.f;
    }


}

void CInvaderScript::walk()
{
    m_prestate = MON_STATE::WALK;
    m_curstate = MON_STATE::WALK;

    m_atime += fDT;
    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    Vec3 monpos = Transform()->GetLocalPos();
    Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
    Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
    float dlen = dir.Length();

    //걸어가기 (방향은 이미 정해져 있음)
    move();

    if (m_atime > 2.f /*m_maxtime*/) // ||dlen < 400.f) //5초이상 걷거나 범위 안에 들어왔을 때
    {
        srand((unsigned int)time(NULL));
        m_attacknum = rand() % 2; //칼질, 선더

        if (m_attacknum == 0) //칼질
        {
            m_atime = 0.f;
            m_prestate = MON_STATE::WALK;
            m_curstate = MON_STATE::ATTACK;
            m_pattern = Pattern::PLAY; // 칼질은 바로 공격
            m_aniflag = false;
            m_speed = 100.f;
        }
        else if (m_attacknum == 1) //선더
        {
            m_atime = 0.f;
            m_prestate = MON_STATE::WALK;
            m_curstate = MON_STATE::ATTACK;
            m_pattern = Pattern::START;
            m_aniflag = false;
            m_speed = 100.f;
        }
    }

}

void CInvaderScript::attack()
{
    m_atime += fDT;

    switch (m_pattern)
    {
    case Pattern::START: //1
    {
        if (Animator2D()->GetCurAnim()->IsFinish())
        {
            m_atime = 0.f;
            m_pattern = Pattern::PLAY;
            m_aniflag = false;

            CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
            Vec3 monpos = Transform()->GetLocalPos();
            Vec3 playerpos = pPlayer->Transform()->GetLocalPos();
            Vec2 dir = Vec2((playerpos.x - monpos.x), (playerpos.y - monpos.y));
            dir.Normalize();
            m_dashdir = dir;

            if (m_eColliderDir.b_UP == true)
            {
                if (m_dashdir.y > 0.f)
                    m_dashdir.y = 0.f;
            }
            if (m_eColliderDir.b_DOWN == true)
            {
                if (m_dashdir.y < 0.f)
                    m_dashdir.y = 0.f;
            }
            if (m_eColliderDir.b_RIGHT == true)
            {
                if (m_dashdir.x > 0.f)
                    m_dashdir.x = 0.f;
            }
            if (m_eColliderDir.b_LEFT == true)
            {
                if (m_dashdir.x < 0.f)
                    m_dashdir.x = 0.f;
            }



        }
        break;
    }
    case Pattern::PLAY: //5
    {
        if (0 == m_attacknum) Attack();
        else if (1 == m_attacknum) Thunder();
        else if (2 == m_attacknum)
        {
            GuardDash();
            m_State = InvaState::DASH;
        }
        break;
    }
    case Pattern::LOOP://1
    {
        m_atime += fDT;

        if (m_atime > 0.7f && m_attacknum == 1 && !m_attackflag) //선더 공격일때만
        {
            loop(); //4방향 구체 생성
        }

        //f (1 == m_attacknum && !m_attackflag) loop();

        if (Animator2D()->GetCurAnim()->IsFinish())// && m_atime > m_maxtime)
        {
            m_thundercount -= 1;
            if (m_thundercount < 0 || m_thundercount >= 4) m_thundercount = 0;   //버그 생김 

            if (m_attacknum == 1)
            {
                if (m_thundercount != 0)
                {
                    m_atime = 0.f;
                    m_pattern = Pattern::START;
                    m_aniflag = false;
                    m_attackflag = false;
                }
                else if (m_thundercount == 0)
                {
                    m_atime = 0.f;
                    m_pattern = Pattern::END;
                    m_aniflag = false;
                    m_attackflag = false;
                }
            }
            else
            {
                m_atime = 0.f;
                m_pattern = Pattern::END;
                m_aniflag = false;
                m_attackflag = false;
            }

        }

        break;
    }
    case Pattern::END:
    {
        m_prestate = MON_STATE::ATTACK;
        m_curstate = MON_STATE::IDLE;
        m_atime = 0.f;
        m_maxtime = 3.f;
        m_pattern = Pattern::NONE;
        m_aniflag = false;
        m_speed = 100.f;
        break;
    }
    }


}

void CInvaderScript::playani()
{
    if ((m_curstate == MON_STATE::WALK && m_curstate != m_prestate))
    {
        if (m_walkdir == DIR::UP) { Animator2D()->PlayAnimation(L"WALK_UP", true); }
        else if (m_walkdir == DIR::DOWN) { Animator2D()->PlayAnimation(L"WALK_DOWN", true); }
        else if (m_walkdir == DIR::LEFT || m_curdir == DIR::UPLEFT || m_curdir == DIR::DOWNLEFT) { Animator2D()->PlayAnimation(L"WALK_LEFT", true); }
        else if (m_walkdir == DIR::RIGHT || m_curdir == DIR::UPRIGHT || m_curdir == DIR::DOWNRIGHT) { Animator2D()->PlayAnimation(L"WALK_RIGHT", true); }
        return;
    }

    if (m_aniflag == false && (m_prestate != m_curstate))// || m_predir != m_curdir))
    {
        int a = 1;
        switch (m_curstate)
        {
        case MON_STATE::IDLE:
        {
            if (m_anidir == DIR::UP) { Animator2D()->PlayAnimation(L"IDLE_UP", true); }
            else if (m_anidir == DIR::DOWN) { Animator2D()->PlayAnimation(L"IDLE_DOWN", true); }
            else if (m_anidir == DIR::LEFT) { Animator2D()->PlayAnimation(L"IDLE_LEFT", true); }
            else if (m_anidir == DIR::RIGHT) { Animator2D()->PlayAnimation(L"IDLE_RIGHT", true); }
            break;
        }
        case MON_STATE::ATTACK:
        {
            if (0 == m_attacknum) //칼질
            {
                switch (m_pattern)
                {
                case Pattern::PLAY:
                {
                    if (m_anidir == DIR::UP) { Animator2D()->PlayAnimation(L"ATTACK_UP2", false); }
                    else if (m_anidir == DIR::DOWN) { Animator2D()->PlayAnimation(L"ATTACK_DOWN2", false); }
                    else if (m_anidir == DIR::LEFT) { Animator2D()->PlayAnimation(L"ATTACK_LEFT2", false); }
                    else if (m_anidir == DIR::RIGHT) { Animator2D()->PlayAnimation(L"ATTACK_RIGHT2", false); }
                    break;
                }
                }
            }
            else if (1 == m_attacknum) {

                switch (m_pattern)
                {

                case Pattern::START:
                {
                    Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"invader_thunderbolt");  //*********************
                    pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

                    Animator2D()->PlayAnimation(L"THUNDERSTART_DOWN", false); break;
                }
                case Pattern::PLAY:Animator2D()->PlayAnimation(L"THUNDER2_DOWN", false); break;
                case Pattern::LOOP:Animator2D()->PlayAnimation(L"THUNDEREND_DOWN", false); break;
                }
            }
            else if (2 == m_attacknum) {



                switch (m_pattern)
                {
                case Pattern::START:
                {
                    if (m_anidir == DIR::RIGHT) { Animator2D()->PlayAnimation(L"GAURDDASHREADY_RIGHT", false); }
                    else if (m_anidir == DIR::LEFT) { Animator2D()->PlayAnimation(L"GAURDDASHREADY_LEFT", false); }
                    else if (m_anidir == DIR::UP) { Animator2D()->PlayAnimation(L"EMBARR_UP", false); }
                    else if (m_anidir == DIR::DOWN) { Animator2D()->PlayAnimation(L"EMBARR_DOWN", false); }
                    break;
                }
                case Pattern::PLAY:
                {
                    if (m_anidir == DIR::UP) { Animator2D()->PlayAnimation(L"GAURD_UP", false); }
                    else if (m_anidir == DIR::DOWN) { Animator2D()->PlayAnimation(L"GAURD_DOWN", false); }
                    else if (m_anidir == DIR::LEFT) { Animator2D()->PlayAnimation(L"GAURD_LEFT", false); }
                    else if (m_anidir == DIR::RIGHT) { Animator2D()->PlayAnimation(L"GAURD_RIGHT", false); }

                    Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"invader_roar");  //*********************
                    pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

                    break;
                }
                case Pattern::LOOP:
                {
                    if (m_anidir == DIR::UP) { Animator2D()->PlayAnimation(L"EMBARR_UP", false); }
                    else if (m_anidir == DIR::DOWN) { Animator2D()->PlayAnimation(L"EMBARR_DOWN", false); }
                    else if (m_anidir == DIR::LEFT) { Animator2D()->PlayAnimation(L"EMBARR_LEFT", false); }
                    else if (m_anidir == DIR::RIGHT) { Animator2D()->PlayAnimation(L"EMBARR_RIGHT", false); }
                    break;
                }
                }
            }  //대시

        }
        }
        m_aniflag = true;
    }

}

void CInvaderScript::loop()
{


    CGameObject* pObject = nullptr;
    //Vec3 PlayerPos = CSceneMgr::GetInst()->FindPlayer()->Transform()->GetLocalPos();

    //4방향 공격
    //UP
    pObject = m_Attack111->Instantiate();
    CHitScript* Hit;
    Ptr<CPrefab> effect = CResMgr::GetInst()->FindRes<CPrefab>(L"InveHit");
    //m_savepos.y += 45.f;
    pObject->Transform()->SetLocalPos(m_savepos);


    CTargetToAuto* hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
    hook->SetDir(DIR::UP);
    hook->SetCoSetPos(Vec2(60.f, 60.f));
    pObject->Transform()->SetLocalScaleX(250.f);
    pObject->Transform()->SetLocalScaleY(150.f);

    pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.25f));  //y x

    Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
    int Damage = m_ObjState->GetATK() * 1.5f;
    Hit->SetiDamage(Damage);
    Hit->Seteffect(effect);


    tEvent even = {};
    even.eEvent = EVENT_TYPE::CREATE_OBJECT;
    even.lParam = (DWORD_PTR)pObject;
    //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
    even.wParam = (DWORD_PTR)30;
    CEventMgr::GetInst()->AddEvent(even);

    //DOWN
    m_savepos.x += 20;
    pObject = m_Attack111->Instantiate();
    pObject->Transform()->SetLocalPos(m_savepos);

    hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
    hook->SetDir(DIR::DOWN);
    pObject->Transform()->SetLocalScaleX(250.f);
    pObject->Transform()->SetLocalScaleY(150.f);
    hook->SetCoSetPos(Vec2(60.f, 60.f));
    pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.25f));

    Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
    Damage = m_ObjState->GetATK() * 1.5f;
    Hit->SetiDamage(Damage);
    Hit->Seteffect(effect);

    even = {};
    even.eEvent = EVENT_TYPE::CREATE_OBJECT;
    even.lParam = (DWORD_PTR)pObject;
    //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
    even.wParam = (DWORD_PTR)30;
    CEventMgr::GetInst()->AddEvent(even);

    //RIGHT
    pObject = m_Attack111->Instantiate();
    pObject->Transform()->SetLocalPos(m_savepos);

    hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
    hook->SetDir(DIR::RIGHT);
    pObject->Transform()->SetLocalScaleX(250.f);
    pObject->Transform()->SetLocalScaleY(150.f);
    hook->SetCoSetPos(Vec2(60.f, 60.f));
    pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.25f));

    Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
    Damage = m_ObjState->GetATK() * 1.5f;
    Hit->SetiDamage(Damage);
    Hit->Seteffect(effect);

    even = {};
    even.eEvent = EVENT_TYPE::CREATE_OBJECT;
    even.lParam = (DWORD_PTR)pObject;
    //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
    even.wParam = (DWORD_PTR)30;
    CEventMgr::GetInst()->AddEvent(even);


    //LEFT
    pObject = m_Attack111->Instantiate();
    pObject->Transform()->SetLocalPos(m_savepos);
    hook = (CTargetToAuto*)pObject->GetScript(L"CTargetToAuto");
    hook->SetDir(DIR::LEFT);
    pObject->Transform()->SetLocalScaleX(250.f);
    pObject->Transform()->SetLocalScaleY(150.f);
    hook->SetCoSetPos(Vec2(60.f, 60.f));
    pObject->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.25f));

    Hit = (CHitScript*)pObject->GetScript(L"CHitScript");
    Damage = m_ObjState->GetATK() * 1.5f;
    Hit->SetiDamage(Damage);
    Hit->Seteffect(effect);

    even = {};
    even.eEvent = EVENT_TYPE::CREATE_OBJECT;
    even.lParam = (DWORD_PTR)pObject;
    //even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
    even.wParam = (DWORD_PTR)30;
    CEventMgr::GetInst()->AddEvent(even);

    m_attackflag = true;

}


void CInvaderScript::move()
{

    Vec3 vPos = Transform()->GetLocalPos();


    if (m_eColliderDir.b_UP == true)
    {
        if (m_walknomal.y > 0.f)
            m_walknomal.y = 0.f;
    }
    if (m_eColliderDir.b_DOWN == true)
    {
        if (m_walknomal.y < 0.f)
            m_walknomal.y = 0.f;
    }
    if (m_eColliderDir.b_RIGHT == true)
    {
        if (m_walknomal.x > 0.f)
            m_walknomal.x = 0.f;
    }
    if (m_eColliderDir.b_LEFT == true)
    {
        if (m_walknomal.x < 0.f)
            m_walknomal.x = 0.f;
    }



    vPos.y += m_walknomal.y * fDT * m_speed;
    vPos.x += m_walknomal.x * fDT * m_speed;

    Transform()->SetLocalPos(vPos);
}


void CInvaderScript::OnCollisionEnter(CGameObject* _pOther)
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
            if (m_State == InvaState::DASH && m_pattern == Pattern::PLAY)
            {
                Player->SetPlayerState(PLAYER_STATE::CRASH);
                Player->SetHit(true);
                m_pattern = Pattern::LOOP;
                m_dashcount == 1;
                CObjState* m_State = Player->GetObjState();
                int Hp = m_State->GetHp() - m_ObjState->GetATK() * 2.f;
                m_State->SetHp(Hp);
            }

        }
    }

}

void CInvaderScript::OnCollisionExit(CGameObject* _pOther)
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

void CInvaderScript::OnCollision(CGameObject* _pOther)
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


void CInvaderScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}
void CInvaderScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}