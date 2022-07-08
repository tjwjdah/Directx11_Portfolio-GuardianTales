#pragma once
#include "GUI.h"
#include <Engine\CTexture.h>

class CMapScript;
class CPrefab;
class CGameObject;
class MaptoolGUI :
    public GUI
{
private:
    Ptr<CTexture> m_TileTex;
    Ptr<CPrefab>  p_Collsion;

    vector<CGameObject*> m_CollVector;

    CMapScript* m_Map;
    int         m_x;
    int        m_y;
    int        m_size;
    Vec2        m_SetIndex;
    bool        m_Collsion;
    POINT m_Res;


public:
    virtual void init();
    virtual void update();
    virtual void render();

public:
    void SetMap(CMapScript* _Map) { m_Map = _Map; }

public:
    MaptoolGUI();
    ~MaptoolGUI();

};