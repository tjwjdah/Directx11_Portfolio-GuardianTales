#include "pch.h"
#include "CFSMScript.h"
#include "CState.h"

#include <Engine\CGameObject.h>
#include <Engine\CScript.h>

#include <Script\CObjState.h>



CFSMScript::CFSMScript():CScript((int)SCRIPT_TYPE::FSMSCRIPT)
, m_pGameObject(nullptr)
, m_pCurState(nullptr)
{
}

CFSMScript::~CFSMScript()
{
	for (const auto& pair : m_mapState)
	{
		delete pair.second;
	}
}

void CFSMScript::awake()
{
	if (nullptr != m_pCurState)
		m_pCurState->awake();
}

void CFSMScript::update()
{
	if (nullptr != m_pCurState)
		m_pCurState->update();
}

void CFSMScript::lateupdate()
{
	if (nullptr != m_pCurState)
		m_pCurState->update();
}

void CFSMScript::AddState(wstring _strStateName, CState* _pState)
{
	CState* pState = FindState(_strStateName);
	assert(nullptr == pState);

	_pState->SetStateName(_strStateName);
	_pState->SetFSM(this);
	m_mapState.insert(make_pair(_strStateName, _pState));
}

CState* CFSMScript::FindState(wstring _strStateName)
{
	map<wstring, CState*>::iterator iter = m_mapState.find(_strStateName);

	if (m_mapState.end() == iter)
	{
		return nullptr;
	}

	return iter->second;
}

void CFSMScript::ChangeState(wstring _strNextStateName)
{
	CState* pNextState = FindState(_strNextStateName);
	assert(pNextState);

	if (nullptr != m_pCurState)
		m_pCurState->Exit();

	m_pCurState = pNextState;

	m_pCurState->awake();
}

CObjState* CFSMScript::GetObjStat()
{
	if (m_pGameObject->GetScript(L"CObjState") != nullptr)
	{
		CObjState* ObjState = (CObjState*)m_pGameObject->GetScript(L"CObjState");
		return ObjState;
	}
	else
	{
		return nullptr;
	}
		
}
