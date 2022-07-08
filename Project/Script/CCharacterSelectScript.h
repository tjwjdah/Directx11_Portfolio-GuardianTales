#pragma once
#include <Engine\CScript.h>
class CCharacterSelectScript :
    public CScript
{

private:
    CGameObject* Player[4];
    POINT m_Res;

    CGameObject* m_DrapObj;
    Vec3         m_ObjPreDrapPos;
    int          m_DrapObjNum;
public:
    virtual void update();
    virtual void awake();
public:
  

public:
    CLONE(CCharacterSelectScript);

public:
    CCharacterSelectScript();
    ~CCharacterSelectScript();

};

