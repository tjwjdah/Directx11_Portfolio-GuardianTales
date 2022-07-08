#pragma once

class CFSMScript;
class CState
{

private:
	CFSMScript* m_pFSM;
	wstring		m_strStateName;

private:
	void SetFSM(CFSMScript* _pFSM) { m_pFSM = _pFSM; }
	void SetStateName(const wstring& _strName) { m_strStateName = _strName; }
	
	virtual void awake() = 0;
	virtual void update() {};
	virtual void lateupdate() {};
	
	virtual void Exit() = 0;

public:
	CFSMScript* GetFSM() { return m_pFSM; }

public:
	
	CState();
	virtual ~CState();

	friend class CFSMScript;

};

