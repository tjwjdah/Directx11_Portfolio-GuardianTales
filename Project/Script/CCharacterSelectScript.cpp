#include "pch.h"
#include "CCharacterSelectScript.h"

#include <Engine\CPrefab.h>
#include <Engine\CResMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CTransform.h>
#include <Engine\CEventMgr.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CCore.h>
CCharacterSelectScript::CCharacterSelectScript():CScript((int)SCRIPT_TYPE::CHARACTERSELECTSCRIPT)
, Player{ (nullptr),(nullptr),(nullptr),(nullptr) }
, m_DrapObj(nullptr)
, m_ObjPreDrapPos(Vec3(0.f,0.f,0.f))
, m_DrapObjNum(-1)
{
	m_Res = CCore::GetInst()->GetWndResolution();
}

CCharacterSelectScript::~CCharacterSelectScript()
{
}

void CCharacterSelectScript::update()
{
	Vec3 pos = Transform()->GetLocalPos();
	POINT mospos = CKeyMgr::GetInst()->GetMousePos();

	mospos.x = mospos.x - m_Res.x / 2;
	mospos.y = -mospos.y + m_Res.y / 2;
	if (KEY_TAP(KEY_TYPE::LBTN))
	{
		if (mospos.y<220.f && mospos.y>-360.f)
		{
			if (mospos.x >= -640.f && mospos.x < -320.f)
			{
				m_DrapObj = Player[0];
				m_DrapObjNum = 0;
			}
			else if (mospos.x >= -320.f && mospos.x < 0.f)
			{
				m_DrapObj = Player[1];
				m_DrapObjNum = 1;
			}
			else if (mospos.x >= 0.f && mospos.x < 320.f)
			{
				m_DrapObj = Player[2];
				m_DrapObjNum = 2;
			}
			else if (mospos.x >= 320.f && mospos.x < 640.f)
			{
				m_DrapObj = Player[3];
				m_DrapObjNum = 3;
			}
			if(m_DrapObj!=nullptr)
				m_ObjPreDrapPos = m_DrapObj->Transform()->GetLocalPos();
		}
	}
	else if (KEY_HOLD(KEY_TYPE::LBTN))
	{
		if(m_DrapObj!=nullptr){
			m_DrapObj->Transform()->SetLocalPosX(mospos.x);
			m_DrapObj->Transform()->SetLocalPosY(mospos.y);
		}
	}
	else if (KEY_AWAY(KEY_TYPE::LBTN))
	{

		if (m_DrapObj != nullptr) {
			if (mospos.y >= 220.f)
			{
				m_DrapObj->Transform()->SetLocalPos(m_ObjPreDrapPos);
				m_DrapObjNum = -1;
			}
			else if (mospos.x >= -640.f && mospos.x < -320.f)
			{
				m_DrapObj->Transform()->SetLocalPosX(-480.f);
				m_DrapObj->Transform()->SetLocalPosY(-110.f);
				if (m_DrapObjNum != 0)
				{
					
					CGameObject* temp= Player[0];
					Player[0] = m_DrapObj;
					Player[m_DrapObjNum] = temp;
					temp->Transform()->SetLocalPosX(-480.f + (320 * m_DrapObjNum));
					CSceneMgr::GetInst()->PlayerListChange(m_DrapObjNum, 0);
					m_DrapObjNum = -1;

					
				}

			}
			else if (mospos.x >= -320.f && mospos.x < 0.f)
			{
				m_DrapObj->Transform()->SetLocalPosX(-160.f);
				m_DrapObj->Transform()->SetLocalPosY(-110.f);
				if (m_DrapObjNum != 1)
				{

					CGameObject* temp = Player[1];
					Player[1] = m_DrapObj;
					Player[m_DrapObjNum] = temp;
					temp->Transform()->SetLocalPosX(-480.f + (320 * m_DrapObjNum));
					CSceneMgr::GetInst()->PlayerListChange(m_DrapObjNum, 1);
					m_DrapObjNum = -1;
				}

			}
			else if (mospos.x >= 0.f && mospos.x < 320.f)
			{
				m_DrapObj->Transform()->SetLocalPosX(160.f);
				m_DrapObj->Transform()->SetLocalPosY(-110.f);
				if (m_DrapObjNum != 2)
				{

					CGameObject* temp = Player[2];
					Player[2] = m_DrapObj;
					Player[m_DrapObjNum] = temp;
					temp->Transform()->SetLocalPosX(-480.f + (320 * m_DrapObjNum));
					CSceneMgr::GetInst()->PlayerListChange(m_DrapObjNum, 2);
					m_DrapObjNum = -1;
				}
			}
			else if (mospos.x >= 320.f && mospos.x < 640.f)
			{
				m_DrapObj->Transform()->SetLocalPosX(480.f);
				m_DrapObj->Transform()->SetLocalPosY(-110.f);
				if (m_DrapObjNum != 3)
				{

					CGameObject* temp = Player[3];
					Player[3] = m_DrapObj;
					Player[m_DrapObjNum] = temp;
					temp->Transform()->SetLocalPosX(-480.f + (320 * m_DrapObjNum));
					CSceneMgr::GetInst()->PlayerListChange(m_DrapObjNum, 3);
					m_DrapObjNum = -1;
				}
			}
			m_DrapObj = nullptr;
		}
	}

}

void CCharacterSelectScript::awake()
{

	for (int i = 0; i < 4; i++)
	{
		Character ch= CSceneMgr::GetInst()->GetPartyListNum(i);
		switch (ch)
		{
		case Character::NARI:
			Player[i] = CResMgr::GetInst()->FindRes<CPrefab>(L"Select_Nari").Get()->Instantiate();
			break;
		case Character::MARINA:
			Player[i] = CResMgr::GetInst()->FindRes<CPrefab>(L"Select_Marina").Get()->Instantiate();
			break;
		case Character::GARAM:
			Player[i] = CResMgr::GetInst()->FindRes<CPrefab>(L"Select_Garam").Get()->Instantiate();
			break;
		case Character::EVA:
			Player[i] = CResMgr::GetInst()->FindRes<CPrefab>(L"Select_Eva").Get()->Instantiate();
			break;
		}
		Player[i]->Transform()->SetLocalPosX(-480.f + (320*i));
		Player[i]->Transform()->SetLocalPosZ(10.f);
		tEvent even = {};
		even.eEvent = EVENT_TYPE::CREATE_OBJECT;
		even.lParam = (DWORD_PTR)Player[i];
		//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
		even.wParam = (DWORD_PTR)10;
		CEventMgr::GetInst()->AddEvent(even);
	}
	
}
