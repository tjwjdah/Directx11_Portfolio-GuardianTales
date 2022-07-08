#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"

class CMeshRender :
    public CComponent
{
private:
    Ptr<CMesh>      m_pMesh;
    Ptr<CMaterial>  m_pMtrl;
    Ptr<CMaterial>  m_pSharedMtrl;

public:
    virtual void update();
    virtual void finalupdate();

    void render();

public:
    Ptr<CMesh> GetMesh() { return m_pMesh; }
    void SetMesh(Ptr<CMesh> _pMesh) { m_pMesh = _pMesh; }
    void SetMaterial(Ptr<CMaterial> _pMtlr) { m_pMtrl = _pMtlr; }

    Ptr<CMaterial> GetSharedMaterial() { return m_pMtrl; }
    Ptr<CMaterial> GetCloneMaterial();

    void ReturnSharedMaterial()
    {
        assert(m_pSharedMtrl.Get());
        m_pMtrl = m_pSharedMtrl;
        m_pSharedMtrl = nullptr;
    }


public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
    CLONE(CMeshRender);

public:
    CMeshRender();
    ~CMeshRender();
};

