#include "pch.h"
#include "EventGUI.h"
#include <Script\CObjEventScript.h>
#include <Engine\CGameObject.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
EventGUI::EventGUI() :
    m_EventScript(nullptr),
    m_iEventTypeIdx(0)
{
}

EventGUI::~EventGUI()
{
}


void EventGUI::update()
{
    if (m_EventScript == nullptr)
        return;
}

void EventGUI::render()
{
    bool bOpen = true;
    ImGui::Begin("Event", &bOpen);


    if (m_EventScript != nullptr)
    {

        static char str[64];
        static int  selected = 0;
        string strName = GetString(m_EventScript->GetGameObject()->GetName());
        ImGui::Text(strName.c_str());
        const char* items[] = { "TriggerOn", "TriggerOnOff"};

        EventType eType = m_EventScript->GetEventType();
        int item_current = int(eType);

        ImGui::Text("Event Type  "); ImGui::SameLine();
        ImGui::Combo("##Collider2D Type", &item_current, items, IM_ARRAYSIZE(items));


        ImGui::Text("Event Add   "); ImGui::SameLine();
        ImGui::InputTextWithHint("##EventName", "InputObjName", str, IM_ARRAYSIZE(str));
        ImGui::SameLine();
        if (ImGui::Button("ADD", { 50, 20 }))
        {
            string a = str;
            const wstring& b = wstring(a.begin(), a.end());
            CGameObject* Obj = CSceneMgr::GetInst()->GetCurScene()->FindObjectByName(b);
            if (Obj != nullptr)
            {
                if (Obj->GetScript(L"CObjEventScript") != nullptr)
                {
                    CObjEventScript* EventScript = (CObjEventScript*)Obj->GetScript(L"CObjEventScript");
                    m_EventScript->PushEvnetChild(EventScript);
                }
            }
        }
        ImGui::Text("Child List");
        ImGui::BeginChild("child", ImVec2(150, 0), true);
        vector<CObjEventScript*> vector = m_EventScript->GetChildeTrigger();
        if (vector.size() > 0)
        {
            for (size_t i = 0; i < vector.size(); i++)
            {

                wstring a = vector[i]->GetGameObject()->GetName();
                string b(a.begin(), a.end());
                if (ImGui::Selectable(b.c_str(), selected == (int)i))
                {
                    selected = i;
                }
            }
        }
        if (ImGui::Button("Release"))
        {
            if (vector.size() > 0)
                m_EventScript->ReleaseEvent(selected);
        }
        ImGui::EndChild();


        if (m_iEventTypeIdx != item_current)
        {
            m_iEventTypeIdx = item_current;
            m_EventScript->SetEventType((EventType)m_iEventTypeIdx);
            ImGui::SetWindowFocus(nullptr); // 모든 ImGui window focus 해제
        }


    }
    ImGui::GetWindowSize();

    ImGui::End();
}
