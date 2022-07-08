#pragma once
#include <Engine\CScript.h>
class CRadianDIRScript :
    public CScript
{
   
private:
   float   m_fSpeed;
   float   m_fRadian; //°¢µµ
   
   DIR     m_DIR;
   float   m_angle;
public:
    virtual void update();
    virtual void awake();
public:
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    void SetRadian(float _Radian) { m_fRadian = _Radian; };
    void SetDir(DIR _Dir) { m_DIR = _Dir; }
public:
    CLONE(CRadianDIRScript);

public:
    CRadianDIRScript();
    ~CRadianDIRScript();

};

