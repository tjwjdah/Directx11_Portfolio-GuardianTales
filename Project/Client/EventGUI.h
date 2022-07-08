#pragma once
#include "GUI.h"

class CObjEventScript;
class EventGUI :
    public GUI
{
    CObjEventScript* m_EventScript;

    int              m_iEventTypeIdx;
public:
    virtual void update();
    virtual void render();

public:
    void SetEventScript(CObjEventScript* _Event) { m_EventScript = _Event; }
public:
    EventGUI();
    ~EventGUI();
};

