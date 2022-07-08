#pragma once
#include "CRes.h"

class CMesh :
    public CRes
{
private:  
    ComPtr<ID3D11Buffer>    m_pVB;
    D3D11_BUFFER_DESC       m_tVBDesc;
    UINT                    m_iVtxCount;

    ComPtr<ID3D11Buffer>    m_pIB;
    D3D11_BUFFER_DESC       m_tIBDesc;
    UINT                    m_iIdxCount;

    D3D_PRIMITIVE_TOPOLOGY  m_eTopology;

public:
    void SetTopology(D3D_PRIMITIVE_TOPOLOGY _eTopology) { m_eTopology = _eTopology; }

    void Create(VTX* _pVTXSysmem, UINT _iVtxCount, UINT* _IdxSysmem, UINT _iIdxCount);
    void UpdateData();
    void render();
    void render_particle(UINT _iParticleCount);

public:
    virtual void Save(const wstring& _strRelativePath) {}
    virtual void Load(const wstring& _strFilePath) {}

public:
    CMesh();
    ~CMesh();
};

