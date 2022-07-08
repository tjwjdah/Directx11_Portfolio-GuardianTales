#include "pch.h"
#include "BtnGUI.h"

#include "imgui.h"
#include <Script\CObjEventScriptMgr.h>
#include <Engine\CPathMgr.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CCore.h>
#include "CSaveLoadMgr.h"
#include "InspectorGUI.h"
#include "CImGUIMgr.h"
#include "MaptoolGUI.h"
#include "EventGUI.h"
#include "ResGUI.h"
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CComponent.h>
BtnGUI::BtnGUI()
    : m_arrIcon{},
    m_SaveIcon(nullptr),
    m_LoadIcon(nullptr)
{

}

BtnGUI::~BtnGUI()
{
    Safe_Delete_Array(m_arrIcon);
}

void BtnGUI::init()
{
    wstring strFilePath = CPathMgr::GetResPath();

    m_arrIcon[(UINT)SCENE_STATE::PLAY] = new CTexture;
    m_arrIcon[(UINT)SCENE_STATE::PLAY]->Load(strFilePath + L"icon\\Play.png");

    m_arrIcon[(UINT)SCENE_STATE::PAUSE] = new CTexture;
    m_arrIcon[(UINT)SCENE_STATE::PAUSE]->Load(strFilePath + L"icon\\Pause.png");

    m_arrIcon[(UINT)SCENE_STATE::STOP] = new CTexture;
    m_arrIcon[(UINT)SCENE_STATE::STOP]->Load(strFilePath + L"icon\\Stop.png");
    m_SaveIcon = CResMgr::GetInst()->FindRes<CTexture>(L"SaveButton");
    m_LoadIcon = CResMgr::GetInst()->FindRes<CTexture>(L"LoadButton");

}

void BtnGUI::update()
{
}

