#pragma once
#include <Engine\CScript.h>

class CSpinBulletScript :
    public CScript
{
private:
    Vec2 m_speed;
    float m_atime;
    float m_maxtime;
    float m_power;

public:
    virtual void update();
    virtual void awake();

public:
    void SetSpeed(Vec2 _s) { m_speed = _s; }
    void SetTime(float _t) { m_maxtime = _t; }
    void SetPower(float _p) { m_power = _p; }
public:
    CLONE(CSpinBulletScript);

public:
    CSpinBulletScript();
    ~CSpinBulletScript();

};

