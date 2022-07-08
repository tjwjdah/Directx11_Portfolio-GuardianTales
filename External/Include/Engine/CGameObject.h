#pragma once
#include "CEntity.h"

class CComponent;
class CTransform;
class CMeshRender;
class CCollider2D;
class CAnimator2D;
class CCamera;
class CParticleSystem;
class CLight2D;
class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END];
    vector<CScript*>        m_vecScript;
    vector<CGameObject*>    m_vecChild;
    CGameObject*            m_pParentObj;
    int                     m_iLayerIdx;

    bool                    m_bDead;

public:
    void awake();
    void start();

    void update();
    void lateupdate();
    void finalupdate();


public:
    void AddComponent(CComponent* _pComponent);
       
    CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM];}
    CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
    CParticleSystem* ParticleSystem(){return (CParticleSystem*)m_arrCom[(UINT)COMPONENT_TYPE::PARTICLE];}
    CCamera* Camera() { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }
    CCollider2D* Collider2D() { return (CCollider2D*)m_arrCom[(UINT)COMPONENT_TYPE::COLLIDER2D]; }
    CLight2D* Light2D() { return (CLight2D*)m_arrCom[(UINT)COMPONENT_TYPE::LIGHT2D]; }
    CAnimator2D* Animator2D() { return (CAnimator2D*)m_arrCom[(UINT)COMPONENT_TYPE::ANIMATOR2D]; }
    CComponent* GetComponent(COMPONENT_TYPE _eType) {return m_arrCom[(UINT)_eType];}
    const vector<CScript*>& GetScripts() { return m_vecScript; }
    CScript* GetScript() { if (m_vecScript.empty()) return nullptr; return m_vecScript[0]; }
    CScript* GetScript(const wstring& _strName);
    CGameObject* GetParent() { return m_pParentObj; }
    const vector<CGameObject*>& GetChild() { return m_vecChild; }
    CGameObject* GetChild(const wstring& _strName);

    bool IsDead() { return m_bDead; }
    int GetLayerIndex() { return m_iLayerIdx; }
private:
   
    void SetLayerIndex(int _iIdx) { m_iLayerIdx = _iIdx; }

    // 부모 오브젝트와의 연결 해제
    void DisconnectWithParent(); 

    // 소속된 Layer 에 ParentObj 로 등록
    void RegisterAsParentObj();

    // 소속된 Layer 에서 부모로서 연결 해제    
    void ReleaseAsParentObj();

    // 자식 오브젝트 추가
    void AddChild(CGameObject* _pChildObj);

public:
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);

    CLONE(CGameObject);

public:
    CGameObject();
    CGameObject(const CGameObject& _origin);
    ~CGameObject();

    friend class CLayer;
    friend class CEventMgr;
};

