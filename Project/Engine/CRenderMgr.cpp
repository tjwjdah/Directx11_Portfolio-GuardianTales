#include "pch.h"
#include "CRenderMgr.h"

#include "CResMgr.h"
#include "CTimeMgr.h"
#include "CDevice.h"
#include "CConstBuffer.h"
#include "CStructuredBuffer.h"

#include "CCamera.h"

CRenderMgr::CRenderMgr()
	: m_iCurNoise(0)
	, m_fAccTime(0.f)
	, m_pLight2DBuffer(nullptr)
	, m_pAnim2DBuffer(nullptr)
{
}

CRenderMgr::~CRenderMgr()
{
	SAFE_DELETE(m_pLight2DBuffer);
	SAFE_DELETE(m_pAnim2DBuffer);

}

void CRenderMgr::init()
{
	Ptr<CTexture> pTex = nullptr;	
	pTex = CResMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_01.png", L"texture\\noise\\noise_01.png");
	m_vecNoiseTex.push_back(pTex);
	/*pTex = CResMgr::GetInst()->Load<CTexture>(L"texture\\noise\\noise_02.png", L"texture\\noise\\noise_02.png");
	m_vecNoiseTex.push_back(pTex);*/

	g_global.vNoiseResolution = Vec2(pTex->Width(), pTex->Height());

	// Light StructuredBuffer Create
	m_pLight2DBuffer = new CStructuredBuffer;
	m_pLight2DBuffer->Create(sizeof(tLight2DInfo), 1, nullptr);

	// Animation 2D Buffer
	m_pAnim2DBuffer = new CStructuredBuffer;
	m_pAnim2DBuffer->Create(sizeof(tAnim2D), 1, nullptr);
		
	// CopyTarget Texture Create
	Vec2 vResolution = Vec2((float)CDevice::GetInst()->GetBufferResolution().x, (float)CDevice::GetInst()->GetBufferResolution().y);
	m_pCopyTarget = CResMgr::GetInst()->CreateTexture(L"PostEffectTargetTex"
		, (UINT)vResolution.x, (UINT)vResolution.y
		, D3D11_BIND_SHADER_RESOURCE
		, DXGI_FORMAT_R8G8B8A8_UNORM);

	// PostEffectMtrl 에 CopyTexture 전달
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"PostEffectMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, m_pCopyTarget.Get());
}

void CRenderMgr::update()
{
	// =================
	// Noise Texture 교체
	// =================
	m_fAccTime += fDT;
	if (m_fAccTime > 0.1f)
	{
		m_fAccTime = 0.f;
		m_iCurNoise += 1;
		if (m_vecNoiseTex.size() == m_iCurNoise)
			m_iCurNoise = 0;
	}

	m_vecNoiseTex[m_iCurNoise]->UpdateData(70, (UINT)PIPELINE_STAGE::PS_ALL);

	// ===================
	// 광원 데이터 업데이트
	// ===================
	g_global.iLight2DCount = (UINT)m_vecLight2D.size();

	if (m_pLight2DBuffer->GetElementCount() < m_vecLight2D.size())
		m_pLight2DBuffer->Create(sizeof(tLight2DInfo), (UINT)m_vecLight2D.size(), nullptr);

	m_pLight2DBuffer->SetData(m_vecLight2D.data(), sizeof(tLight2DInfo), (UINT)m_vecLight2D.size());
	m_pLight2DBuffer->UpdateData(71);

	m_vecLight2D.clear();

	// ==================
	// 전역 데이터 업데이트
	// ==================
	static const CConstBuffer* pGlobalBuffer = CDevice::GetInst()->GetCB(CB_TYPE::GLOBAL_VALUE);
	pGlobalBuffer->SetData(&g_global);
	pGlobalBuffer->UpdateData((UINT)PIPELINE_STAGE::PS_ALL);	
}

void CRenderMgr::render()
{
	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{
		m_vecCam[i]->SortObject();
		m_vecCam[i]->render_forward();		
	}

	for (size_t i = 0; i < m_vecCam.size(); ++i)
	{		
		m_vecCam[i]->render_posteffect();		 		
	}

	m_vecCam.clear();
}

void CRenderMgr::CopyTarget()
{	
	CONTEXT->CopyResource(m_pCopyTarget->GetTex2D().Get(), CDevice::GetInst()->GetRenderTargetTex()->GetTex2D().Get());
}
