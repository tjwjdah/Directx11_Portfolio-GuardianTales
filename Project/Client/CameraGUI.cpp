#include "pch.h"
#include "CameraGUI.h"
#include <Engine\CGameObject.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CCamera.h>

#include <Engine\CKeyMgr.h>
CameraGUI::CameraGUI() :ComponentGUI(COMPONENT_TYPE::CAMERA)
{
}

CameraGUI::~CameraGUI()
{
}
void CameraGUI::init()
{
}

void CameraGUI::lateupdate()
{
    if (IsActive() && KEY_TAP(KEY_TYPE::ENTER))
    {
        ImGui::SetWindowFocus(nullptr); // 모든 ImGui window focus 해제
    }
}

void CameraGUI::render()
{
    CCamera* Camera = GetTargetObj()->Camera();

    float arrData[4] = {};
    float vData[4] = { Camera->GetfMaxUp(), Camera->GetfMaxDown(), Camera->GetfMaxLeft(),Camera->GetfMaxRight() };

    for (int i = 0; i < 4; ++i)
    {
            arrData[i] = vData[i];
    }

    Start();
    ImGui::Text("MaxUP     \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxUp", &arrData[0], 1.f,0.0f,"%.2f");
    ImGui::Text("MaxDown   \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxDown",&arrData[1], 1.f, 0.0f, "%.2f");
    ImGui::Text("MaxLeft   \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxLeft", &arrData[2], 1.f, 0.0f, "%.2f");
    ImGui::Text("MaxRight  \t");  ImGui::SameLine(); ImGui::InputFloat("##MaxRight", &arrData[3], 1.f, 0.0f, "%.2f");
    End();

    Camera->SetfMaxUp(arrData[0]);
    Camera->SetfMaxDown(arrData[1]);
    Camera->SetfMaxLeft(arrData[2]);
    Camera->SetfMaxRight(arrData[3]);
}


