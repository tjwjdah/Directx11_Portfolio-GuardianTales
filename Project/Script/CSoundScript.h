#pragma once
#include <Engine\CScript.h>

enum class BGM_NAME
{
    BOSSMAIN,
    CHANGECHAR,
    DUNGEON,
    BOSS,
    START,
    NONE
};

class CSoundScript :
    public CScript
{
private:
    BGM_NAME m_eName;
    Ptr<CSound> m_pSound;

    UINT m_isave;
    bool m_bplay;


public:
    void SetBgmName(BGM_NAME _name) { m_eName = _name; }


public:
    virtual void awake();
    virtual void update();

public:
    CLONE(CSoundScript);

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
public:
    CSoundScript();
    ~CSoundScript();
};