#pragma once
#include "GUI.h"
#include "TreeCtrl.h"

class CRes;
class CGameObject;
class CMapScript;
class CPrefab;
class ResGUI :
    public GUI
{
private:
    TreeCtrl     m_Tree;
    bool         m_On;
    Ptr<CPrefab> m_PrefabObj;

    CMapScript* m_Map;
    POINT m_Res;


public:
    void Reset();
    virtual void init();
    virtual void update();
    virtual void render();

public:
    void SelectResource(const void* _SelChangedData);



public:
    ResGUI();
    ~ResGUI();
};
