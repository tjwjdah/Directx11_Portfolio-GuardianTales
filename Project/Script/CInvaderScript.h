#pragma once
#include <Engine\CScript.h>

class CPrefab;
class CObjScript;

//CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer();

enum class InvaState {
    IDLE,
    WALK,
    ATTACK,
    DASH,
    NONE
};

class CObjState;
class CInvaderScript :
    public CScript
{
    Ptr<CPrefab>             m_Attack1;
    Ptr<CPrefab>             m_Attack11;
    Ptr<CPrefab>             m_Attack111;
    Ptr<CPrefab>             m_Attack2;

    DIR             m_curdir;
    DIR             m_predir;
    DIR   m_walkdir;
    DIR m_anidir;
    DIR m_AttackDir;

    Vec2 m_walknomal;
    Vec2  m_dashdir;
    MON_STATE       m_curstate;
    MON_STATE       m_prestate;

    Pattern         m_pattern;

    InvaState       m_State;

    UINT m_hp;
    UINT m_dashcount;
    UINT m_thundercount;

    UINT m_attacknum;
    UINT m_preattacknum;

    float m_speed;
    float m_maxspeed;

    float m_atime;
    float m_maxtime;

    bool m_aniflag;
    bool m_testflag;

    bool m_attackflag;
    bool m_attackflag2;
    float m_effecttime;

    //skill
    Vec3 m_savepos;
    float m_attackdashspeed;

    
    CDIR                m_eColliderDir;

    CObjState* m_ObjState;
    CGameObject* m_AttackObj;

    float     m_fThunderTime;

    bool      m_Die;
public:
    virtual void awake();
    virtual void update();

private:
    void checkdir();
    void idle();
    void attack();
    void walk();
    void playani();

    void loop();
    void move();

    //skill
    void Attack();
    void Thunder();
    void GuardDash();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
public:
    CLONE(CInvaderScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CInvaderScript();
    ~CInvaderScript();
};
