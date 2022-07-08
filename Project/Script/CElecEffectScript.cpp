#include "pch.h"
#include "CElecEffectScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CCollider2D.h>

#include "CObjEventScript.h"


CElecEffectScript::CElecEffectScript()
    : CScript((int)SCRIPT_TYPE::ELECEFFECTSCRIPT)
    , m_IsCol(false)
{}

CElecEffectScript::~CElecEffectScript() {}

void CElecEffectScript::awake() {}

void CElecEffectScript::update() {

    if (m_IsCol)
    {
        Collider2D()->SetvOffsetScale(Vec2(0.f, 0.0f));

    }
    else
    {
        Collider2D()->SetvOffsetScale(Vec2(1.f, 0.5f));
    }

}

void CElecEffectScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CPushSmallStoneScript"))
    {
        m_IsCol = true;
    }

}

void CElecEffectScript::OnCollisionOn(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CPushSmallStoneScript"))
    {
        m_IsCol = true;
    }
}

void CElecEffectScript::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CPushStoneScript") || _pOther->GetScript(L"CPushSmallStoneScript"))
    {
        m_IsCol = false;
    }
}

void CElecEffectScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CElecEffectScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}