#include "pch.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CLayer.h"
#include "CEventMgr.h"
#include "CGameObject.h"
#include "CScript.h"


CSceneMgr::CSceneMgr()
	: m_pCurScene(nullptr)
	, m_PartyList{ Character::MARINA,Character::NARI,Character::GARAM,Character::EVA, }
	, Sceneawake(false)
	, m_ColShow(true)
{
}

CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);
}

void CSceneMgr::init()
{
	m_pCurScene = new CScene;
}

void CSceneMgr::progress()
{
	
	if (m_pCurScene->GetState() == SCENE_STATE::PLAY)
	{
		if (Sceneawake)
		{
			m_pCurScene->awake();
			m_pCurScene->start();
			Sceneawake = false;
		}
		m_pCurScene->update();
		m_pCurScene->lateupdate();
	}
	

	if (KEY_TAP(KEY_TYPE::ENTER))
	{
		if (m_ColShow)
			m_ColShow = false;
		else
			m_ColShow = true;
	}

	m_pCurScene->finalupdate();
}

CGameObject* CSceneMgr::FindPlayer(int _num)
{
	const vector<CGameObject*>& Player = m_pCurScene->GetLayer(1)->GetParentObj();
	
	if((size_t)_num >= Player.size())
		return nullptr;

	if (Player[(size_t)_num] == nullptr)
		return nullptr;

	if(Player[(size_t)_num]->GetScript(L"CPlayerScript"))
		return Player[(size_t)_num];
	else
		return nullptr;
}

CGameObject* CSceneMgr::FindObjectByName(const wstring& _strName)
{
	assert(m_pCurScene);

	return m_pCurScene->FindObjectByName(_strName);
}

void CSceneMgr::ChangeScene(CScene* _pNextScene)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)m_pCurScene;
	evn.wParam = (DWORD_PTR)_pNextScene;

	CEventMgr::GetInst()->AddEvent(evn);
}

void CSceneMgr::PlayerListChange(int _Num1, int _Num2)
{
	//1번을 선택해서 2번으로 바꿈 ㅇ
	Character temp = m_PartyList[_Num2];

	m_PartyList[_Num2] = m_PartyList[_Num1];
	m_PartyList[_Num1] = temp;
}
