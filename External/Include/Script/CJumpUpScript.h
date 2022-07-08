#pragma once
#include <Engine\CScript.h>

// obj name : 점프 버튼
// desc : 플레이어가 밟으면 특정 조건 (문이 열린다거나) 실행

class CPlayerScript;

class CJumpUpScript :
    public CScript
{
private:
    int                     m_Dir;
    int                     m_PreDir;
    bool                    m_bIsPushed;            //눌렸는가?
    float                   m_fAtime;               //스피드 유지되는 시간
    float                   m_fRotValue;            //90도
    bool                    m_bFlag; //test

public:
    bool GetIsPushed() { return m_bIsPushed; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CJumpUpScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CJumpUpScript();
    ~CJumpUpScript();
};
