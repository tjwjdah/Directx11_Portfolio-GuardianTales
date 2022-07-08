#include "pch.h"
#include "CMonsterScript.h"

#include <Engine/CCore.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>

#include <Engine\CTransform.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\CCollider2D.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CAnimation2D.h>
#include <Engine\CEventMgr.h>
#include <Engine\CCamera.h>

#include "CPlayerScript.h"
#include "CObjEventScriptMgr.h"
#include "CObjState.h"

CMonsterScript::CMonsterScript()
	: CScript((int)SCRIPT_TYPE::MONSTERSCRIPT)
	, m_Hit(false)
	, m_HitTime(0.f)
	, m_mMonster(Monster::None)
	, m_ObjState(nullptr)
	, m_DieTime(1.f)
	, m_DieEffect(false)
	, m_DieCamera(false)
	, m_ChangeTime(0.f)
	, m_SoundPlay(false)
{

}

CMonsterScript::~CMonsterScript() {}

void CMonsterScript::awake()
{
	m_ObjState = (CObjState*)GetGameObject()->GetScript(L"CObjState");
}

void CMonsterScript::update()
{
	if (GetGameObject()->IsDead())
		return;
	
	if (m_ObjState->GetHp() > 0)
	{
		if (m_Hit)
		{
			m_HitTime += fDT;
			int a = 1;
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a);
			if (m_HitTime > 0.1)
			{
				m_Hit = false;
				m_HitTime = 0;
			}
		}
		else
		{
			int a = 0;

			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a);
		}
	}
	else
	{
		if (!m_DieCamera)
		{
			CGameObject* pObject2 = CSceneMgr::GetInst()->GetCurScene()->FindObjectByName(L"Camera Object");
			CCamera* Light = pObject2->Camera();
			Light->MonsterDie(Vec2(Transform()->GetLocalPos().x, Transform()->GetLocalPos().y));
			m_DieCamera = true;
		}
		if (!m_DieEffect && m_DieTime>3.f)
		{
			CGameObject* pObject ;
			switch (m_mMonster)
			{
			case Monster::SAPA:
			{
				pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"SapaDie").Get()->Instantiate();
				pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
				tEvent even = {};
				even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				even.lParam = (DWORD_PTR)pObject;
				even.wParam = (DWORD_PTR)30;
				CEventMgr::GetInst()->AddEvent(even);
			}
				break;
			case Monster::BUG:
			{
				pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"BugDie").Get()->Instantiate();
				pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
				tEvent even = {};
				even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				even.lParam = (DWORD_PTR)pObject;
				even.wParam = (DWORD_PTR)30;
				CEventMgr::GetInst()->AddEvent(even);
			}
				break;
			case Monster::MINO:
			{
				pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"MinoDie").Get()->Instantiate();
				pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
				tEvent even = {};
				even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				even.lParam = (DWORD_PTR)pObject;
				even.wParam = (DWORD_PTR)30;
				CEventMgr::GetInst()->AddEvent(even);
			}
				break;
			case Monster::INVADER:
			{
				pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"InveDie").Get()->Instantiate();
				pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
				tEvent even = {};
				even.eEvent = EVENT_TYPE::CREATE_OBJECT;
				even.lParam = (DWORD_PTR)pObject;
				even.wParam = (DWORD_PTR)30;
				CEventMgr::GetInst()->AddEvent(even);
			}
				break;
			
			}
			
			
			
			m_DieEffect = true;
		}
		if (m_DieTime <= 4.5f)
		{
			m_DieTime += fDT;
			int a = 3;
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a);
			MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::FLOAT_0, &m_DieTime);

		}
		else
		{
			Transform()->SetLocalScaleX(0.f);
			m_ChangeTime += fDT;
			if (!m_SoundPlay)
			{
				m_SoundPlay = true;
				Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_end");  //*********
				pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
			}
			if (m_ChangeTime > 2.f)
			{
				int a = 0;
				MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a);
				float n = 1.f;
				MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::FLOAT_0, &m_DieTime);
				m_ChangeTime = 0.f;
				CScene* Scene = new CScene;
				wstring strFilePath = CPathMgr::GetResPath();
				const wstring& Name = L"scene\\BossSelete.scene";
				strFilePath += Name;
				FILE* pFile = nullptr;
				HRESULT hr = _wfopen_s(&pFile, strFilePath.c_str(), L"rb");

				if (nullptr == pFile)
				{
					MessageBox(nullptr, L"Scene Load Failed", L"Error", MB_OK);
					return;
				}
				Scene->LoadFromScene(pFile);
				//Scene->awake();
				//Scene->start();

				CObjEventScriptMgr::GetInst()->LoadFromScene(Scene, pFile);
				fclose(pFile);

				
				CSceneMgr::GetInst()->ChangeScene(Scene);
			}

		}
	}
	
}





void CMonsterScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
	
}

void CMonsterScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
	

}