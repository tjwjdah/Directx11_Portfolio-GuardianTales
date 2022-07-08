#include "pch.h"
#include "CElecTowerScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CElecTowerScript::CElecTowerScript()
	: CScript((int)SCRIPT_TYPE::ELECTOWERSCRIPT)
	, m_bIsCol(false)
	//, m_pPlayerScript(nullptr)
{
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"electower");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ElecTowerMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CElecTowerScript::~CElecTowerScript() {}

void CElecTowerScript::awake()
{
}

void CElecTowerScript::update()
{


}

void CElecTowerScript::OnCollisionEnter(CGameObject* _pOther)
{
	m_bIsCol = true;

}

void CElecTowerScript::OnCollisionExit(CGameObject* _pOther)
{
	m_bIsCol = false;
}

void CElecTowerScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
}

void CElecTowerScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
}