void BtnGUI::render()
{
    // 현제 Scene
    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();


    bool bOpen = true;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar;
    ImGui::Begin("##BtnGUI", &bOpen, window_flags);

    Vec2 uv_min = Vec2(0.0f, 0.0f);                 // Top-left
    Vec2 uv_max = Vec2(1.0f, 1.0f);                 // Lower-right
    Vec2 teszie = Vec2(50.f, 50.f);            // Texture render size
    Vec4 tint_col = Vec4(1.0f, 1.0f, 1.0f, 1.0f);   // No tint
    Vec4 bg_col = Vec4(1.0f, 1.0f, 1.0f, 0.f); // 50% opaque white


    if (pCurScene->GetState() != SCENE_STATE::PLAY)
    {
        // Play 버튼을 눌렀다.
        if (ImGui::ImageButton(m_arrIcon[(UINT)SCENE_STATE::PLAY]->GetSRV().Get(), teszie, uv_min, uv_max, 1, bg_col, tint_col))
        {
            ChangeSceneState(pCurScene, SCENE_STATE::PLAY);

        }
    }
    else
    {
        // Pause 버튼을 눌렀다.
        if (ImGui::ImageButton(m_arrIcon[(UINT)SCENE_STATE::PAUSE]->GetSRV().Get(), teszie, uv_min, uv_max, 1, bg_col, tint_col))
        {
            ChangeSceneState(pCurScene, SCENE_STATE::PAUSE);

        }
    }

    ImGui::SameLine();

    // 정지버튼을 누른경우   
    if (ImGui::ImageButton(m_arrIcon[(UINT)SCENE_STATE::STOP]->GetSRV().Get(), teszie, uv_min, uv_max, 1, bg_col, tint_col))
    {
        ChangeSceneState(pCurScene, SCENE_STATE::STOP);
    }

    ImGui::SameLine();
    //Save
    if (ImGui::ImageButton(m_SaveIcon->GetSRV().Get(), teszie, uv_min, uv_max, 1, bg_col, tint_col))
    {
        OPENFILENAME ofn = {};       // common dialog box structure
        wchar_t szFile[260] = { 0 };       // if using TCHAR macros

        wstring strMapFilePath = CPathMgr::GetResPath();
        strMapFilePath += L"scene\\";

        // Initialize OPENFILENAME   
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = CCore::GetInst()->GetWndHwnd();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = L"\0scene\0*.scene\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = strMapFilePath.c_str(); // 탐색창 초기 경로
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        GetSaveFileName(&ofn);
        wstring strOutput = ofn.lpstrFile;

        // 타일 정보 저장
        // 파일 열기
        FILE* pFile = nullptr;

        // 쓰기모드
        // 파일이 있으면 덮어쓰고, 없으면 만든다.
        strOutput += L".scene";
        _wfopen_s(&pFile, strOutput.c_str(), L"wb");

        // 파일 열기 실패
        if (nullptr == pFile)
        {
            MessageBox(nullptr, L"씬 저장 실패", L"에러", MB_OK);
            return;
        }

        // 타일 정보 저장
        CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
        pCurScene->SaveToScene(pFile);
        CObjEventScriptMgr::GetInst()->SaveToScene(pFile);
        fclose(pFile);
    }
    ImGui::SameLine();
    //LOAD

    if (ImGui::ImageButton(m_LoadIcon->GetSRV().Get(), teszie, uv_min, uv_max, 1, bg_col, tint_col))
    {
        OPENFILENAME ofn = {};       // common dialog box structure
        wchar_t szFile[260] = { 0 };       // if using TCHAR macros

        wstring strMapFilePath = CPathMgr::GetResPath();
        strMapFilePath += L"scene\\";

        // Initialize OPENFILENAME   
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = CCore::GetInst()->GetWndHwnd();
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = L"\0scene\0*.scene\0";
        ofn.nFilterIndex = 1;
        ofn.lpstrFileTitle = NULL;
        ofn.nMaxFileTitle = 0;
        ofn.lpstrInitialDir = strMapFilePath.c_str(); // 탐색창 초기 경로
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        GetOpenFileName(&ofn);
        wstring strOutput = ofn.lpstrFile;
        CScene* pScene = new CScene;

        FILE* pFile = nullptr;
        HRESULT hr = _wfopen_s(&pFile, strOutput.c_str(), L"rb");

        if (nullptr == pFile)
        {
            MessageBox(nullptr, L"Scene Load Failed", L"Error", MB_OK);
            return;
        }

        pScene->LoadFromScene(pFile);
        pScene->awake();
        pScene->start();

        CObjEventScriptMgr::GetInst()->LoadFromScene(pScene, pFile);
        fclose(pFile);
        CSceneMgr::GetInst()->ChangeScene(pScene);

        // InspeactorGUI 의 타겟 오브젝트 무효화
        InspectorGUI* pInspector = (InspectorGUI*)CImGUIMgr::GetInst()->FindGUI(L"Inspector");
        pInspector->SetTargetObject(nullptr);
        EventGUI* Event = (EventGUI*)CImGUIMgr::GetInst()->FindGUI(L"Event");
        Event->SetEventScript(nullptr);
        pScene->SetState(SCENE_STATE::STOP);
    }

    ImGui::End();
}

void BtnGUI::ChangeSceneState(CScene* _pScene, SCENE_STATE _eState)
{
    // 정지 -> 플레이
    if (SCENE_STATE::STOP == _pScene->GetState() && SCENE_STATE::PLAY == _eState)
    {
        CSaveLoadMgr::SaveScene(_pScene, L"scene\\temp.scene");

        _pScene->awake();
        _pScene->start();
       // CImGUIMgr::GetInst()->FindGUI(L"Maptool")->init();
        CImGUIMgr::GetInst()->FindGUI(L"Resources")->init();

    }

    else if (_pScene->GetState() != SCENE_STATE::STOP && _eState == SCENE_STATE::STOP)
    {
        _pScene = new CScene;

        CSaveLoadMgr::LoadScene(_pScene, L"scene\\temp.scene");
        CSceneMgr::GetInst()->ChangeScene(_pScene);

        // InspeactorGUI 의 타겟 오브젝트 무효화
        InspectorGUI* pInspector = (InspectorGUI*)CImGUIMgr::GetInst()->FindGUI(L"Inspector");
        EventGUI* Event = (EventGUI*)CImGUIMgr::GetInst()->FindGUI(L"Event");
        pInspector->SetTargetObject(nullptr);
        Event->SetEventScript(nullptr);

    }


    _pScene->SetState(_eState);
}