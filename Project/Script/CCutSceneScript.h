#pragma once
#include <Engine\CScript.h>
class CCutSceneScript :
    public CScript
{
private:
    float   m_fTime;
    
    Character m_CCharacter;
public:
    virtual void update();
    virtual void awake();
public:
 
    GET_SET(Character, CCharacter);
public:
    CLONE(CCutSceneScript);

public:
    CCutSceneScript();
    ~CCutSceneScript();
};

