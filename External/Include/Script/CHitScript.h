#pragma once
#include <Engine\CScript.h>


enum class ObjType {
    Player,
    Monster,
    None
}; //기술쓴 대상이 누군지






//상태이상 종류
enum class CC {
    DOWN,
    AIRBORNE,
    INJURE,
    NONE
};
class CHitScript:
	public CScript
{
private:
    ObjType   m_Type;
    int       m_iDamage; //데미지
    CC        m_CCType;  //상태이상 타입
    int       m_CCValue; //상태이상 수치

    bool      m_bHitDeleteOn; //충돌되면 사라지는지 아닌지
    bool      m_bDamageColEnter; //true 엔터일때 데미지 false면 on일때 데미지
    float     m_fDamageTime;  //몇초마다 데미지 입힐지
    float     m_fTime;



    bool      m_IsDead;
 


    bool      m_Player; //내가쏜건지


    Ptr<CPrefab>             m_effect;  //평타




public:
    virtual void update();

public:
    GET_SET(int, iDamage);
    GET_SET(int, CCValue);
    GET_SET(ObjType, Type);
    GET_SET(CC, CCType);
    GET_SET(bool, bHitDeleteOn);
    GET_SET(bool, bDamageColEnter);
    GET_SET(float, fDamageTime);
    GET_SET(bool, Player);


    void Seteffect(Ptr<CPrefab> _Prefab) { m_effect = _Prefab; }

public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
    

    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

public:
    CLONE(CHitScript);
    CHitScript();
    ~CHitScript();


};

