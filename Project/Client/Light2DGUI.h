#pragma once
#include "ComponentGUI.h"
class Light2DGUI :
    public ComponentGUI
{
private:
    int     m_iColliderTypeIdx;

public:
    virtual void lateupdate();
    virtual void render();

    Light2DGUI();
    ~Light2DGUI();
};

