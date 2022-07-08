#pragma once
#include <Engine\CScript.h>

// obj name : 마무리 돌
// desc : 끝에 깨는 돌

class CPlayerScript;

class CEndBlockScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pStoneTex;       //tex
    Ptr<CPrefab>            m_pEndEffect;
    Ptr<CMaterial>          m_pMtrl;           //material

    CGameObject* m_pChildEffect;

    float m_fAtime;
    bool m_bIsPushed;
    bool m_bIsEnd;

    bool m_Ani;
    float m_EndTime;

    int   m_StageNum;
public:


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CEndBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CEndBlockScript();
    ~CEndBlockScript();
};