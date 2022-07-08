#include "pch.h"
#include "Light2DGUI.h"
#include <Engine\CGameObject.h>
#include <Engine\CSceneMgr.h>


#include <Engine\CKeyMgr.h>
#include <Engine\CLight2D.h>
Light2DGUI::Light2DGUI():
	ComponentGUI(COMPONENT_TYPE::LIGHT2D)
{
}

Light2DGUI::~Light2DGUI()
{
}

void Light2DGUI::lateupdate()
{
    if (IsActive() && KEY_TAP(KEY_TYPE::ENTER))
    {
        ImGui::SetWindowFocus(nullptr); // 모든 ImGui window focus 해제
    }

}

void Light2DGUI::render()
{

    CLight2D* Light2D = GetTargetObj()->Light2D();

    float arrData[3] = {};
    float vData[3] = { Light2D->GetAmbient().x, Light2D->GetAmbient().y, Light2D->GetAmbient().z };

    for (int i = 0; i < 4; ++i)
    {
        arrData[i] = vData[i];
    }

    Start();
    ImGui::Text("MaxUP     \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxUp", &arrData[0], 1.f, 0.0f, "%.2f");
    ImGui::Text("MaxDown   \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxDown", &arrData[1], 1.f, 0.0f, "%.2f");
    ImGui::Text("MaxLeft   \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxLeft", &arrData[2], 1.f, 0.0f, "%.2f");

    End();

    Light2D->SetAmbient(Vec3(arrData[0], arrData[1], arrData[2]));
 
}

