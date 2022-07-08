#pragma once
#include "GUI.h"

class ComponentGUI;
class ResInfoGUI;
class CGameObject;
class ScriptGUI;
class CRes;

class InspectorGUI :
    public GUI
{
private:
    ComponentGUI* m_arrComGUI[(UINT)COMPONENT_TYPE::END];
    vector<ScriptGUI*> m_vecScriptGUI;

    ResInfoGUI* m_arrResInfoGUI[(UINT)RES_TYPE::END];

    CGameObject* m_pTargetObj;

    CRes* m_pTargetRes;
    RES_TYPE        m_eResType;
    unsigned int    m_ID;
    int             m_LayerIndex;
    string          m_ObjectName;
public:
    virtual void init();
    virtual void update();
    virtual void render();

public:
    void SetTargetObject(CGameObject* _pObj)
    {
        m_pTargetObj = _pObj;
        if (nullptr != m_pTargetObj)
            m_pTargetRes = nullptr;
    }

    void SetTargetResource(CRes* _pRes, RES_TYPE _eType);

    string GetObjectName() { return m_ObjectName; }

    CGameObject* GetTargetObj() { return m_pTargetObj; }
    CRes* GetResObj() { return m_pTargetRes; }
    int   GetLayerIndex() { return m_LayerIndex; }
    void ID_Plus();
public:
    InspectorGUI();
    ~InspectorGUI();
};
