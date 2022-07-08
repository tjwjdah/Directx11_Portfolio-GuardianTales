#pragma once
#include <Engine\CScript.h>

class CDropMissileScript :
    public CScript
{
private:
    Vec3 m_startpos;
    float m_startposy;

    float   m_speed;
    float   m_atime;
    float   m_maxtime;
    float m_offsety;

    bool m_start;
public:
    virtual void update();
    virtual void awake();

public:
    void SetStartPos(Vec3 _pos) { m_startpos = _pos; }
    void SetSpeed(float _Speed) { m_speed = _Speed; }
    void SetTime(float _time) { m_maxtime = _time; }
    void Setoffsety(float _y) { m_offsety = _y; }

public:
    CLONE(CDropMissileScript);

public:
    CDropMissileScript();
    ~CDropMissileScript();

};

