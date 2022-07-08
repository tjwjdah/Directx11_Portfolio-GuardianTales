#pragma once
#include <Engine\CScript.h>

// obj name : 화로
// desc : 장작에 불을 붙임

class CPlayerScript;

enum class FIRE_STATE
{
    COL,
    HEAD,
    SLIDE,
    END,
    NONE
};

class CFireBowlScript :
    public CScript
{
private:

    //CPlayerScript*          m_pPlayerScript;
    bool m_bCol;

    FIRE_STATE              m_eState;
    Vec3                    m_vPos;
    Vec3                    m_vStartPos;
    DIR                     m_eDir;

    float                   m_fAtime;
    Vec2                    m_vSpeed;
    float                   m_fSpeed;
    float                   m_fAngle;
    float                   m_fAdjSpeed;

public:
    virtual void awake();
    virtual void update();

public:
    FIRE_STATE GetState() { return m_eState; }

private:
    void CheckState();
    void Move();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CFireBowlScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CFireBowlScript();
    ~CFireBowlScript();
};