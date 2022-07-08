#include "pch.h"
#include "CFireWoodScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include "CPlayerScript.h"

#include "CObjEventScript.h"

CFireWoodScript::CFireWoodScript()
    : CScript((int)SCRIPT_TYPE::FIREWOODSCRIPT)
    , m_pEventScript(nullptr)
    , m_bPlayAni(false)
    , m_bIsOnFire(false)
    , m_fOnTime(0.f)
    , m_fSetTime(0.f)
    , m_test(0.f)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firewood");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

    //test
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::FLOAT, "time", &m_fSetTime));
}

CFireWoodScript::~CFireWoodScript()
{
}

void CFireWoodScript::awake()
{

    m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
    m_Child = GetGameObject()->GetChild(L"FireWoodChild");

}

void CFireWoodScript::update()
{

    if (m_pEventScript->GetTrigger())
    {
        m_bIsOnFire = true;
        if (!m_bPlayAni)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_fire");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            m_Child->Animator2D()->PlayAnimation(L"BURN", true);
            m_bPlayAni = true;
        }
    }

    if (m_bIsOnFire == true && m_fSetTime != 0.f) //설정한 시간이 있으면 (기본값은 0)
    {
        m_fOnTime += fDT;
        m_test = m_fSetTime - m_fOnTime; //test

        if (m_fSetTime < m_fOnTime) //켜져있는 시간이 설정한 시간을 초과하면
        {
            //불이 꺼짐
            m_bIsOnFire = false;
            m_bPlayAni = false;
            m_fOnTime = 0.f;
            m_Child->Animator2D()->PlayAnimation(L"NONE", true);
            m_pEventScript->SetTrigger(false);
            m_test = 0.f; // test
        }

    }

}

void CFireWoodScript::OnCollisionEnter(CGameObject* _pOther)
{
    //부딪힌 오브젝트 이름 받아옴

    if (nullptr != _pOther->GetScript(L"CFireBowlScript"))
        m_pEventScript->SetTrigger(true);
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {

        PLAYER_ITEM _item = dynamic_cast<CPlayerScript*>(_pOther->GetScript(L"CPlayerScript"))->GetPlayerItem();
        if (_item == PLAYER_ITEM::FIREBOWL) m_pEventScript->SetTrigger(true);
    }
}

void CFireWoodScript::OnCollisionExit(CGameObject* _pOther)
{
    //m_IsOnCol = false;
}

void CFireWoodScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_fSetTime, sizeof(float), 1, _pFile);
}

void CFireWoodScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_fSetTime, sizeof(float), 1, _pFile);
}