#pragma once
#include <Engine\CScript.h>

class CStructuredBuffer;
class CTexture;
class CDamageFontScript :
    public CScript
{
private:
    vector<tDamageFont>           m_Damage;
    tDamageFontShared             m_DamageShared;
    CStructuredBuffer*      m_DamageBuffer;
    CStructuredBuffer*      m_TSharedBuffer;

    int                   m_Damage_x;
    int                   m_Damage_y;
    float                 m_DamageUv_x;
    float                 m_DamageUv_y;

    int                  m_DamageSize;

    bool                m_Player;


    float               m_Time;

    int                m_iDamage;

public:
    void SetDamageNum(int _Damage);
    void SetDamage(int _x, int _y, int index);
    //void SetTileTexture(CTexture* _Tex) { m_TileTexture = _Tex; }
    int GetDamageX() { return m_Damage_x; }
    int GetDamageY() { return m_Damage_y; }
    int GetDamageSIze() { return m_DamageSize; }
    float GetDamageUvX() { return m_DamageUv_x; }
    float GetDamageUvY() { return m_DamageUv_y; }

    GET_SET(bool, Player);
public:
    virtual void awake();
    virtual void update();
    virtual void render();

public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CLONE(CDamageFontScript);
    CDamageFontScript();
    CDamageFontScript(const CDamageFontScript& _origin);
    ~CDamageFontScript();

};

