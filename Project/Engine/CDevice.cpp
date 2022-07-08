#include "pch.h"
#include "CDevice.h"

#include "CCore.h"
#include "CConstBuffer.h"

#include "CResMgr.h"

CDevice::CDevice()
	: m_tViewPort{}
	, m_hOutputWindowHwnd(nullptr)
	, m_ptBufferResolution{}
	, m_bWindow(true)
	, m_arrCB{}
{
}

CDevice::~CDevice()
{		
	// 상수버퍼 해제
	for (UINT i = 0; i < (UINT)CB_TYPE::END; ++i)
	{
		if (nullptr != m_arrCB[i])
			delete m_arrCB[i];
	}
}

int CDevice::init(HWND _hWnd, POINT _ptResolution, bool _bWindow)
{
	m_hOutputWindowHwnd = _hWnd;
	m_ptBufferResolution = _ptResolution;
	m_bWindow = _bWindow;

	g_global.vResolution = Vec2((float)m_ptBufferResolution.x, (float)m_ptBufferResolution.y);


	int iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
		
	D3D_FEATURE_LEVEL eFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag, 0, 0
		, D3D11_SDK_VERSION
		, &m_pDevice, &eFeatureLevel
		, &m_pContext)))
	{
		return E_FAIL;
	}

	//m_pDevice->AddRef();

	// 멀티샘플 레벨체크
	UINT iMultiSampleLevel = 0; // out
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &iMultiSampleLevel);

	if (iMultiSampleLevel <= 0)	
		return E_FAIL;
	
	// SwapChain 생성
	if (FAILED(CreateSwapChain()))
		return E_FAIL;

	// View
	if (FAILED(CreateView()))
		return E_FAIL;

	// ViewPort
	CreateViewPort();

	// Create Sampler
	CreateSamplerState();

	// ConstBuffer
	CreateConstBuffer();

	// Create Blend, DS State
	CreateBlendState();
	CreateDepthStencilState();

	return S_OK;
}

void CDevice::ClearTarget()
{
	// DepthStencilView 를 장치에 전달
	// OM (Output Merge)	
	m_pContext->OMSetRenderTargets(1, m_pRTTex->GetRTV().GetAddressOf(), m_pDSTex->GetDSV().Get());

	float arrClear[4] = { 0.4f, 0.4f, 0.4f, 1.f };
	CONTEXT->ClearRenderTargetView(m_pRTTex->GetRTV().Get(), arrClear);
	CONTEXT->ClearDepthStencilView(m_pDSTex->GetDSV().Get(),  D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC tDesc = {};

	// 출력 윈도우, 출력 모드(전체화면 모드 or 윈도우 모드)
	tDesc.OutputWindow = m_hOutputWindowHwnd;
	tDesc.Windowed = m_bWindow;

	// 버퍼 해상도 및 포맷
	tDesc.BufferDesc.Width = m_ptBufferResolution.x;
	tDesc.BufferDesc.Height = m_ptBufferResolution.y;
	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	tDesc.BufferCount = 1; // 백버퍼 수,

	// 화면 갱신비율
	tDesc.BufferDesc.RefreshRate.Denominator = 1;
	tDesc.BufferDesc.RefreshRate.Numerator = 60;

	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// front, back 버퍼 전환 시 장면 유지 필요 없음
	tDesc.Flags = 0;

	// Anti-Aliasing
	// Deferred Rendering 으로 인한 자체구현 필요
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> pAdapter = nullptr;
	ComPtr<IDXGIFactory> pFactory = nullptr;

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	HRESULT hr = pFactory->CreateSwapChain(m_pDevice.Get(), &tDesc, &m_pSwapChain);
		
	if (FAILED(hr))
		return E_FAIL;

	return S_OK;
}

int CDevice::CreateView()
{
	// SwapChain 의 백버퍼를 포인터로 참조한다.	
	ComPtr<ID3D11Texture2D> pTex2D = nullptr;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pTex2D.GetAddressOf());
	m_pRTTex = CResMgr::GetInst()->CreateTexture(L"SwapChainRenderTargetTex", pTex2D);	

	if (nullptr == m_pRTTex)
		return E_FAIL;
	
	// DepthStencl Texture 생성
	m_pDSTex = CResMgr::GetInst()->CreateTexture(L"DepthStencilTex", m_ptBufferResolution.x, m_ptBufferResolution.y
		,D3D11_BIND_DEPTH_STENCIL , DXGI_FORMAT_D24_UNORM_S8_UINT);

	return 0;
}

