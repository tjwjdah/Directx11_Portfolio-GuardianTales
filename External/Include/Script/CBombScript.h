#pragma once
#include <Engine\CScript.h>

// obj name : 폭탄
// desc : 장애물 폭파

enum class BOMB_STATE
{
    ONHEAD,     //머리위
    //THROW,      //던짐
    SLIDE,      //미끄러짐
    EXPLODE_READY,
    EXPLODE,    //터짐
    NONE
};


class CPlayerScript;

class CBombScript :
    public CScript
{
private:

    //
    vector<CScript*> m_pTarScript;
    Ptr<CPrefab> m_effect;
    //CPlayerScript*          m_pPlayerScript;
    bool m_IsCol;
    BOMB_STATE              m_eState;
    DIR                     m_eDir;         //플레이어 방향 저장
    Vec3                    m_vPos;         //처음 위치 저장
    Vec3                    m_vStartPos;
    Vec2                    m_vSpeed; //좌 , 우 speed
    float                   m_fSpeed; //상,  하 speed
    float                   m_fAtime;
    float                   m_fAngle;
    float                   m_fPower;
    float                   m_fAdjSpeed;


    float               m_bombcolortime;
    float               m_bombcolortime2;
    bool                m_bombcolor;
private:
    void CheckState();
    void Move();

public:
    virtual void awake();
    virtual void update();


public:

    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionOn(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);


public:
    CLONE(CBombScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CBombScript();
    ~CBombScript();
};