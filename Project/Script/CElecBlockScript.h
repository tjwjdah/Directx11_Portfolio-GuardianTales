
#pragma once
#include <Engine\CScript.h>

// obj name : 전기 블록(밀 수 있음)
// desc : 끝에 깨는 돌

class CPlayerScript;
class CObjEventScript;
class CElecBlockScript :
    public CScript
{
private:
    CScript* m_pTarScript;
    //CPlayerScript*          m_pPlayerScript;
    CObjEventScript*        m_pEventScript;
    bool                    m_bIsLinked;        //연결되었느가?
    bool                    m_bIsPushed;        //미는중인가?
    bool                    m_bIsCol;           //충돌중인가?

    CGameObject* m_Child;
    DIR                     m_pushdir;

    //bool m_stop;
    CDIR                m_eColliderDir;

public:
    bool GetIsPushed() { return m_bIsPushed; }
    bool GetIsLinked() { return m_bIsLinked; }
    void SetIsLinked(bool _link) { m_bIsLinked = _link; }


public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);

public:
    CLONE(CElecBlockScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CElecBlockScript();
    ~CElecBlockScript();
};