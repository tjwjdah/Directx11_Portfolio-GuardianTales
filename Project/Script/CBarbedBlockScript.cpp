#include "pch.h"
#include "CBarbedBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"

CBarbedBlockScript::CBarbedBlockScript()
    : CScript((int)SCRIPT_TYPE::BARBEDBLOCKSCRIPT)
    , m_fDir(1.f)
    , m_fSpeed(300.f)
    , m_fRange(100.f)
    , m_vStartPos(0, 0)
    , m_bCol(false)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"barbedblock");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "speed", &m_fSpeed));
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "Dir", &m_fDir));
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "Range", &m_fRange));
}

CBarbedBlockScript::~CBarbedBlockScript() {}

void CBarbedBlockScript::awake() {}

void CBarbedBlockScript::update()
{

    Vec3 _vPos = Transform()->GetLocalPos();

    _vPos.y += m_fDir * m_fSpeed * DT;

    if (abs(_vPos.y - m_vStartPos.y) > m_fRange)
    {
        if (1.f == m_fDir)
        {
            _vPos.y = m_vStartPos.y + m_fRange;
        }
        else
        {
            _vPos.y = m_vStartPos.y - m_fRange;
        }

        m_fDir *= -1.f;
    }

    Transform()->SetLocalPos(_vPos);
}

void CBarbedBlockScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bCol = true;

        CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        Player->SetPlayerState(PLAYER_STATE::CRASH);
        Player->SetHit(true);

        // m_pPlayer = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
    }
}

void CBarbedBlockScript::OnCollisionExit(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bCol = false;
    }
}

void CBarbedBlockScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_fDir, sizeof(float), 1, _pFile);
    fwrite(&m_fSpeed, sizeof(float), 1, _pFile);
    fwrite(&m_fRange, sizeof(float), 1, _pFile);
    fwrite(&m_vStartPos, sizeof(Vec2), 1, _pFile);
}

void CBarbedBlockScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_fDir, sizeof(float), 1, _pFile);
    fread(&m_fSpeed, sizeof(float), 1, _pFile);
    fread(&m_fRange, sizeof(float), 1, _pFile);
    fread(&m_vStartPos, sizeof(Vec2), 1, _pFile);
}