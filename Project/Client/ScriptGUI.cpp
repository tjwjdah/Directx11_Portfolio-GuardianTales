#include "pch.h"
#include "ScriptGUI.h"

#include <Engine\CScript.h>

#include "DataGUI.h"

ScriptGUI::ScriptGUI()
	: ComponentGUI(COMPONENT_TYPE::SCRIPT)
	, m_pTargetScript(nullptr)
{
}

ScriptGUI::~ScriptGUI()
{
}

void ScriptGUI::update()
{
	ComponentGUI::update();
}

void ScriptGUI::render()
{
	assert(m_pTargetScript);

	Start();

	const vector<tDataDesc>& vecDataDesc = m_pTargetScript->GetDataDesc();
	for (size_t i = 0; i < vecDataDesc.size(); ++i)
	{
		switch (vecDataDesc[i].eType)
		{
		case SCRIPT_DATA_TYPE::INT:
			DataGUI::render_int(vecDataDesc[i].strName.c_str(), vecDataDesc[i].pData);
			break;
		case SCRIPT_DATA_TYPE::FLOAT:
			DataGUI::render_float(vecDataDesc[i].strName.c_str(), vecDataDesc[i].pData);
			break;
		case SCRIPT_DATA_TYPE::VEC2:
			DataGUI::render_Vec2(vecDataDesc[i].strName.c_str(), vecDataDesc[i].pData);
			break;
		case SCRIPT_DATA_TYPE::VEC4:
			DataGUI::render_Vec4(vecDataDesc[i].strName.c_str(), vecDataDesc[i].pData);
			break;
		case SCRIPT_DATA_TYPE::PREFAB:
			DataGUI::render_Prefab(vecDataDesc[i].strName.c_str(), vecDataDesc[i].pData);
			break;	
		}
	}



	End();

	ImVec2 vSize = ImGui::GetItemRectMin();
	SetSize(Vec2(0.f, vSize.y));
}

void ScriptGUI::Start()
{
	string strName = GetString(GetName());

	//ImGui::BeginChild(strName.c_str());
	//float fOrigin = ImGui::GetFontSize();

	ImGui::Text(strName.c_str());
	
}

void ScriptGUI::End()
{
	//ImGui::EndChild();
}
