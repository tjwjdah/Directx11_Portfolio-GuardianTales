#include "pch.h"
#include "ResGUI.h"

#include <Engine\CRes.h>
#include <Engine\CResMgr.h>

#include "CImGUIMgr.h"
#include "InspectorGUI.h"
#include "TreeCtrl.h"


#include <Engine\CSceneMgr.h>
#include <Engine\CPrefab.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CScene.h>
#include <Engine\CEventMgr.h>
#include <Script\CMapScript.h>
#include <Engine/CCore.h>


ResGUI::ResGUI() :m_On(false),
m_PrefabObj(nullptr)
{
    m_Tree.SetSelChangeCallBack((SEL_CHANGE_CALLBACK)&ResGUI::SelectResource, this);
}

ResGUI::~ResGUI()
{
}
void ResGUI::init()
{
    m_Map = (CMapScript*)CSceneMgr::GetInst()->GetCurScene()->FindObjectByName(L"Background")->GetScript(L"CMapScript");
    m_Res = CCore::GetInst()->GetWndResolution();
}
void ResGUI::update()
{
    if (CSceneMgr::GetInst()->GetCurScene()->GetState() == SCENE_STATE::STOP)
        return;
    if (m_PrefabObj.Get() != nullptr && m_On)
    {


        if (KEY_TAP(KEY_TYPE::LBTN)) {

            InspectorGUI* pInspector = (InspectorGUI*)CImGUIMgr::GetInst()->FindGUI(L"Inspector");
            if (pInspector->GetTargetObj() != nullptr || pInspector->GetResObj() == nullptr)
                return;
            Vec3 Pos = m_Map->GetGameObject()->Transform()->GetWorldPos() - CamaraPos;
            Vec3 Scale = m_Map->GetGameObject()->Transform()->GetLocalScale();
            POINT _Pos = CKeyMgr::GetInst()->GetMousePos();
            if (_Pos.x < 0.f || _Pos.x >1280.f || _Pos.y < 0 || _Pos.y>720)
                return;
            /*  _Pos.x = _Pos.x - 800;
              _Pos.y = -_Pos.y + 450;*/
            _Pos.x = _Pos.x - m_Res.x / 2;
            _Pos.y = -_Pos.y + m_Res.y / 2;

            if (_Pos.x > Pos.x - Scale.x / 2 &&
                _Pos.x < Pos.x + Scale.x / 2 &&
                _Pos.y > Pos.y - Scale.y / 2 &&
                _Pos.y < Pos.y + Scale.y / 2)
            {
                float xsize = (float)(m_Map->GetTileX()) / 2.f;
                float ysize = (float)(m_Map->GetTileY()) / 2.f;
                int x = (_Pos.x - (Pos.x - Scale.x / 2)) / TileSize_X;
                //int x = (_Pos.x - Pos.x)/ TileSize_X;
                int y = ((Pos.y + Scale.y / 2) - _Pos.y) / TileSize_Y;
                int z = y * m_Map->GetTileX() + x;
                CGameObject* pObject = m_PrefabObj->GetGameObject();
                int x1 = pObject->Transform()->GetLocalScale().x;
                int y1 = pObject->Transform()->GetLocalScale().y;
                int xn = 0;   int yn = 0;
                for (int i = 0; i < y1;)
                {
                    xn = 0;
                    for (int l = 0; l < x1;)
                    {
                        l = l + 64;
                        xn++;
                    }
                    yn++;
                    i = i + 64;
                }
              
              /*
                결국 오브젝트 위치는 마우스 위치 + 카메라 위치로 해주고 그다음에 타일 사이즈를 나눈다음 다시 곱해서 넣어주면 댐
                근데 그렇게 할경우 마우스 좌표가 -이면  -63일경우 -1이 되는게 아니라 0이 되므로 이런게 문제가 생김
                그래서 스케일 반만큼 더해서 죄다 양수 위치로 자표 잡은다음에 다시뺴줘서 해결 
                결국 x 는  ((_Pos.x - m_Map->GetGameObject()->Transform()->GetWorldPos() - CamaraPos) + Scale.x / 2)) / TileSize_X; 
                맵오브젝트는 0.0 고정  (_Pos.x +  CamaraPos) + Scale.x / 2)) / TileSize_X; 
              */
                Vec3 ObjPos = Vec3(-(xsize * TileSize_X) + (x * TileSize_X) + TileSize_X / 2 * xn + m_PrefabObj->GetOffSet().x,
                    (ysize * TileSize_Y) - (y * TileSize_Y) - TileSize_Y / 2 * yn + m_PrefabObj->GetOffSet().y,
                    400.f);
                pObject = m_PrefabObj->Instantiate();
                string name = pInspector->GetObjectName();
                pObject->SetName(wstring(name.begin(), name.end()));
                //pObject->SetName(L"Tile_Collsion");
                pObject->Transform()->SetLocalPos(ObjPos);
                tEvent even = {};
                even.eEvent = EVENT_TYPE::CREATE_OBJECT;
                even.lParam = (DWORD_PTR)pObject;
                even.wParam = (DWORD_PTR)pInspector->GetLayerIndex();
                CEventMgr::GetInst()->AddEvent(even);
                pInspector->ID_Plus();
            }
        }
    }

}
void ResGUI::Reset()
{

    m_Tree.Clear();
    tTreeItem* pDummyRoot = m_Tree.UseDummyRoot("Dummy");

    for (UINT i = 0; i <= (UINT)RES_TYPE::PREFAB; ++i)
    {
        string strLabel = GetString(g_szResName[i]);
        tTreeItem* pHeadItem = m_Tree.AddItem(pDummyRoot, strLabel, 0);

        const map<wstring, CRes*> mapRes = CResMgr::GetInst()->GetRes((RES_TYPE)i);

        for (const auto& pair : mapRes)
        {
            CRes* pRes = pair.second;
            m_Tree.AddItem(pHeadItem, GetString(pRes->GetKey().c_str()), (DWORD_PTR)pRes);
        }
    }


}



void ResGUI::render()
{
    ImGui::Begin("Prefab");

    if (CResMgr::GetInst()->HasEvnOcrd())
    {
        Reset();
    }

    m_Tree.render();

    bool bOpen = m_On;
    if (ImGui::Checkbox("PrefabAdd", &bOpen)) {
        if (!bOpen)
        {
            m_PrefabObj = nullptr;
        }
        m_On = bOpen;
    }

    ImGui::End();
}

void ResGUI::SelectResource(const void* _SelChangedData)
{
    const tTreeItem* pSelectedItem = m_Tree.GetSelectedItem();

    string restypename;
    RES_TYPE eResType = RES_TYPE::END;

    for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
    {
        restypename = GetString(g_szResName[i]);
        if (pSelectedItem->GetParent()->GetLabel() == restypename)
        {
            eResType = (RES_TYPE)i;
            break;
        }
    }

    // 특정 리소스를 클릭한게 아닌 경우
    if (eResType == RES_TYPE::END)
        return;

    tData* pData = (tData*)_SelChangedData;
    InspectorGUI* pInspector = (InspectorGUI*)CImGUIMgr::GetInst()->FindGUI(L"Inspector");
    pInspector->SetTargetResource((CRes*)pData->dwData, eResType);
    if (eResType == RES_TYPE::PREFAB)
    {
        m_PrefabObj = (CPrefab*)pData->dwData;

    }
}