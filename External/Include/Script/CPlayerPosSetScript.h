#pragma once
#include <Engine\CScript.h>

class CGameObject;
class CPlayerPosSetScript :
    public CScript
{
private:
    CGameObject* m_TargetObj;

public:
    virtual void update();
    
public:
    void SetTarget(CGameObject* _Obj) { m_TargetObj = _Obj; }

public:
    CLONE(CPlayerPosSetScript);

public:
    CPlayerPosSetScript();
    ~CPlayerPosSetScript();

};

