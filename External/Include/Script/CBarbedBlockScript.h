#pragma once
#include <Engine\CScript.h>

// obj name : 가시돋친 장애물
// desc : 플레이어의 체력을 깎음

class CPlayerScript;

class CBarbedBlockScript :
    public CScript
{
private:
    float                   m_fDir;                   //dir
    float                   m_fSpeed;
    float                   m_fRange;
    Vec2                    m_vStartPos;

    bool                    m_bCol;            //눌렸는가?


public:
    // bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBarbedBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CBarbedBlockScript();
    ~CBarbedBlockScript();
};