#include "pch.h"

#include <Engine\extern.h>

#include "CMapScript.h"
#include <Engine/CTransform.h>
#include <Engine/CTexture.h>
#include <Engine/CResMgr.h>
#include <Engine/CStructuredBuffer.h>
#include <Engine/CConstBuffer.h>

CMapScript::CMapScript():CScript((int)SCRIPT_TYPE::MAPSCRIPT),
m_tileSize(0),
m_tile_x(10),
m_tile_y(10),
m_tileUv_x(0.2f),
m_tileUv_y(0.2f)
{
	
	m_TileBuffer = new CStructuredBuffer;
	m_TSharedBuffer = new CStructuredBuffer;
	m_TSharedBuffer->Create(sizeof(tTileShared), 1, nullptr);

	Ptr<CTexture> pTex  = CResMgr::GetInst()->FindRes<CTexture>(L"TILE");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

CMapScript::~CMapScript()
{
	delete m_TSharedBuffer;
	delete m_TileBuffer;
}

void CMapScript::awake()
{

	SetTileNum(m_tile_x, m_tile_y);
	//m_TSharedBuffer->CreateRW(sizeof(tTileShared), 1, nullptr);	
}

void CMapScript::update()
{

	m_TileShared.iTileXSize = m_tile_x;
	m_TileShared.iTileYSize = m_tile_y;
	//타일이 x y 축으로 몇개인지

	if (m_TileBuffer->GetElementCount() < m_tileSize)
		m_TileBuffer->Create(sizeof(tTile), m_tileSize, nullptr);
	//타일 다시 만들어질경우 버퍼 다시 생성
	m_TileBuffer->SetData(m_tile2D.data(), sizeof(tTile), (UINT)m_tile2D.size());
	m_TileBuffer->UpdateData(101);
	//타일 이미지 시작 위치와 간격에 대한 버퍼
	m_TSharedBuffer->SetData(&m_TileShared, sizeof(tTileShared), (UINT)1);
	m_TSharedBuffer->UpdateData(102);
	//타일 사이즈에 대한 버퍼
	
}

void CMapScript::render()
{



	

	
	
	
	//m_pMesh->render_particle(m_tileSize);
	//m_pMesh->render();
	
}

void CMapScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);

	UINT iCount = (UINT)m_tile2D.size();
	fwrite(&iCount, sizeof(UINT), 1, _pFile);
	for (size_t i = 0; i < m_tile2D.size(); ++i)
	{
		fwrite(&m_tile2D[i], sizeof(tTile), 1, _pFile);
	}
	fwrite(&m_tile_x, sizeof(int), 1, _pFile);
	fwrite(&m_tile_y, sizeof(int), 1, _pFile);
}

void CMapScript::LoadFromScene(FILE* _pFile)
{
	UINT iCount = 0;
	fread(&iCount, sizeof(UINT), 1, _pFile);

	for (UINT i = 0; i < iCount; ++i)
	{
		tTile frm = {};
		fread(&frm, sizeof(tTile), 1, _pFile);
		m_tile2D.push_back(frm);
	}
	fread(&m_tile_x, sizeof(UINT), 1, _pFile);
	fread(&m_tile_y, sizeof(UINT), 1, _pFile);


}



void CMapScript::SetTileNum(int _x, int _y)
{
	m_tile_x = _x;
	m_tile_y = _y;
	Transform()->SetLocalScale(Vec3((float)m_tile_x * TileSize_X, 
		(float)m_tile_y * TileSize_Y, 
		1.f));
	int size = m_tile_x * m_tile_y;
	size_t sizet = (size_t)size;
	m_tile2D.resize(sizet);
	
	//m_TileBuffer->CreateRW(sizeof(tTile), (UINT)m_tile2D.size(), m_tile2D.data());
	m_tileSize = m_tile_x * m_tile_y;
}

void CMapScript::SetTile(int _x, int _y, Vec2 index)
{
	
	if (_x < m_tile_x && _y < m_tile_y)
	{
		int z = _y * m_TileShared.iTileXSize + _x;
		m_tile2D[(size_t)z].vLeftTop.x = index.x * m_tileUv_x;
		m_tile2D[(size_t)z].vLeftTop.y = index.y  * m_tileUv_y;

	}
	
}