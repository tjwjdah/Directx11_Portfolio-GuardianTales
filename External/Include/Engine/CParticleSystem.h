#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;


class CParticleSystem :
    public CComponent
{
private:
    CStructuredBuffer*          m_pParticleBuffer;

    Ptr<CMesh>                  m_pMesh;
    Ptr<CMaterial>              m_pMtrl;
    Ptr<CParticleUpdateShader>  m_pUpdateShader;

    int                         m_iMaxCount;    // 파티클 최대 수용량
    int                         m_iAliveCount;  // 이번에 활성화 시킬 파티클 개수
    float                       m_fMinLifeTime;
    float                       m_fMaxLifeTime;
    float                       m_fMinSpeed;
    float                       m_fMaxSpeed;
    float                       m_fFrequency;   // 파티클 생성 주기
    float                       m_fAccTime;     // 누적시간

    Vec4                        m_vCreateRange; // 파티클 생성 범위

    Vec4                        m_vStartColor;
    Vec4                        m_vEndColor;
    Vec3                        m_vStartScale;
    Vec3                        m_vEndScale;


public:
    virtual void update() {}
    virtual void finalupdate();
    void render();

public:
    void SetMaxParticleCount(int _iMaxCount);



public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
    CLONE(CParticleSystem);

public:
    CParticleSystem();
    ~CParticleSystem();
};

