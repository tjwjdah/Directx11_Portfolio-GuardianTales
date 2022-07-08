#pragma once
#include <Engine\CScript.h>

enum class EventType {
    TriggerOn,
    TriggerOnOff
};
class CObjEventScript :
    public CScript
{
private:
    vector<CObjEventScript*>   ChildTrigger;
    bool                b_TriggerOn;
    EventType           E_EvnetType;

    CObjEventScript* m_pParentObj;
public:
    virtual void awake();
    virtual void update();

public:
    bool GetTrigger() { return b_TriggerOn; }
    void SetTrigger(bool _Trigger) { b_TriggerOn = _Trigger; }
    void SetEventType(EventType _Type) { E_EvnetType = _Type; }
    EventType GetEventType() { return E_EvnetType; }
    void PushEvnetChild(CObjEventScript* _Event);
    void PushEvnetChild(CGameObject* _Event);
    vector<CObjEventScript*>& GetChildeTrigger() { return ChildTrigger; }
    void SetParent(CObjEventScript* _Parent) { m_pParentObj = _Parent; }
    void ReleaseEvent(int _num);
public:
    virtual void OnCollisionEnter(CGameObject* _pOther);


public:
    CLONE(CObjEventScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CObjEventScript();
    ~CObjEventScript();
};