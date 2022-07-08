#pragma once
#include <Engine\CScript.h>

// obj name : 气藕 采
// desc : 气藕 积己

enum class FLOWER_STATE
{
    IDLE,
    COL,
    BOMB,
    HEAD,
    NONE,
    MAKEBOMB,
    EXP, //气惯
};

class CPlayerScript;
class CScene;

class CBombFlowerScript :
    public CScript
{
private:
    Ptr<CTexture>           m_pTex1;             //tex ( 气藕 + 采 )
    Ptr<CTexture>           m_pTex2;             //tex ( 采 )
    Ptr<CMaterial>          m_pMtrl;
    Ptr<CPrefab> m_bomb;
    Ptr<CPrefab> m_effect;

    CScene* m_pCurScene;

    FLOWER_STATE            m_eState;           //气藕采 惑怕
    bool                    m_IsOnCol;          //面倒吝?
    float                   m_fAtime;           //气藕 犁积己 矫埃
    bool m_bExp; //阂捞 搓栏搁 官肺 气惯

private:
    void CheckState();
    void Excute();

public:
    //void SetMakeBombState() { m_eState = FLOWER_STATE::MAKEBOMB; }
    FLOWER_STATE GetState() { return m_eState; }
public:
    virtual void awake();
    virtual void update();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);

public:
    CLONE(CBombFlowerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombFlowerScript();
    ~CBombFlowerScript();
};