#pragma once
#include <Engine\CScript.h>

// obj name : 전기 타워 (부모)
// desc : 

class CPlayerScript;

class CElecTowerScript :
    public CScript
{
private:
    CScript* m_pTarScript;
    // CPlayerScript*          m_pPlayerScript;
    bool                    m_bIsCol;


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CElecTowerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecTowerScript();
    ~CElecTowerScript();
};