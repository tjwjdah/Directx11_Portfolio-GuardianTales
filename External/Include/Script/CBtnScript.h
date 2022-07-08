#pragma once
#include <Engine\CScript.h>

class CScene;
class CBtnScript :
    public CScript
{
private:
    POINT m_Res;
    float m_width;
    float m_height;
    
    wstring m_SName;
    bool    m_PlayerAdd;

public:
    

public:
    void SetSName(const wstring& _Name) {
        m_SName = _Name;
    }
    GET_SET(bool, PlayerAdd);
public:
    virtual void awake();
    virtual void update();

    void Size(Vec2 _Size) { m_width = _Size.x;
    m_height = _Size.y;
    }
    

public:
    CLONE(CBtnScript);

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
public:
    CBtnScript();
    ~CBtnScript();
};

