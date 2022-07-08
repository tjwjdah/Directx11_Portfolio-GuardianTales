#pragma once
#include <Engine\CScript.h>

//상태이상

class CObjState :
    public CScript
{
private:
    int         m_MaxHp;
    int         m_Hp;
    int         m_ATK;

    int         m_CCDOWN;
    int         m_CCAIRBORNE;
    int         m_CCINJURE;
    float		m_TargetRange; // 인식범위
    
    float                m_CoolTime;
    float                m_CoolTimeMax;
    float                m_CoolTime2;
    float                m_CoolTimeMax2;
public:
   
    GET_SET(int, MaxHp);
    GET_SET(int, Hp);
    GET_SET(int, ATK);
    GET_SET(float, TargetRange);
    GET_SET(int, CCDOWN);
    GET_SET(int, CCAIRBORNE);
    GET_SET(int, CCINJURE);

    GET_SET(float, CoolTime);
    GET_SET(float, CoolTimeMax);
    GET_SET(float, CoolTime2);
    GET_SET(float, CoolTimeMax2);
public:
    virtual void update() {};
    virtual void awake();
public:
    CLONE(CObjState);
    CObjState();
    ~CObjState();
    
    friend class CHitScript;
    friend class CPlayerScript;
};

