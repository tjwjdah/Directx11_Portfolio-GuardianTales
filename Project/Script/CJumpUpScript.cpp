#include "pch.h"
#include "CJumpUpScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>
#include <Engine\CCollider2D.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"

CJumpUpScript::CJumpUpScript()
    : CScript((int)SCRIPT_TYPE::JUMPUPSCRIPT)
    , m_bIsPushed(false)
    , m_fAtime(0.f)
    , m_fRotValue(1.58)
    , m_Dir(1)
    , m_PreDir(0)
    , m_bFlag(false)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"jumpup");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"JumpUpMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "0123(dir)", &m_Dir));
}
CJumpUpScript::~CJumpUpScript() {}

void CJumpUpScript::awake() {}

void CJumpUpScript::update()
{
    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;
    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

    if (m_PreDir != m_Dir)
    {
        if (m_Dir == 1) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue));
        else if (m_Dir == 2) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 2));
        else if (m_Dir == 3) Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 3));
        else Transform()->SetLocalRot(Vec3(0.f, 0.f, m_fRotValue * 0));

    }
    if (m_bIsPushed == true)// && m_pPlayerScript != nullptr)
    {
        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_jumpup");
        pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

        m_fAtime += fDT;
        if (m_fAtime < 1.f)
        {
            pPS->SetPlayerState(PLAYER_STATE::JUMP);

            if (m_Dir == 0)
                pPS->SetPlayerDir(DIR::DOWN); //왼쪽 발판일때 플레이어의 왼쪽으로 강제로 바꾸어줌
            else if (m_Dir == 1)
                pPS->SetPlayerDir(DIR::RIGHT);
            else if (m_Dir == 2)
                pPS->SetPlayerDir(DIR::UP);
            else if (m_Dir == 3)
                pPS->SetPlayerDir(DIR::LEFT);
        }
        else // 시간이 지나면 발판상태 초기화
        {
            m_bIsPushed = false;
            m_fAtime = 0.f;
            pPS = nullptr;
        }
    }
    m_PreDir = m_Dir;
}

void CJumpUpScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* PlayerScript = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        PlayerScript->SetPlayerJumpSpeed(Vec2(550.f, 500.f));
        m_bIsPushed = true;
    }
}

void CJumpUpScript::OnCollision(CGameObject* _pOther) {}

void CJumpUpScript::OnCollisionExit(CGameObject* _pOther)
{
    m_bIsPushed = false;
}

void CJumpUpScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_Dir, sizeof(int), 1, _pFile);
    fwrite(&m_fRotValue, sizeof(float), 1, _pFile);
}

void CJumpUpScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_Dir, sizeof(int), 1, _pFile);
    fread(&m_fRotValue, sizeof(float), 1, _pFile);
}