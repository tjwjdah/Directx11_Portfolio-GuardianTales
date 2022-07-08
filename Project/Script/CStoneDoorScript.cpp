#include "pch.h"
#include "CStoneDoorScript.h"
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include "CRedButtonScript.h"
#include "CObjEventScript.h"

CStoneDoorScript::CStoneDoorScript()
    : CScript((int)SCRIPT_TYPE::STONEDOORSCRIPT)
    , m_MtrlClone(true)
{
    //테스트 씬에서 redbutton 스크립트 받아옴


    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"stonedoor");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

    pTex = CResMgr::GetInst()->FindRes<CTexture>(L"stonedoor2");
    pMtrl->SetData(SHADER_PARAM::TEX_1, pTex.Get());
}

CStoneDoorScript::~CStoneDoorScript()
{
}

void CStoneDoorScript::awake()
{
    m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
    
   
}

void CStoneDoorScript::update()
{

    //현재 씬의 버튼 스크립트에서 bool값 받아옴
    if (m_pEventScript != nullptr)
    {
        if (m_pEventScript->GetTrigger())
        {
            int a = 100;
            if (m_MtrlClone)
            {
                MeshRender()->GetCloneMaterial();
                m_MtrlClone = false;
            }
            MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a);
            // ++ 충돌체 제거
            GetGameObject()->Collider2D()->SetvOffsetScale(Vec2(0.f, 0.f));
            
            GetGameObject()->Collider2D()->SetvOffsetPos(Vec2(99999.f, 99999.f));
        }
        else
        {
            int a = 0;
            if (!m_MtrlClone)
            {
                MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));
                m_MtrlClone = true;
            }
            GetGameObject()->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.75f));
            GetGameObject()->Collider2D()->SetvOffsetPos(Vec2(0.f, -15.f));
            MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a);
        }
    }


    //눌린것이 아니면 1을 계속 전달   
    // //쉐이더에 값 전달
}

void CStoneDoorScript::OnCollisionEnter(CGameObject* _pOther)
{


}

void CStoneDoorScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
  

}

void CStoneDoorScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    

}