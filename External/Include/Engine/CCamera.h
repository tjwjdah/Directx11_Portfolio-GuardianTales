#pragma once
#include "CComponent.h"

class CCamera :
    public CComponent
{
private:
    PROJ_TYPE       m_eProjType;    
    Vec2            m_vScale;   // 직교투영 범위 배율

    Matrix          m_matView;
    Matrix          m_matProj;

    float           m_fFOV;

    UINT            m_iLayerCheck;

    float           m_HitTime;
    bool            m_HitOn;
    Vec3            m_HitPrePos;


    float           m_MonDieTime;
    bool            m_MonDie;
    Vec2            m_MonPos;

    vector<CGameObject*>    m_vecForward;
    vector<CGameObject*>    m_vecParticle;
    vector<CGameObject*>    m_vecPostEffect;
    
    float           m_fMaxUp;
    float           m_fMaxDown;
    float           m_fMaxLeft;
    float           m_fMaxRight;
public:
    virtual void update();
    virtual void finalupdate();

public:
    void SetProjType(PROJ_TYPE _eType) { m_eProjType = _eType; }
    void SetScale(Vec2 _vScale) {m_vScale = _vScale;}
    void SetLayerCheck(UINT _iLayerIdx, bool _bAdd);
    void SetLayerAllCheck() { m_iLayerCheck = 0xffffffff; }

    void MonsterDie(Vec2 _Pos);

    GET_SET(float, fMaxUp);
    GET_SET(float, fMaxDown);
    GET_SET(float, fMaxLeft);
    GET_SET(float, fMaxRight);
    void Hit() { m_HitOn = true; }
   // void HitCameraMove();
public:
    void SortObject();
    void render_forward();
    void render_posteffect();

public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
    CLONE(CCamera);

public:
    CCamera();
    ~CCamera();
};

