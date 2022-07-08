#pragma once
#include <Engine\CScript.h>

class CPrefab;
class CObjScript;

enum class BUG_STATE
{
    IDLE,
    ATTACK,
    INOUT,
    SPIN,
    DEAD,
    NONE
   
};

//CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer();
class CObjState;
class CBugMonsterScript :
    public CScript
{
    Ptr<CPrefab>             m_Attack1;
    Ptr<CPrefab>             m_Attack11;
    Ptr<CPrefab>             m_Attack2;

    BUG_STATE m_curstate;
    BUG_STATE m_prestate;
    Pattern m_pattern;

    BUG_STATE m_InOutState;

    float m_atime;
    float m_maxtime;
    float m_speed;
    UINT m_attacknum;

    
    float m_fInOutTime;


    bool m_aniflag;
    bool m_nextaniflag;
    bool m_effectaniflag;

    UINT m_preattacknum;

    bool m_didattack;

    //skill
    Vec3 m_savepos;
    float m_spinatime;
    UINT m_spincount;

    CDIR            m_eColliderDir;
    CObjState*      m_ObjState;

public:
    virtual void awake();
    virtual void update();

private:
    void checkstate();

    void idle();
    void attack();
    void playani();



    // skill
    void Attack();
    void AttackEffect(int _effectnum);
    void Spin();
    void InOut();

    void createbullet();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
public:
    CLONE(CBugMonsterScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CBugMonsterScript();
    ~CBugMonsterScript();
};
