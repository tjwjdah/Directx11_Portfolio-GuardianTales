#include "pch.h"
#include "CTexture.h"

#include "CDevice.h"

CTexture::CTexture()
	: m_Image()
	, m_pTex2D(nullptr)
	, m_pSRV(nullptr)
{
}

CTexture::~CTexture()
{
	//if (L"texture\\noise\\noise_01.png" == GetKey())
	//	int a = 0;
}


int CTexture::Create(UINT _iWidth, UINT _iHeight, UINT _eFlag, DXGI_FORMAT _eFormat)
{
	// 텍스쳐 생성
	m_tDesc.ArraySize = 1;
	m_tDesc.BindFlags = _eFlag;
	m_tDesc.Format = _eFormat;

	m_tDesc.CPUAccessFlags = 0;
	m_tDesc.Usage = D3D11_USAGE_DEFAULT;

	m_tDesc.Width = _iWidth;
	m_tDesc.Height = _iHeight;
	m_tDesc.MipLevels = 1;
	m_tDesc.MiscFlags = 0;
	m_tDesc.SampleDesc.Count = 1;
	m_tDesc.SampleDesc.Quality = 0;

	HRESULT hr = DEVICE->CreateTexture2D(&m_tDesc, nullptr, m_pTex2D.GetAddressOf());
	if (FAILED(hr))
		return E_FAIL;

	if (D3D11_BIND_DEPTH_STENCIL & _eFlag)
	{
		// DepthStencilView 생성
		hr = DEVICE->CreateDepthStencilView(m_pTex2D.Get(), nullptr, m_pDSV.GetAddressOf());
		if (FAILED(hr))
			return E_FAIL;
	}
	else
	{
		if (D3D11_BIND_RENDER_TARGET & _eFlag)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateRenderTargetView(m_pTex2D.Get(), nullptr, m_pRTV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}

		if (D3D11_BIND_SHADER_RESOURCE & _eFlag)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateShaderResourceView(m_pTex2D.Get(), nullptr, m_pSRV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}

		if (D3D11_BIND_UNORDERED_ACCESS & _eFlag)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateUnorderedAccessView(m_pTex2D.Get(), nullptr, m_pUAV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}
	}

	return S_OK;
}

int CTexture::Create(ComPtr<ID3D11Texture2D> _pTex2D)
{
	m_pTex2D = _pTex2D;
	m_pTex2D->GetDesc(&m_tDesc);

	HRESULT hr = S_OK;
	if (D3D11_BIND_DEPTH_STENCIL & m_tDesc.BindFlags)
	{
		// DepthStencilView 생성
		hr = DEVICE->CreateDepthStencilView(m_pTex2D.Get(), nullptr, m_pDSV.GetAddressOf());
		if (FAILED(hr))
			return E_FAIL;
	}
	else
	{
		if (D3D11_BIND_RENDER_TARGET & m_tDesc.BindFlags)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateRenderTargetView(m_pTex2D.Get(), nullptr, m_pRTV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}

		if (D3D11_BIND_SHADER_RESOURCE & m_tDesc.BindFlags)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateShaderResourceView(m_pTex2D.Get(), nullptr, m_pSRV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}

		if (D3D11_BIND_UNORDERED_ACCESS & m_tDesc.BindFlags)
		{
			// RenderTargetView 생성
			hr = DEVICE->CreateUnorderedAccessView(m_pTex2D.Get(), nullptr, m_pUAV.GetAddressOf());
			if (FAILED(hr))
				return E_FAIL;
		}
	}

	return hr;
}

void CTexture::Save(const wstring& _strRelativePath)
{
	
}


void CTexture::Load(const wstring& _strFilePath)
{
	wstring strExt = path(_strFilePath).extension();

	HRESULT hr = S_OK;
	if (L".dds" == strExt || L".DDS" == strExt)
	{
		hr = LoadFromDDSFile(_strFilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_Image);
	}
	else if (L".tga" == strExt || L".TGA" == strExt)
	{
		hr = LoadFromTGAFile(_strFilePath.c_str(), nullptr, m_Image);
	}
	else // png, jpg, jpeg, bmp (WIC)
	{
		hr = LoadFromWICFile(_strFilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_Image);
	}

	// 텍스쳐 로딩 실패
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"텍스쳐 로딩 실패", L"텍스쳐 로딩 에러", MB_OK);
		assert(nullptr);
	}

	hr = CreateShaderResourceView(DEVICE, m_Image.GetImages(), m_Image.GetImageCount(), m_Image.GetMetadata(), &m_pSRV);

	// 텍스쳐 로딩 실패
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Shader Resource View 생성 실패", L"텍스쳐 로딩 에러", MB_OK);
		assert(nullptr);
	}

	m_pSRV->GetResource((ID3D11Resource**)m_pTex2D.GetAddressOf());
	m_pTex2D->GetDesc(&m_tDesc);
}



void CTexture::UpdateData(UINT _iRegisterNum, UINT _iPipelineStage)
{
	if ((UINT)PIPELINE_STAGE::PS_VERTEX & _iPipelineStage)
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if ((UINT)PIPELINE_STAGE::PS_HULL & _iPipelineStage)
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if ((UINT)PIPELINE_STAGE::PS_DOMAIN & _iPipelineStage)
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if ((UINT)PIPELINE_STAGE::PS_GEOMETRY & _iPipelineStage)
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if ((UINT)PIPELINE_STAGE::PS_PIXEL & _iPipelineStage)
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());

	if ((UINT)PIPELINE_STAGE::PS_COMPUTE & _iPipelineStage)
		CONTEXT->CSSetShaderResources(_iRegisterNum, 1, m_pSRV.GetAddressOf());
}

void CTexture::UpdateDataRW(UINT _iRegisterNum)
{
	UINT i = -1;
	CONTEXT->CSSetUnorderedAccessViews(_iRegisterNum, 1, m_pUAV.GetAddressOf(), &i);
}

void CTexture::Clear(UINT _iRegisterNum, UINT _iPipelineStage)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	if ((UINT)PIPELINE_STAGE::PS_VERTEX & _iPipelineStage)
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, &pSRV);

	if ((UINT)PIPELINE_STAGE::PS_HULL & _iPipelineStage)
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, &pSRV);

	if ((UINT)PIPELINE_STAGE::PS_DOMAIN & _iPipelineStage)
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, &pSRV);

	if ((UINT)PIPELINE_STAGE::PS_GEOMETRY & _iPipelineStage)
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, &pSRV);

	if ((UINT)PIPELINE_STAGE::PS_PIXEL & _iPipelineStage)
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, &pSRV);

	if ((UINT)PIPELINE_STAGE::PS_COMPUTE & _iPipelineStage)
		CONTEXT->CSSetShaderResources(_iRegisterNum, 1, &pSRV);
}

void CTexture::ClearRW(UINT _iRegisterNum)
{
	ID3D11UnorderedAccessView* pUAV = nullptr;
	UINT i = -1;
	CONTEXT->CSSetUnorderedAccessViews(_iRegisterNum, 1,  &pUAV, &i);
}
