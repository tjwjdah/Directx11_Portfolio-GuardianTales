
#pragma once
#include <Engine\CScript.h>

// obj name : 전기 타워 (자식)
// desc : 

enum class estate
{
    link,
    block,
    none
};


class CElecEffectScript;
class CElecBlockScript;

class CElecChildScript :
    public CScript
{
private:
    estate m_state;

    Ptr<CPrefab>            m_effect;

    vector<CScript*>        m_vecScript;
    CScript* m_pTarScript;

    CGameObject* m_effobj;
    CElecEffectScript* m_pEffectScript;

    float                   m_fMinDir;
    bool                    m_bIsCol;

    //eff ani
    bool m_bAni;
    bool m_bAni2;

    void checkstate();


public:
    void SetElecState(estate _s) { m_state = _s; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CElecChildScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecChildScript();
    ~CElecChildScript();
};