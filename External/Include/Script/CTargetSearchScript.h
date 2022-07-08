#pragma once
#include <Engine\CScript.h>



class CTargetSearchScript :
    public CScript
{
private:
    vector<CGameObject*> m_TargetList;

    CGameObject*        m_Target;
    float               m_fMinDistance;
    
 
public:
    virtual void update();
    virtual void awake();

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
public:
    CLONE(CTargetSearchScript);
    CTargetSearchScript();
    ~CTargetSearchScript();



};

