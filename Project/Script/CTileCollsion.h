#pragma once
#include <Engine\CScript.h>
class CTileCollsion :
    public CScript
{
private:
    bool    m_CollsionOn;

public:
    virtual void awake();
    virtual void update();


public:
    CLONE(CTileCollsion);
  


public:
    CTileCollsion();
    ~CTileCollsion();
};