void CDevice::CreateViewPort()
{
	POINT ptWinRes = CCore::GetInst()->GetWndResolution();

	m_tViewPort.Width = (float)ptWinRes.x;
	m_tViewPort.Height = (float)ptWinRes.y;
	m_tViewPort.MinDepth = 0.f;
	m_tViewPort.MaxDepth = 1.f;

	m_pContext->RSSetViewports(1, &m_tViewPort);
}

void CDevice::CreateConstBuffer()
{
	m_arrCB[(UINT)CB_TYPE::TRANSFORM] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::TRANSFORM]->Create(CB_TYPE::TRANSFORM, sizeof(tTransform));

	m_arrCB[(UINT)CB_TYPE::MATERIAL] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::MATERIAL]->Create(CB_TYPE::MATERIAL, sizeof(tMtrlInfo));

	m_arrCB[(UINT)CB_TYPE::GLOBAL_VALUE] = new CConstBuffer;
	m_arrCB[(UINT)CB_TYPE::GLOBAL_VALUE]->Create(CB_TYPE::GLOBAL_VALUE, sizeof(tGlobalValue));
}

void CDevice::CreateSamplerState()
{
	D3D11_SAMPLER_DESC tDesc = {};

	tDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	DEVICE->CreateSamplerState(&tDesc, m_arrSam[0].GetAddressOf());

	tDesc = {};
	tDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	tDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	DEVICE->CreateSamplerState(&tDesc, m_arrSam[1].GetAddressOf());

	ID3D11SamplerState* arrSam[2] = { m_arrSam[0].Get(), m_arrSam[1].Get() };

	CONTEXT->VSSetSamplers(0, 2, arrSam);
	CONTEXT->HSSetSamplers(0, 2, arrSam);
	CONTEXT->DSSetSamplers(0, 2, arrSam);
	CONTEXT->GSSetSamplers(0, 2, arrSam);
	CONTEXT->PSSetSamplers(0, 2, arrSam);
	CONTEXT->CSSetSamplers(0, 2, arrSam);
}

void CDevice::CreateBlendState()
{
	m_arrBS[(UINT)BLEND_TYPE::DEFAULT] = nullptr;

	D3D11_BLEND_DESC tDesc = {};
	tDesc.AlphaToCoverageEnable = true;	
	tDesc.IndependentBlendEnable = false;	
	tDesc.RenderTarget[0].BlendEnable = true;
	tDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlend =  D3D11_BLEND_SRC_ALPHA;
	tDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	tDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	tDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	
	tDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&tDesc, m_arrBS[(UINT)BLEND_TYPE::ALPHABLEND].GetAddressOf());	
		
	tDesc.AlphaToCoverageEnable = false;
	tDesc.IndependentBlendEnable = false;
	tDesc.RenderTarget[0].BlendEnable = true;
	tDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	tDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

	tDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	tDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	tDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&tDesc, m_arrBS[(UINT)BLEND_TYPE::ALPHA_ONE].GetAddressOf());
}

void CDevice::CreateDepthStencilState()
{
	m_arrDSS[(UINT)DS_TYPE::LESS] = nullptr;

	D3D11_DEPTH_STENCIL_DESC tDesc = {};

	// Less Equal
	tDesc.StencilEnable = false;
	tDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.DepthEnable = true;
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::LESS_EQUAL].GetAddressOf());

	// Greater
	tDesc.StencilEnable = false;
	tDesc.DepthFunc = D3D11_COMPARISON_GREATER;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.DepthEnable = true;
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::GREATER].GetAddressOf());

	// Greater Equal
	tDesc.StencilEnable = false;
	tDesc.DepthFunc = D3D11_COMPARISON_GREATER_EQUAL;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	tDesc.DepthEnable = true;
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::GREATER_EQUAL].GetAddressOf());

	// No Test
	tDesc.StencilEnable = false;
	tDesc.DepthEnable = true;					// 깊이 옵션 사용
	tDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;	// 항상 통과(테스트 x)
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // 깊이는 기록
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::NO_TEST].GetAddressOf());

	// Less, No Write	
	tDesc.StencilEnable = false;
	tDesc.DepthEnable = true;
	tDesc.DepthFunc = D3D11_COMPARISON_LESS;
	tDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::LESS_NO_WRITE].GetAddressOf());


	// No Test, No Write	
	tDesc.StencilEnable = false;
	tDesc.DepthEnable = false;	
	DEVICE->CreateDepthStencilState(&tDesc, m_arrDSS[(UINT)DS_TYPE::NO_TEST_NO_WRITE].GetAddressOf());
}
