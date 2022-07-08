#include "pch.h"
#include "CHPHarScript.h"
#include "CObjState.h"
#include <Engine\CMeshRender.h>
#include <Engine\CEventMgr.h>





CHPHarScript::CHPHarScript() :CScript((int)SCRIPT_TYPE::HPHARSCRIPT)
, m_ParentsState(nullptr)
, m_Hpratio(0.f)
, m_Coolratio(0.f)
, m_HpBarRed(nullptr)
, m_HpBarGreen(nullptr)
, m_HpBarSkyblue(nullptr)
, m_Player(true)
, m_awake2(false)
{

}

CHPHarScript::~CHPHarScript()
{
}


void CHPHarScript::awake()
{
	if (!m_awake2)
	{
		m_awake2 = true;
	}
	else
		return;
	if (GetGameObject()->GetParent() != nullptr)
	{
		m_ParentsState = (CObjState*)GetGameObject()->GetParent()->GetScript(L"CObjState");
	}
	if (m_Player)
	{
		m_HpBarRed = CResMgr::GetInst()->FindRes<CPrefab>(L"HPBar_Red").Get()->Instantiate();
		m_HpBarGreen= CResMgr::GetInst()->FindRes<CPrefab>(L"HPBar_Green").Get()->Instantiate();
		m_HpBarSkyblue= CResMgr::GetInst()->FindRes<CPrefab>(L"HPBar_Skyblue").Get()->Instantiate();
	

		m_HpBarRed->Transform()->SetLocalPos(Vec3(0.f, -0.29f, -1.f));
		m_HpBarRed->Transform()->SetLocalScale(Vec3(1.f, 0.19f, 1.f));

		m_HpBarGreen->Transform()->SetLocalPos(Vec3(0.f, 0.16f, -1.f));
		m_HpBarGreen->Transform()->SetLocalScale(Vec3(1.f, 0.38f, 1.f));

		m_HpBarSkyblue->Transform()->SetLocalPos(Vec3(0.f, -0.29f, 1.f));
		m_HpBarSkyblue->Transform()->SetLocalScale(Vec3(1.f, 0.19f, 1.f));

		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)m_HpBarRed;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)11;
		CEventMgr::GetInst()->AddEvent(even);
		even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)m_HpBarGreen;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)11;
		CEventMgr::GetInst()->AddEvent(even);
		even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)m_HpBarSkyblue;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)11;
		CEventMgr::GetInst()->AddEvent(even);

		CScript::AddChild(GetGameObject(), m_HpBarRed);
		CScript::AddChild(GetGameObject(), m_HpBarGreen);
		CScript::AddChild(GetGameObject(), m_HpBarSkyblue);
	}
	else
	{
		Transform()->SetLocalScaleY(0.05f);
		Transform()->SetLocalPosY(-0.15f);
		m_HpBarRed = CResMgr::GetInst()->FindRes<CPrefab>(L"HPBar_Red").Get()->Instantiate();

		m_HpBarRed->Transform()->SetLocalPos(Vec3(0.f, 0.16f, -1.f));
		m_HpBarRed->Transform()->SetLocalScale(Vec3(1.f, 0.38f, 1.f));

		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)m_HpBarRed;
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)11;
		CEventMgr::GetInst()->AddEvent(even);

		CScript::AddChild(GetGameObject(), m_HpBarRed);
	}
}

void CHPHarScript::update()
{
	if (m_ParentsState == nullptr)
		return;
	m_Hpratio = (float)m_ParentsState->GetHp() / (float)m_ParentsState->GetMaxHp();
	if (m_Player)
	{

		m_Coolratio = (float)m_ParentsState->GetCoolTime() / (float)m_ParentsState->GetCoolTimeMax();
		m_HpBarGreen->Transform()->SetLocalScaleX(m_Hpratio);
		m_HpBarGreen->Transform()->SetLocalPosX(-((1.f-m_Hpratio) / 2));
		if (m_Coolratio < 1.f)
		{
			m_HpBarRed->Transform()->SetLocalPosZ(-1.f);
			m_HpBarRed->Transform()->SetLocalScaleX(m_Coolratio);
			m_HpBarRed->Transform()->SetLocalPosX(-((1.f - m_Coolratio) / 2)+0.03);
			m_HpBarSkyblue->Transform()->SetLocalPosZ(1.f);
			m_HpBarSkyblue->Transform()->SetLocalScaleX(0.f);
		}
		else {
			m_HpBarRed->Transform()->SetLocalPosZ(1.f);
			m_HpBarSkyblue->Transform()->SetLocalPosZ(-1.f);
			m_HpBarSkyblue->Transform()->SetLocalScaleX(1.f);
		}
		
	}
	else
	{
		m_HpBarRed->Transform()->SetLocalScaleX(m_Hpratio);
		m_HpBarRed->Transform()->SetLocalPosX(-((1.f - m_Hpratio) / 2));



		if (m_Hpratio <= 0.f)
		{
			Transform()->SetLocalScale(Vec3(0.f, 0.f, 0.f));
		}
	}
	//


}

void CHPHarScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
	fwrite(&m_Player, sizeof(bool), 1, _pFile);
}
void CHPHarScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
	fread(&m_Player, sizeof(bool), 1, _pFile);
}