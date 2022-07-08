#include "pch.h"
#include "CSoundScript.h"

#include <Engine/CCore.h>
#include <Engine/CScene.h>
#include <Engine/CSceneMgr.h>
#include <Engine\CResMgr.h>
#include <Engine/CSound.h>
#include "CObjEventScriptMgr.h"

CSoundScript::CSoundScript()
    : CScript((UINT)SCRIPT_TYPE::SOUNDSCRIPT)
    , m_eName(BGM_NAME::NONE)
    , m_pSound(nullptr)
    , m_bplay(false)
{
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "BgmNum", &m_eName));
}

CSoundScript::~CSoundScript()
{
    if (m_pSound.Get() != nullptr)
    {
        m_pSound->Stop();
        m_bplay = false;
    }
}

void CSoundScript::awake()
{
}

void CSoundScript::update()
{
    if (m_eName == BGM_NAME::NONE && m_pSound == nullptr) return;

    if (m_eName == BGM_NAME::NONE && !(m_pSound == nullptr))
    {
        m_pSound->Stop();
        m_bplay = false;
        return;
    }

    if (m_isave != (UINT)m_eName && !(m_pSound == nullptr))
    {
        m_pSound->Stop();
        m_bplay = false;
    }

    if (m_pSound == nullptr || m_bplay == false)
    {
        switch (m_eName)
        {
        case BGM_NAME::BOSSMAIN:
        {
            m_pSound = CResMgr::GetInst()->FindRes<CSound>(L"bgm_bossmain");
            m_pSound->Play(0); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            m_bplay = true;
            m_isave = 0;
            break;
        }
        case BGM_NAME::CHANGECHAR:
        {
            m_pSound = CResMgr::GetInst()->FindRes<CSound>(L"bgm_changechar");
            m_pSound->Play(0);
            m_bplay = true;
            m_isave = 1;
            break;
        }
        case BGM_NAME::DUNGEON:
        {
            m_pSound = CResMgr::GetInst()->FindRes<CSound>(L"bgm_dungeon");
            m_pSound->Play(0);
            m_bplay = true;
            m_isave = 2;
            break;
        }
        case BGM_NAME::BOSS:
        {
            m_pSound = CResMgr::GetInst()->FindRes<CSound>(L"bgm_bossintro");
            m_pSound->Play(0);
            m_bplay = true;
            m_isave = 3;
            break;
        }
        case BGM_NAME::START:
        {
            m_pSound = CResMgr::GetInst()->FindRes<CSound>(L"bgm_title_main");
            m_pSound->Play(0); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
            m_bplay = true;
            m_isave = 4;
            break;
        }
        default:
            break;
        }
    }

}

void CSoundScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_eName, sizeof(BGM_NAME), 1, _pFile);
    
}

void CSoundScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_eName, sizeof(BGM_NAME), 1, _pFile);
}