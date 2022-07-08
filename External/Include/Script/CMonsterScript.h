#pragma once
#include <Engine\CScript.h>



class CPrefab;
class CObjState;
class CMonsterScript :
    public CScript
{


public:
    virtual void awake();
    virtual void update();
    
    bool        m_Hit;
    float       m_HitTime;

    float       m_DieTime;
    float       m_ChangeTime;
    bool        m_DieEffect;
    bool        m_DieCamera;

    bool        m_SoundPlay;
    CObjState* m_ObjState;
    Monster     m_mMonster;
public:
    GET_SET(bool, Hit);
    GET_SET(Monster, mMonster);
public:
    CLONE(CMonsterScript);

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);
public:
    CMonsterScript();
    ~CMonsterScript();
};
