#pragma once
#include <Engine\CScript.h>


class CTouchScript :
    public CScript
{

private:
    float m_Time;
    bool  m_Show;
public:
    CLONE(CTouchScript);

public:
    virtual void update();

public:
    CTouchScript();
    ~CTouchScript();
};

