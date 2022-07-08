#pragma once
#include <Engine\CScript.h>

class CMissileScript :
    public CScript
{
private:
    float   m_fTime; 
    float   m_fMaxTime; //지속시간
public:
    virtual void update();
    
public:
    void SetTime(float _Time) {
        m_fMaxTime = _Time;
    }

public:
    CLONE(CMissileScript);

public:
    CMissileScript();
    ~CMissileScript();
};

