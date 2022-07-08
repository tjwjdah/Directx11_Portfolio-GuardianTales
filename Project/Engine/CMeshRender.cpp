#include "pch.h"
#include "CMeshRender.h"

#include "CResMgr.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CAnimator2D.h"


CMeshRender::CMeshRender()
	:CComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::update()
{
}

void CMeshRender::finalupdate()
{
}

void CMeshRender::render()
{
	Transform()->UpdateData();
		
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	m_pMtrl->UpdateData();

	m_pMesh->UpdateData();
	m_pMesh->render();

	m_pMtrl->Clear();

	if (Animator2D())
	{
		CAnimator2D::Clear();
	}
}

Ptr<CMaterial> CMeshRender::GetCloneMaterial()
{
	if (nullptr == m_pSharedMtrl)
	{
		m_pSharedMtrl = m_pMtrl;
	}
	
	m_pMtrl = m_pMtrl->Clone();

	return m_pMtrl;
}

void CMeshRender::SaveToScene(FILE* _pFile)
{
	CComponent::SaveToScene(_pFile);		
	
	SaveResRefInfo(m_pMesh, _pFile);
	SaveResRefInfo(m_pMtrl, _pFile);
}

void CMeshRender::LoadFromScene(FILE* _pFile)
{
	CComponent::LoadFromScene(_pFile);
		
	LoadResRefInfo(m_pMesh, _pFile);
	LoadResRefInfo(m_pMtrl, _pFile);
}