#include "pch.h"
#include "CEndBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine/CEventMgr.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>
#include "CPlayerScript.h"
#include "CObjEventScriptMgr.h"
#include "CObjEventScript.h"

CEndBlockScript::CEndBlockScript()
    : CScript((int)SCRIPT_TYPE::ENDBLOCKSCRIPT)
    , m_bIsEnd(false)
    , m_bIsPushed(false)
    , m_Ani(false)
    , m_fAtime(0.f)
    , m_EndTime(0.f)
{
    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "m_StageNum", &m_StageNum));
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"endblock");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"EndBlockMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

    pTex = CResMgr::GetInst()->FindRes<CTexture>(L"endblock2");
    pMtrl->SetData(SHADER_PARAM::TEX_1, pTex.Get());
}

CEndBlockScript::~CEndBlockScript()
{
}

void CEndBlockScript::awake()
{
    m_pEndEffect = CResMgr::GetInst()->FindRes<CPrefab>(L"ExpEffect");
    m_pChildEffect = GetGameObject()->GetChild(L"EndSmokeEffect");

    Transform()->SetLocalPosZ(399.f);
    int a1 = 0;
    MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a1);
}

void CEndBlockScript::update()
{

    if (m_bIsPushed && KEY_HOLD(KEY_TYPE::KEY_Z))
    {
        m_fAtime += fDT;
        if (m_fAtime > 3.f) //end
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_endblock");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            //연기이펙트
            m_pChildEffect->Animator2D()->PlayAnimation(L"NONE", false);

            //폭발 이펙트
            int a = 100;
            MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_0, &a);
            Collider2D()->SetvOffsetScale(Vec2(0.f, 0.f));
            m_bIsEnd = true;

            Vec3 _Pos = Transform()->GetLocalPos(); float py = _Pos.y - 25.f;

            CGameObject* _obj = m_pEndEffect->Instantiate();
            _obj->Transform()->SetLocalScale(Vec3(200.f, 180.f, 1.f));
            _obj->Transform()->SetLocalPos(Vec3(_Pos.x, py, 398.f));

            tEvent e = { };
            e.eEvent = EVENT_TYPE::CREATE_OBJECT;
            e.lParam = (DWORD_PTR)_obj;
            //e.wParam = (DWORD_PTR)4;
            CEventMgr::GetInst()->AddEvent(e);

            //깨진이미지
            Transform()->SetLocalScale(Vec3(128.f, 110.f, 0.f));
            Transform()->SetLocalPosY(_Pos.y - 45.f);
            Transform()->SetLocalPosZ(401.f);
            m_fAtime = 0.f;
        }



        if (!m_Ani)
        {
            m_pChildEffect->Transform()->SetLocalScale(Vec3(0.7f, 0.5f, 1.f));
            m_pChildEffect->Transform()->SetLocalPosY(-0.3);
            m_pChildEffect->Animator2D()->PlayAnimation(L"SMOKE");
            m_Ani = true;
        }

    }

    if (KEY_AWAY(KEY_TYPE::KEY_Z) || KEY_NONE(KEY_TYPE::KEY_Z))
    {
        m_fAtime = 0.f;
        m_pChildEffect->Animator2D()->PlayAnimation(L"NONE");
    }

    if (m_bIsEnd)
    {
        m_EndTime += fDT;

        if (m_EndTime > 1.5f)
        {
            wstring strFilePath = CPathMgr::GetResPath();
            switch (m_StageNum)
            {
            case 0:
            {
                const wstring& Name = L"scene\\Snack.scene";
                strFilePath += Name;

              
            }
            break;
            case 1:
            {
                const wstring& Name = L"scene\\Dungeon.scene";
                strFilePath += Name;
            }
            break;
            case 2:
            {
                const wstring& Name = L"scene\\Desert.scene";
                strFilePath += Name;
            }
            break;
            case 3:
            {
                const wstring& Name = L"scene\\Town.scene";
                strFilePath += Name;
            }
            break;
            }

            CScene* Scene = new CScene;
            
            
            FILE* pFile = nullptr;
            HRESULT hr = _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

            if (nullptr == pFile)
            {
                MessageBox(nullptr, L"Scene Load Failed", L"Error", MB_OK);
                return;
            }
            Scene->LoadFromScene(pFile);
            //Scene->awake();
            //Scene->start();
        
              
          

            CObjEventScriptMgr::GetInst()->LoadFromScene(Scene, pFile);

            fclose(pFile);

            switch (m_StageNum)
            {
            case 0:
            {
                CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Mino").Get()->Instantiate();
                pObject->Transform()->SetLocalPos(Vec3(0.f, 120.f, 400.f));

                Scene->AddObject(pObject, 3);
            }
            break;
            case 1:
            {

                CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Sapa").Get()->Instantiate();
                pObject->Transform()->SetLocalPos(Vec3(0.f, 120.f, 400.f));

                Scene->AddObject(pObject, 3);
                
            }
            break;
            case 2:
            {
                CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Bug").Get()->Instantiate();
                pObject->Transform()->SetLocalPos(Vec3(0.f, 120.f, 400.f));

                Scene->AddObject(pObject, 3);

            }
            break;
            case 3:
            {
                CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Invader").Get()->Instantiate();
                pObject->Transform()->SetLocalPos(Vec3(0.f, 120.f, 400.f));

                Scene->AddObject(pObject, 3);

            }
            break;
            }

            for (int i = 0; i < 4; i++)
            {
                Character Char = CSceneMgr::GetInst()->GetPartyListNum(i);
                switch (Char)
                {
                case Character::NARI:
                {
                    CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Nari").Get()->Instantiate();
                    pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
                    CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                    Player->SetAuto(i);
                    Scene->AddObject(pObject, 1);

                }
                break;
                case Character::MARINA:
                {
                    CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Marina").Get()->Instantiate();
                    pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
                    CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                    Player->SetAuto(i);
                    Scene->AddObject(pObject, 1);
                }
                break;
                case Character::GARAM:
                {
                    CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Garam").Get()->Instantiate();
                    pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
                    CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                    Player->SetAuto(i);
                    Scene->AddObject(pObject, 1);
                }
                break;
                case Character::EVA:
                {
                    CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Eva").Get()->Instantiate();
                    pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
                    CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                    Player->SetAuto(i);
                    Scene->AddObject(pObject, 1);
                }
                break;
                }
            }

            CSceneMgr::GetInst()->ChangeScene(Scene);


        }

    }

}

void CEndBlockScript::OnCollisionEnter(CGameObject* _pOther)
{

    if (_pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = true;
    }


}

void CEndBlockScript::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = false;
        m_Ani = false;
    }
}

void CEndBlockScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    fwrite(&m_StageNum, sizeof(int), 1, _pFile);
}

void CEndBlockScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    fread(&m_StageNum, sizeof(int), 1, _pFile);
}