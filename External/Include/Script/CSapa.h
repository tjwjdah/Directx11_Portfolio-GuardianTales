#pragma once
#include <Engine\CScript.h>


enum class SapaState {
    IDLE,
    WALK,
    TELEPORT,
    ATTACKJINGAK,
    ATTACKBOBM,
    ATTACKORARUSH
};
class CObjState;
class CSapa :
    public CScript
{
private:

    SapaState   m_State;

    Vec2        m_vTargetDir;
    Vec2        m_vRushSetDir;
    Vec3        m_vTelpoPos;  //텔포할 위치 저장

    DIR         m_DIR;
    CDIR                m_eColliderDir;

    Pattern     m_Pattern;

    float       m_fDistance;
    float       m_fMaxTime;
    float       m_fTime;

    float       m_fSpeed;

    bool        m_AinmOn;


    int         m_BobmNum;

    Ptr<CPrefab>            m_TelPo;
    Ptr<CPrefab>            m_BobmStart;
    Ptr<CPrefab>            m_Bobm;
    Ptr<CPrefab>            m_Jin;
    Ptr<CPrefab>            m_Ora;
    CGameObject*            m_OraObj;
    CObjState* m_ObjState;
public:

    void StateChange();

    void IDLE();
    void WALK();
    void TELEPORT();
    void ATTACKJINGAK();
    void ATTACKBOBM();
    void ATTACKORARUSH();

    void SetDir();

public:
    virtual void update();
    virtual void awake();


public:
    virtual void OnCollisionEnter(CGameObject* _pOther);

    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
public:
    CLONE(CSapa);
    CSapa();
    ~CSapa();
};

