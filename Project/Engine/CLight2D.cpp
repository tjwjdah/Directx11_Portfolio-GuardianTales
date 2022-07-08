#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"
#include "CTimeMgr.h"
CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
	, m_info{}
	, m_SkillOn(false)
	, m_Time(0.f)
	, m_MaxTime(1.f)
{
}

CLight2D::~CLight2D()
{
}

void CLight2D::finalupdate()
{
	m_info.vWorldPos = Transform()->GetWorldPos();
	m_info.vDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	if (m_SkillOn)
	{
		m_Time += fDT;
		
		if (m_Time > m_MaxTime)
		{
			m_Time = 0.f;
			m_SkillOn = false;
			m_info.color.vAmb = Vec3(1.0f, 1.0f, 1.0f);
		}
	}

	CRenderMgr::GetInst()->RegisterLight2D(this);
}

void CLight2D::SetSkill(float _MaxTime)
{
	m_MaxTime = _MaxTime;
	m_SkillOn = true;
	m_info.color.vAmb = Vec3(0.5f, 0.5f, 0.5f);

}

void CLight2D::SaveToScene(FILE* _pFile)
{
	CComponent::SaveToScene(_pFile);

	fwrite(&m_info, sizeof(tLight2DInfo), 1, _pFile);
}

void CLight2D::LoadFromScene(FILE* _pFile)
{
	CComponent::LoadFromScene(_pFile);

	fread(&m_info, sizeof(tLight2DInfo), 1, _pFile);
}