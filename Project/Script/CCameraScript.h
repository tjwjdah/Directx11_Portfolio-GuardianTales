#pragma once
#include <Engine\CScript.h>

class CCameraScript :
    public CScript
{

public:
    virtual void update();

public:
    CLONE(CCameraScript);

public:
    CCameraScript();
    ~CCameraScript();
};

