#include "pch.h"
#include "MenuGUI.h"

MenuGUI::MenuGUI()
{
}

MenuGUI::~MenuGUI()
{
}


void MenuGUI::update()
{
}

void MenuGUI::render()
{
    if (ImGui::BeginMainMenuBar())
    {       
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("Save Scene");
            ImGui::MenuItem("Load Scene");

            ImGui::Separator();

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("GameObject"))
        {
            ImGui::MenuItem("Create Empty Object");

            if (ImGui::BeginMenu("Add Component"))
            {
                if (ImGui::MenuItem("MeshRender"))
                {

                }

                if (ImGui::MenuItem("Collider2D"))
                {

                }

                if (ImGui::MenuItem("Light2D"))
                {

                }

                if (ImGui::MenuItem("Camera"))
                {

                }

                if (ImGui::MenuItem("ParticleSystem"))
                {

                }

                ImGui::EndMenu();
            }            

            ImGui::Separator();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}
