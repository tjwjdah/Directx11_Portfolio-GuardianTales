#pragma once
#include <Engine\CScript.h>
class CObjTileCol :
    public CScript
{

public:
    virtual void awake();
    virtual void update();


public:
    CLONE(CObjTileCol);



public:
    CObjTileCol();
    ~CObjTileCol();
};
