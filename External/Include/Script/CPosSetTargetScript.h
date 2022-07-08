#pragma once
#include <Engine\CScript.h>
class CPosSetTargetScript :
    public CScript
{
private:
    float   m_fSpeed;
    Vec3    m_TargetPos; //°¢µµ
    Vec3    m_Dir;
public:
    virtual void update();
    virtual void awake();
public:
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    void SetTargetPos(Vec3 _Pos) { m_TargetPos = _Pos; };

public:
    CLONE(CPosSetTargetScript);

public:
    CPosSetTargetScript();
    ~CPosSetTargetScript();
};

