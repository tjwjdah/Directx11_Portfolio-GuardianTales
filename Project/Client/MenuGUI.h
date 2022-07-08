#pragma once
#include "GUI.h"

class MenuGUI :
    public GUI
{
public:
    virtual void update();
    virtual void render();

public:
    MenuGUI();
    ~MenuGUI();
};

