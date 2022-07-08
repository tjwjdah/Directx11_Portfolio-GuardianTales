#pragma once
#include <Engine\CScript.h>


enum class MinoState {
    IDLE,
    WALK,
    ATTACKFIREBALL,
    ATTACKWAVE,
    ATTACKRUSH
};
class CObjState;
class CFSMScript;
class CMinotauros :
    public CScript
{
private:

    Ptr<CPrefab>             m_Attack1;
    Ptr<CPrefab>            m_Attack2;


    MinoState   m_State;

    Vec2        m_vTargetDir;
    Vec2        m_vRushSetDir;
    
    DIR         m_DIR;
    CDIR                m_eColliderDir;
    Pattern     m_Pattern;  

    float       m_fDistance;
    float       m_fMaxTime;
    float       m_fTime;
    
    float       m_fSpeed;

    bool        m_AinmOn;


    int         m_RushNum;

    CObjState*  m_ObjState;
public:

    void StateChange();

    void IDLE();
    void WALK();
    void ATTACKFIREBALL();
    void ATTACKWAVE();
    void ATTACKRUSH();
    
    void SetDir();

public:
    virtual void update();
    virtual void awake();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);

public:
    CLONE(CMinotauros);
    CMinotauros();
    ~CMinotauros();
};

