
#pragma once
#include <Engine\CScript.h>

// obj name : 일반 장애물
// desc : 장애물

class CPlayerScript;

class CBlockScript :
    public CScript
{
private:

    //  CPlayerScript*          m_pPlayerScript;        //플레이어 참조
    //  bool                    m_bIsPushed;            //눌렸는가?


public:
    //    bool GetIsPushed() { return m_bIsPushed; }

public:
    virtual void awake();
    virtual void update();


public:
    //virtual void OnCollisionEnter(CGameObject* _pOther);
    //virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBlockScript();
    ~CBlockScript();
};
