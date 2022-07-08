#include "pch.h"
#include "CResMgr.h"

#include "CTexture.h"

CResMgr::CResMgr()
{
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		m_vecCloneRes[i].reserve(1000);
	}
}

CResMgr::~CResMgr()
{
	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Vector(m_vecCloneRes[i]);
	}	

	for (UINT i = 0; i < (UINT)RES_TYPE::END; ++i)
	{
		Safe_Delete_Map(m_mapRes[i]);
	}
}

Ptr<CTexture> CResMgr::CreateTexture(const wstring& _strKey, UINT _iWidth, UINT _iHeight, UINT _eFlag, DXGI_FORMAT _eFormat)
{
	Ptr<CTexture> pTex = FindRes<CTexture>(_strKey);

	assert(nullptr == pTex);
	
	pTex = new CTexture;
	if (FAILED(pTex->Create(_iWidth, _iHeight, _eFlag, _eFormat)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"오류", MB_OK);
		return nullptr;
	}

	pTex->SetKey(_strKey);
	m_mapRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(_strKey, pTex.Get()));
	m_bEvent = true;

	return pTex;
}

Ptr<CTexture> CResMgr::CreateTexture(const wstring& _strKey, ComPtr<ID3D11Texture2D> _pTex2D)
{
	Ptr<CTexture> pTex = FindRes<CTexture>(_strKey);

	assert(nullptr == pTex);

	pTex = new CTexture;
	if (FAILED(pTex->Create(_pTex2D)))
	{
		MessageBox(nullptr, L"텍스쳐 생성 실패", L"오류", MB_OK);
		return nullptr;
	}

	pTex->SetKey(_strKey);
	m_mapRes[(UINT)RES_TYPE::TEXTURE].insert(make_pair(_strKey, pTex.Get()));
	m_bEvent = true;
	return pTex;
}
