#pragma once
#include "ComponentGUI.h"

class ListGUI;

class MeshRenderGUI :
    public ComponentGUI
{
public:    
    virtual void update();
    virtual void render();

private:
    GUI* PopupListGUI();
    void SelectListItem(ListGUI* _pListGUI, const char* _pSelectName);



public:
    MeshRenderGUI();
    ~MeshRenderGUI();
};

