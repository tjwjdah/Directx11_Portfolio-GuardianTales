#include "pch.h"
#include "InspectorGUI.h"

#include <Engine\CGameObject.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CRes.h>

#include <Script\CScriptMgr.h>

#include "ComponentGUI.h"
#include "TransformGUI.h"
#include "MeshRenderGUI.h"
#include "Collider2DGUI.h"
#include "CameraGUI.h"
#include "ScriptGUI.h"

#include "ResInfoGUI.h"
#include "MaterialGUI.h"
#include "EventGUI.h"
#include "CImGUIMgr.h"
#include "Light2DGUI.h"
#include <Engine\CEventMgr.h>





InspectorGUI::InspectorGUI()
    : m_arrComGUI{}
    , m_arrResInfoGUI{}
    , m_pTargetObj(nullptr)
    , m_pTargetRes(nullptr)
    , m_ID(0)
    , m_LayerIndex(0)
{
}

InspectorGUI::~InspectorGUI()
{
    Safe_Delete_Array(m_arrComGUI);
    Safe_Delete_Array(m_arrResInfoGUI);
    Safe_Delete_Vector(m_vecScriptGUI);
}

void InspectorGUI::init()
{
    ComponentGUI* pNew = new TransformGUI;

    pNew->SetName(L"Transform");
    pNew->SetSize(Vec2(0.f, 100.f));
    m_arrComGUI[(UINT)COMPONENT_TYPE::TRANSFORM] = pNew;

    pNew = new MeshRenderGUI;

    pNew->SetName(L"MeshRender");
    pNew->SetSize(Vec2(0.f, 80.f));
    m_arrComGUI[(UINT)COMPONENT_TYPE::MESHRENDER] = pNew;

    pNew = new Collider2DGUI;

    pNew->SetName(L"Collider2D");
    pNew->SetSize(Vec2(0.f, 100.f));
    m_arrComGUI[(UINT)COMPONENT_TYPE::COLLIDER2D] = pNew;
    
    pNew = new CameraGUI;

    pNew->SetName(L"CameraGUI");
    pNew->SetSize(Vec2(0.f, 100.f));
    m_arrComGUI[(UINT)COMPONENT_TYPE::CAMERA] = pNew;

    pNew = new Light2DGUI;
    pNew->SetName(L"Light2DGUI");
    pNew->SetSize(Vec2(0.f, 100.f));
    m_arrComGUI[(UINT)COMPONENT_TYPE::LIGHT2D] = pNew;

    for (int i = 0; i < 10; ++i)
    {
        m_vecScriptGUI.push_back(new ScriptGUI);
    }

    ResInfoGUI* pResInfoGUI = new MaterialGUI;
    pResInfoGUI->SetName(L"Material");
    m_arrResInfoGUI[(UINT)RES_TYPE::MATERIAL] = pResInfoGUI;
}

void InspectorGUI::update()
{
    for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
    {
        if (nullptr == m_arrComGUI[i])
            continue;

        m_arrComGUI[i]->SetTargetObj(m_pTargetObj);
        m_arrComGUI[i]->update();
    }

    if (m_pTargetObj)
    {
        const vector<CScript*> vecScript = m_pTargetObj->GetScripts();
        for (size_t i = 0; i < vecScript.size(); ++i)
        {
            if (m_vecScriptGUI.size() <= i)
            {
                m_vecScriptGUI.push_back(new ScriptGUI);
            }

            m_vecScriptGUI[i]->SetTargetObj(m_pTargetObj);
            m_vecScriptGUI[i]->update();
        }
    }
    else
    {
        for (size_t i = 0; i < m_vecScriptGUI.size(); ++i)
        {
            m_vecScriptGUI[i]->SetTargetObj(nullptr);
            m_vecScriptGUI[i]->update();
        }
    }


    if (m_pTargetRes)
    {
        if (nullptr != m_arrResInfoGUI[(UINT)m_eResType])
        {
            m_arrResInfoGUI[(UINT)m_eResType]->SetTargetRes(m_pTargetRes);
            m_arrResInfoGUI[(UINT)m_eResType]->update();
        }
    }
}

void InspectorGUI::render()
{
    ImGui::Begin("Inspector");

    if (m_pTargetObj)
    {
        string strName = GetString(m_pTargetObj->GetName());
        ImGui::Text(strName.c_str());
        for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
        {
            if (nullptr == m_arrComGUI[i])
                continue;

            if (m_arrComGUI[i]->IsActive())
            {
                m_arrComGUI[i]->render();
                ImGui::Separator();
            }
        }

        // Object Script 에 대응하는 ScriptGUI render
        const vector<CScript*> vecScript = m_pTargetObj->GetScripts();
        if (vecScript.size() > 0)
        {
            ImGui::Text("Script");
            ImGui::NewLine();
        }
        for (size_t i = 0; i < vecScript.size(); ++i)
        {
            m_vecScriptGUI[i]->SetName(CScriptMgr::GetScriptName(vecScript[i]));
            m_vecScriptGUI[i]->SetScript(vecScript[i]);
            m_vecScriptGUI[i]->render();
        }

        if (ImGui::Button("Delete", { 50, 20 }))
        {
            tEvent even = {};
            even.eEvent = EVENT_TYPE::DELETE_OBJECT;
            even.lParam = (DWORD_PTR)m_pTargetObj;
            even.wParam = (DWORD_PTR)0;
            CEventMgr::GetInst()->AddEvent(even);
            m_pTargetObj = nullptr;
            EventGUI* Event = (EventGUI*)CImGUIMgr::GetInst()->FindGUI(L"Event");
            Event->SetEventScript(nullptr);
        }
    }
    else if (m_pTargetRes)
    {
        string strName = GetString(m_pTargetRes->GetKey().c_str());
        ImGui::Text(strName.c_str());
        ImGui::Text("Object Name "); ImGui::SameLine();
        string n = m_ObjectName;

        ImGui::InputText("##Obj_Name", (char*)n.c_str(), 100);

        int index = m_LayerIndex;

        ImGui::Text("Layer Index "); ImGui::SameLine();
        ImGui::InputInt("##Layer_Index", &index);
        if (index >= 0 && index < 32)
            m_LayerIndex = index;
        m_ObjectName = n;

        if (nullptr != m_arrResInfoGUI[(UINT)m_eResType])
        {
            m_arrResInfoGUI[(UINT)m_eResType]->render();
        }
    }

    ImGui::End();
}

void InspectorGUI::SetTargetResource(CRes* _pRes, RES_TYPE _eType)
{
    m_pTargetRes = _pRes;
    m_eResType = _eType;
    m_ObjectName = GetString(_pRes->GetKey().c_str()) + to_string(m_ID);
    if (nullptr != m_pTargetRes)
        m_pTargetObj = nullptr;
}
void InspectorGUI::ID_Plus()
{
    m_ID++;

    m_ObjectName = GetString(m_pTargetRes->GetKey().c_str()) + to_string(m_ID);
}