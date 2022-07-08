#include "pch.h"
#include "CRedButtonScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>

#include "CObjEventScript.h"

CRedButtonScript::CRedButtonScript()
    : CScript((int)SCRIPT_TYPE::REDBUTTONSCRIPT)
    , m_pEventScript(nullptr)

{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"redbutton");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}


CRedButtonScript::~CRedButtonScript()
{
}

void CRedButtonScript::awake()
{
    m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));

}

void CRedButtonScript::update()
{

}

void CRedButtonScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTargetSearchScript"))
    {
        return;
    }
    if (m_pEventScript != nullptr)
    {
        m_pEventScript->SetTrigger(true);
    }
}

void CRedButtonScript::OnCollision(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CTargetSearchScript"))
    {
        return;
    }
    if (m_pEventScript != nullptr)
    {
        m_pEventScript->SetTrigger(true);
    }
}

void CRedButtonScript::OnCollisionExit(CGameObject* _pOther)
{
    if (m_pEventScript != nullptr)
    {
        m_pEventScript->SetTrigger(false);
    }
}

void CRedButtonScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CRedButtonScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}
