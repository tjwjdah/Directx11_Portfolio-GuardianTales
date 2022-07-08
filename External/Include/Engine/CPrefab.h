#pragma once
#include "CRes.h"

class CGameObject;

class CPrefab :
    public CRes
{
private:
    CGameObject*    m_pProtoObj;
    Vec2            m_OffSet;

public:
    CGameObject*    Instantiate();

public:
    CGameObject* GetGameObject() { return m_pProtoObj; }
    void         SetOffSet(Vec2 _OffSet) { m_OffSet = _OffSet; }
    Vec2         GetOffSet() { return m_OffSet; }
public:
    virtual void Save(const wstring& _strRelativePath);

private:
    virtual void Load(const wstring& _strFilePath);

public:
    CPrefab();
    CPrefab(CGameObject* _pProto);
    ~CPrefab();
};

