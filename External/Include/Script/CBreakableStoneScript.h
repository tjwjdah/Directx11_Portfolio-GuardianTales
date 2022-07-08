#pragma once
#include <Engine\CScript.h>

// obj name : 부술 수 있는 돌( 큰돌 )
// desc : 플레이어가 깰 수 있음, 지나갈 수 없음

class CPlayerScript;
class CGameObject;
class CBreakableStoneScript :
    public CScript
{
private:
    bool                    m_bIsCol;          //충돌중?
    bool                    m_bIsBreak;        //돌 부셨는가?
    bool m_delete; //삭제
    bool m_end;
    bool m_ani;

    float                   m_fAtime;
    Ptr<CPrefab>             m_effect;
    //CGameObject* m_pObject;

public:
    bool GetIsBreak() { return m_bIsBreak; }
    void SetIsBreak(bool _break) { m_bIsBreak = _break; }

public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBreakableStoneScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBreakableStoneScript();
    ~CBreakableStoneScript();
};