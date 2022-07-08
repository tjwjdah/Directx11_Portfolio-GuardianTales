#pragma once
#include <Engine\CScript.h>

class CState;
class CObjState;
class CFSMScript :
	public CScript
{
private:
	map<wstring, CState*>	m_mapState;
	CGameObject* m_pGameObject;
	CState* m_pCurState;

public:
	virtual void awake();
	virtual void update();
	virtual void lateupdate();



	
	
public:
	void SetCGameObject(CGameObject* _GameObject) { m_pGameObject = _GameObject; }
	void AddState(wstring _strStateName, CState* _pState);
	CState* FindState(wstring _strStateName);
	void ChangeState(wstring _strNextStateName);
	CGameObject* GetGObj() { return m_pGameObject; }
	CObjState* GetObjStat();

public:
	CLONE(CFSMScript);
	CFSMScript();
	~CFSMScript();
};

