#include "pch.h"
#include "CBtnScript.h"

#include <Engine/CCore.h>
#include <Engine/CScene.h>
#include <Engine/CSceneMgr.h>
#include <Engine\CResMgr.h>

#include "CObjEventScriptMgr.h"
#include <Engine\CEventMgr.h>;
#include  "CPlayerScript.h"
CBtnScript::CBtnScript()
    : CScript((UINT)SCRIPT_TYPE::BTNSCRIPT)
    , m_width(0.f)
    , m_height(0.f)
    , m_PlayerAdd(false)

{

    m_Res = CCore::GetInst()->GetWndResolution();
}

CBtnScript::~CBtnScript()
{
}

void CBtnScript::awake()
{
   m_height = Transform()->GetLocalScale().y/2.f;
  m_width = Transform()->GetLocalScale().x/2.f;
}

void CBtnScript::update()
{
    Vec3 pos = Transform()->GetLocalPos();
    POINT mospos = CKeyMgr::GetInst()->GetMousePos();
    Vec2 test = {};
    mospos.x = mospos.x - m_Res.x / 2;
    mospos.y = -mospos.y + m_Res.y / 2;
    
    if (KEY_TAP(KEY_TYPE::LBTN))
    {
        if ((pos.x - m_width / 2 <= mospos.x && mospos.x <= pos.x + m_width / 2)
            && (pos.y - m_height / 2 <= mospos.y && mospos.y <= pos.y + m_height / 2))
        {
            CScene* Scene = new CScene;
            wstring strFilePath = CPathMgr::GetResPath();
            const wstring& Name = m_SName;
            strFilePath += Name;
            FILE* pFile = nullptr;
            HRESULT hr = _wfopen_s(&pFile, strFilePath.c_str(), L"rb");
           
            if (nullptr == pFile)
            {
                MessageBox(nullptr, L"Scene Load Failed", L"Error", MB_OK);
                return;
            }
            Scene->LoadFromScene(pFile);
           

            CObjEventScriptMgr::GetInst()->LoadFromScene(Scene, pFile);
            fclose(pFile);

           // Scene->awake();
            //Scene->start();
            if (m_PlayerAdd)
            {
           
                    Vec2 m_Pos;
                    if (m_SName == L"scene\\maze0.scene")
                    {
                        m_Pos.x = 1760.f;
                        m_Pos.y =-224.f;

                    }else if (m_SName == L"scene\\maze1.scene")
                    {
                        m_Pos.x = 0.f;
                        m_Pos.y = 0.f;

                    }else if (m_SName == L"scene\\maze2.scene")
                    {
                        m_Pos.x = 1856.f;
                        m_Pos.y = -256.f;

                    }else if (m_SName == L"scene\\maze3.scene")
                    {
                       
                        m_Pos.x = -547.f;
                        m_Pos.y = 109.f;

                    }

                    Character Char = CSceneMgr::GetInst()->GetPartyListNum(0);
                    switch (Char)
                    {
                    case Character::NARI:
                    {
                        CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Nari").Get()->Instantiate();
                        pObject->Transform()->SetLocalPos(Vec3(m_Pos.x, m_Pos.y, 400.f));
                        CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                        Player->SetAuto(0);
                        Scene->AddObject(pObject, 1);

                    }
                    break;
                    case Character::MARINA:
                    {
                        CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Marina").Get()->Instantiate();
                        pObject->Transform()->SetLocalPos(Vec3(m_Pos.x, m_Pos.y, 400.f));
                        CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                        Player->SetAuto(0);
                        Scene->AddObject(pObject, 1);
                    }
                    break;
                    case Character::GARAM:
                    {
                        CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Garam").Get()->Instantiate();
                        pObject->Transform()->SetLocalPos(Vec3(m_Pos.x, m_Pos.y, 400.f));
                        CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                        Player->SetAuto(0);
                        Scene->AddObject(pObject, 1);
                    }
                    break;
                    case Character::EVA:
                    {
                        CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Eva").Get()->Instantiate();
                        pObject->Transform()->SetLocalPos(Vec3(m_Pos.x, m_Pos.y, 400.f));
                        CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
                        Player->SetAuto(0);
                        Scene->AddObject(pObject, 1);;
                    }
                    break;
                    }
                   
                       
                   
            }

            CSceneMgr::GetInst()->ChangeScene(Scene);

            //scene initialize()
           // Scene->awake();
           // Scene->start();
        }
    }
}

void CBtnScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
    SaveWString(m_SName, _pFile);
    fwrite(&m_PlayerAdd, sizeof(bool), 1, _pFile);
    
}

void CBtnScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
    LoadWString(m_SName, _pFile);
    fread(&m_PlayerAdd, sizeof(bool), 1, _pFile);
    
}