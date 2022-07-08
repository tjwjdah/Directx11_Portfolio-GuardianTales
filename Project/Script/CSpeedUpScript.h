#pragma once
#include <Engine\CScript.h>

// obj name : 스피드 업 발판
// desc : 플레이어가 밟으면 빨라짐

class CPlayerScript;

class CSpeedUpScript :
    public CScript
{
private:
    bool                    m_bCol;                 //충돌중인가?
    int                     m_Dir;
    int                     m_PreDir;
    bool                    m_bIsSlide;            //미끄러졌는가?
     
    float                   m_fRotValue;           //90도
    bool                    m_bOneTime;             //한번만

public:
    //bool GetIsPushed() { return m_bIsPushed; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CSpeedUpScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CSpeedUpScript();
    ~CSpeedUpScript();
};
