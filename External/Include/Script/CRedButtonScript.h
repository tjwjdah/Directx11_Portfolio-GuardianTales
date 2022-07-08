#pragma once
#include <Engine\CScript.h>

// obj name : 빨간 버튼
// desc : 플레이어가 밟으면 특정 조건 (문이 열린다거나) 실행

class CObjEventScript;

class CRedButtonScript :
    public CScript
{
private:

    CObjEventScript* m_pEventScript;         //EventScript



public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CRedButtonScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CRedButtonScript();
    ~CRedButtonScript();
};
