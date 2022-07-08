#pragma once
#include <Engine\CScript.h>

class CElecEffectScript :
    public CScript
{
private:
    bool m_IsCol;



public:
    bool GetIsCol() { return m_IsCol; }

    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CElecEffectScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecEffectScript();
    ~CElecEffectScript();
};