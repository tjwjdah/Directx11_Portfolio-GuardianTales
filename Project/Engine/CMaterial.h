#pragma once
#include "CRes.h"

#include "CGraphicsShader.h"
#include "CTexture.h"

class CMaterial :
    public CRes
{
private:
    tMtrlInfo               m_tInfo;
    Ptr<CTexture>           m_arrTex[(UINT)SHADER_PARAM::TEX_END - (UINT)SHADER_PARAM::TEX_0];

    Ptr<CGraphicsShader>    m_pShader;
    bool                    m_bDefault;

public:
    void SetShader(Ptr<CGraphicsShader> _pShader) { m_pShader = _pShader; }
    Ptr<CGraphicsShader> GetShader() { return m_pShader; }
    void SetData(SHADER_PARAM _eType, const void* _pData);
    void* GetData(SHADER_PARAM _eType);
    void UpdateData();
    void Clear();

public:
    virtual CMaterial* Clone();

public:
    virtual void Save(const wstring& _strRelativePath);
    virtual void Load(const wstring& _strFilePath);

public:
    CMaterial();
    CMaterial(const CMaterial& _origin);
    ~CMaterial();

    friend class CResMgr;
};

