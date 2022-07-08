#include "pch.h"
#include "CSpeedUpScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine/CLayer.h>
#include <Engine\CCollider2D.h>
#include "CPlayerScript.h"
#include "CObjEventScript.h"

CSpeedUpScript::CSpeedUpScript()
    : CScript((int)SCRIPT_TYPE::SPEEDUPSCRIPT)
    , m_bIsSlide(false)
  
    , m_fRotValue(1.58)
    , m_Dir(0)
    , m_PreDir(0)
    , m_bOneTime(false)
    , m_bCol(false)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"speedup");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "0123", &m_Dir));
}

CSpeedUpScript::~CSpeedUpScript() {}

void CSpeedUpScript::awake() {}

void CSpeedUpScript::update()
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

    if (m_bCol == true && m_bOneTime == false)
    {
        if (!m_bOneTime)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_slide");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            pPS->SetPlayerState(PLAYER_STATE::SLIDE);

            if (m_Dir == 0)
                pPS->SetPlayerDir(DIR::DOWN); //왼쪽 발판일때 왼쪽으로 강제로 바꾸어줌
            else if (m_Dir == 1)
                pPS->SetPlayerDir(DIR::RIGHT);
            else if (m_Dir == 2)
                pPS->SetPlayerDir(DIR::UP);
            else if (m_Dir == 3)
                pPS->SetPlayerDir(DIR::LEFT);

            m_bIsSlide = true;
            m_bOneTime = true;
        }
    }

    m_PreDir = m_Dir;
}

void CSpeedUpScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* PlayerScript = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
        Vec3 Pos = Transform()->GetLocalPos();

        if (PlayerScript->GetPlayerState() == PLAYER_STATE::SLIDE) return;
        if (m_Dir == 0 || m_Dir == 2)
        {
            PlayerScript->Transform()->SetLocalPosX(Pos.x);
        }
        else if (m_Dir == 1 || m_Dir == 3)
        {
            PlayerScript->Transform()->SetLocalPosY(Pos.y);
        }
        m_bCol = true;
    }
}

void CSpeedUpScript::OnCollision(CGameObject* _pOther) {}

void CSpeedUpScript::OnCollisionExit(CGameObject* _pOther)
{
    m_bCol = false;
    m_bOneTime = false;
}

void CSpeedUpScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_Dir, sizeof(int), 1, _pFile);
    fwrite(&m_fRotValue, sizeof(float), 1, _pFile);
}

void CSpeedUpScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_Dir, sizeof(int), 1, _pFile);
    fread(&m_fRotValue, sizeof(float), 1, _pFile);
}