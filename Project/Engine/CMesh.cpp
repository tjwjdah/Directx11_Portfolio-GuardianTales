#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh()
	: m_tVBDesc{}
	, m_tIBDesc{}
	, m_eTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CMesh::~CMesh()
{
}

void CMesh::Create(VTX* _pVTXSysmem, UINT _iVtxCount, UINT* _IdxSysmem, UINT _iIdxCount)
{
	m_iVtxCount = _iVtxCount;
	m_iIdxCount = _iIdxCount;
	
	// GPU 메모리에 Vertex Buffer 만들기
	m_tVBDesc.ByteWidth = sizeof(VTX) * m_iVtxCount;	// GPU 에 생성할 버퍼 메모리 크기
	m_tVBDesc.Usage = D3D11_USAGE_DEFAULT;				// 수정 불가능
	m_tVBDesc.CPUAccessFlags = 0;						// 수정 불가능
	m_tVBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// Vertex Buffer 용도

	D3D11_SUBRESOURCE_DATA tSubDesc = {};
	tSubDesc.pSysMem = _pVTXSysmem;							// 초기 데이터

	HRESULT hr = DEVICE->CreateBuffer(&m_tVBDesc, &tSubDesc, &m_pVB);

	// GPU 메모리에 Index Buffer 만들기
	m_tIBDesc.ByteWidth = sizeof(UINT) * m_iIdxCount;	// GPU 에 생성할 버퍼 메모리 크기
	m_tIBDesc.Usage = D3D11_USAGE_DEFAULT;				// 수정 불가능 버퍼
	m_tIBDesc.CPUAccessFlags = 0;						// 수정 불가능 버퍼
	m_tIBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;		// Index Buffer 용도

	tSubDesc = {};
	tSubDesc.pSysMem = _IdxSysmem;						// 초기 데이터

	hr = DEVICE->CreateBuffer(&m_tIBDesc, &tSubDesc, &m_pIB);
}

void CMesh::UpdateData()
{	
	// Topology(위상구조) 설정
	CONTEXT->IASetPrimitiveTopology(m_eTopology);

	UINT iStride = sizeof(VTX);
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_pVB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::render()
{
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}

void CMesh::render_particle(UINT _iParticleCount)
{
	CONTEXT->DrawIndexedInstanced(m_iIdxCount, _iParticleCount, 0, 0, 0);
}
