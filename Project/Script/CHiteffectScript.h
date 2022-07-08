#pragma once
#include <Engine\CScript.h>
class CHiteffectScript :
    public CScript
{

public:
    virtual void update();
    virtual void awake();


public:
    CLONE(CHiteffectScript);

public:
    CHiteffectScript();
    ~CHiteffectScript();
};

