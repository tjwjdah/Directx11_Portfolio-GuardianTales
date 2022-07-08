#pragma once

#include "CSingleton.h"

#include "Ptr.h"
#include "CTexture.h"
#include "CLight2D.h"

class CStructuredBuffer;
class CCamera;

class CRenderMgr
	: public CSingleton<CRenderMgr>
{
	SINGLE(CRenderMgr)
private:
	vector<Ptr<CTexture>>	m_vecNoiseTex;
	int						m_iCurNoise;
	float					m_fAccTime;

	vector<tLight2DInfo>	m_vecLight2D;
	CStructuredBuffer*		m_pLight2DBuffer;

	Ptr<CTexture>			m_pCopyTarget;		// swapchain backbuffer copy
	vector<CCamera*>		m_vecCam;

	CStructuredBuffer*      m_pAnim2DBuffer;	// 2D Animation 정보 전달

public:
	void init();
	void update();
	void render();

public:
	void RegisterLight2D(CLight2D* _pLight2D){m_vecLight2D.push_back(_pLight2D->GetInfo());}
	void RegisterCamera(CCamera* _pCam) { m_vecCam.push_back(_pCam); }
	void CopyTarget(); // SwapChain backbuffer 를 후처리용 리소스 텍스쳐에 복사한다.

	CStructuredBuffer* GetAnim2DBuffer() { return m_pAnim2DBuffer; }
};

