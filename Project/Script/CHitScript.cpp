#include "pch.h"
#include "CHitScript.h"
#include <Engine\CEventMgr.h>
#include <Engine\func.h>
#include "CPlayerScript.h"
#include "CObjState.h"

#include <Engine\CCamera.h>
#include <Engine\CScene.h>
#include <Engine\CSceneMgr.h>

#include "CTargetToAuto.h"
#include "CMonsterScript.h"
#include "CPlayerScript.h"
#include "CDamageFontScript.h"

CHitScript::CHitScript() :CScript((int)SCRIPT_TYPE::HITSCRIPT)
, m_Type(ObjType::None)
, m_iDamage(0)
, m_CCType(CC::NONE)
, m_CCValue(0)
, m_bHitDeleteOn(true)
, m_bDamageColEnter(true)
, m_fDamageTime(0.f)
, m_fTime(0.f)
, m_IsDead(false)
, m_Player(false)
, m_effect(nullptr)
{
}

CHitScript::~CHitScript()
{

}

void CHitScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (m_bDamageColEnter)
	{
		if (m_Type == ObjType::Player)
		{
			if (_pOther->GetLayerIndex() == 3)
			{
				if (m_Player)
				{
					CGameObject* Camera = CSceneMgr::GetInst()->GetCurScene()->FindObjectByName(L"Camera Object");
					Camera->Camera()->Hit();
				}
				CObjState* State = (CObjState*)_pOther->GetScript(L"CObjState");
				if (State != nullptr)
				{
					CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"DamageFont").Get()->Instantiate();
					CDamageFontScript* damage = (CDamageFontScript*)pObject->GetScript(L"CDamageFontScript");
					damage->SetDamageNum(m_iDamage);
					pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
					State->m_Hp = State->m_Hp - m_iDamage;
					
					tEvent even = {};
					even.eEvent = EVENT_TYPE::CREATE_OBJECT;
					even.lParam = (DWORD_PTR)pObject;
					//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
					even.wParam = (DWORD_PTR)30;
					CEventMgr::GetInst()->AddEvent(even);
					switch (m_CCType)
					{
					case CC::DOWN:
						State->m_CCDOWN += m_CCValue;
						break;
					case CC::AIRBORNE:
						State->m_CCAIRBORNE += m_CCValue;
						break;
					case CC::INJURE:
						State->m_CCINJURE += m_CCValue;
						break;
					case CC::NONE:
						break;

					}
				}
				if (m_bHitDeleteOn && !GetGameObject()->IsDead())
				{
					m_IsDead = true;
				}

				if (m_effect.Get() != nullptr)
				{
					CGameObject* pObject = m_effect->Instantiate();
					Vec3 Pos = Transform()->GetWorldPos();
					
					
					if (GetGameObject()->GetScript(L"CTargetToAuto"))
					{
						CTargetToAuto* Target = (CTargetToAuto*)GetGameObject()->GetScript(L"CTargetToAuto");
						Vec2 Dir =Target->GetTargeDir();
						Pos.x += Dir.x * 40.f;
						Pos.y += Dir.y * 40.f;
					}
					if (GetGameObject()->GetName() == L"MarinaAttack")
					{
						Vec2 Pos2;
						Pos2.x = _pOther->Transform()->GetLocalPos().x - Pos.x;
						Pos2.y = _pOther->Transform()->GetLocalPos().y - Pos.y;
						Pos.x += Pos2.x * 0.5f;
						Pos.y += Pos2.y * 0.5f;
					}
					if (GetGameObject()->GetName() == L"GaramSkill2")
					{
						
						Pos= _pOther->Transform()->GetLocalPos();
						
					}
					pObject->Transform()->SetLocalPos(Pos);
					tEvent even = {};
					even.eEvent = EVENT_TYPE::CREATE_OBJECT;
					even.lParam = (DWORD_PTR)pObject;
					//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
					even.wParam = (DWORD_PTR)30;
					CEventMgr::GetInst()->AddEvent(even);
				}

				if (_pOther->GetScript(L"CMonsterScript"))
				{
					CMonsterScript* Monster = (CMonsterScript*)_pOther->GetScript(L"CMonsterScript");
					Monster->SetHit(true);
				}

			}
			
		}
		else if (m_Type == ObjType::Monster)
		{
			if (_pOther->GetLayerIndex() == 1)
			{
				CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
				if (Player == nullptr)
					return;
				if (Player->GetAuto() == 0)
				{
					CObjState* State = (CObjState*)_pOther->GetScript(L"CObjState");
					if (State != nullptr)
					{
						CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"DamageFont").Get()->Instantiate();
						CDamageFontScript* damage = (CDamageFontScript*)pObject->GetScript(L"CDamageFontScript");
						damage->SetDamageNum(m_iDamage);
						damage->SetPlayer(false);
						pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
					
					State->m_Hp = State->m_Hp - m_iDamage;
					tEvent even = {};
					even.eEvent = EVENT_TYPE::CREATE_OBJECT;
					even.lParam = (DWORD_PTR)pObject;
					//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
					even.wParam = (DWORD_PTR)30;
					CEventMgr::GetInst()->AddEvent(even);
					switch (m_CCType)
						{
					case CC::DOWN:
						State->m_CCDOWN += m_CCValue;
						break;
					case CC::AIRBORNE:
						State->m_CCAIRBORNE += m_CCValue;
						break;
					case CC::INJURE:
						State->m_CCINJURE += m_CCValue;
						break;
					case CC::NONE:
						break;
						}
					}	
					if (m_bHitDeleteOn && !GetGameObject()->IsDead())
					{
						m_IsDead = true;
					}
					if (m_effect.Get() != nullptr)
					{
						CGameObject* pObject = m_effect->Instantiate();
						Vec3 Pos = _pOther->Transform()->GetWorldPos();

						pObject->Transform()->SetLocalPos(Pos);
						tEvent even = {};
						even.eEvent = EVENT_TYPE::CREATE_OBJECT;
						even.lParam = (DWORD_PTR)pObject;
						//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
						even.wParam = (DWORD_PTR)30;
						CEventMgr::GetInst()->AddEvent(even);
					}
					if (_pOther->GetScript(L"CPlayerScript"))
					{
						CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
						Player->SetHit(true);
					}
					
				}
				
			}
			
		}
		
	}

}

void CHitScript::OnCollisionExit(CGameObject* _pOther)
{
	
}

void CHitScript::OnCollision(CGameObject* _pOther)
{
	if (!m_bDamageColEnter)
	{
		if (m_Type == ObjType::Player)
		{
			if (_pOther->GetLayerIndex() == 3)
			{
				CObjState* State = (CObjState*)_pOther->GetScript(L"CObjState");
				if (State != nullptr)
				{
					m_fTime += fDT;


					if (m_fTime > m_fDamageTime) {

						CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"DamageFont").Get()->Instantiate();
						CDamageFontScript* damage = (CDamageFontScript*)pObject->GetScript(L"CDamageFontScript");
						damage->SetDamageNum(m_iDamage);
						pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
						State->m_Hp = State->m_Hp - m_iDamage;

						tEvent even = {};
						even.eEvent = EVENT_TYPE::CREATE_OBJECT;
						even.lParam = (DWORD_PTR)pObject;
						//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
						even.wParam = (DWORD_PTR)30;
						CEventMgr::GetInst()->AddEvent(even);

						
						switch (m_CCType)
						{
						case CC::DOWN:
							State->m_CCDOWN += m_CCValue;
							break;
						case CC::AIRBORNE:
							State->m_CCAIRBORNE += m_CCValue;
							break;
						case CC::INJURE:
							State->m_CCINJURE += m_CCValue;
							break;
						case CC::NONE:
							break;
							

							
						}
						m_fTime = 0;
						if (_pOther->GetScript(L"CMonsterScript"))
						{
							CMonsterScript* Monster = (CMonsterScript*)_pOther->GetScript(L"CMonsterScript");
							Monster->SetHit(true);
						}
					}

				}
			
			}
		}
		else if (m_Type == ObjType::Monster)
		{
			if (_pOther->GetLayerIndex() == 1)
			{
				CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
				if (Player == nullptr)
					return;
				if (Player->GetAuto() == 0)
				{
					CObjState* State = (CObjState*)_pOther->GetScript(L"CObjState");
					if (State != nullptr)
					{
						m_fTime += fDT;
						if (m_fTime > m_fDamageTime) {

							CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"DamageFont").Get()->Instantiate();
							CDamageFontScript* damage = (CDamageFontScript*)pObject->GetScript(L"CDamageFontScript");
							damage->SetDamageNum(m_iDamage);
							damage->SetPlayer(false);
							pObject->Transform()->SetLocalPos(Transform()->GetWorldPos());
							State->m_Hp = State->m_Hp - m_iDamage;

							tEvent even = {};
							even.eEvent = EVENT_TYPE::CREATE_OBJECT;
							even.lParam = (DWORD_PTR)pObject;
							//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
							even.wParam = (DWORD_PTR)30;
							CEventMgr::GetInst()->AddEvent(even);
						
							switch (m_CCType)
							{
							case CC::DOWN:
								State->m_CCDOWN += m_CCValue;
								break;
							case CC::AIRBORNE:
								State->m_CCAIRBORNE += m_CCValue;
								break;
							case CC::INJURE:
								State->m_CCINJURE += m_CCValue;
								break;
							case CC::NONE:
								break;


							}
							m_fTime = 0;

							if (m_effect.Get() != nullptr)
							{
								CGameObject* pObject = m_effect->Instantiate();
								Vec3 Pos = _pOther->Transform()->GetWorldPos();

								pObject->Transform()->SetLocalPos(Pos);
								tEvent even = {};
								even.eEvent = EVENT_TYPE::CREATE_OBJECT;
								even.lParam = (DWORD_PTR)pObject;
								//even.wParam = (DWORD_PTR)GetGameObject()->GetLayerIndex();
								even.wParam = (DWORD_PTR)30;
								CEventMgr::GetInst()->AddEvent(even);
							}
							if (_pOther->GetScript(L"CPlayerScript"))
							{
							CPlayerScript* Player = (CPlayerScript*)_pOther->GetScript(L"CPlayerScript");
							Player->SetHit(true);
							}

						}
					}
				}
			}
		}

	}

}

void CHitScript::SaveToScene(FILE* _pFile)
{
	CScript::SaveToScene(_pFile);
	fwrite(&m_Type, sizeof(ObjType), 1, _pFile);
	fwrite(&m_iDamage, sizeof(int), 1, _pFile);
	fwrite(&m_CCType, sizeof(CC), 1, _pFile);
	fwrite(&m_CCValue, sizeof(int), 1, _pFile);
	fwrite(&m_bHitDeleteOn, sizeof(bool), 1, _pFile);
	fwrite(&m_bDamageColEnter, sizeof(bool), 1, _pFile);
	fwrite(&m_fDamageTime, sizeof(float), 1, _pFile);
	
}

void CHitScript::LoadFromScene(FILE* _pFile)
{
	CScript::LoadFromScene(_pFile);
	fread(&m_Type, sizeof(float), 1, _pFile);
	fread(&m_iDamage, sizeof(int), 1, _pFile);
	fread(&m_CCType, sizeof(CC), 1, _pFile);
	fread(&m_CCValue, sizeof(int), 1, _pFile);
	fread(&m_bHitDeleteOn, sizeof(bool), 1, _pFile);
	fread(&m_bDamageColEnter, sizeof(bool), 1, _pFile);
	fread(&m_fDamageTime, sizeof(float), 1, _pFile);
}

void CHitScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	if (m_IsDead)
	{

			tEvent _temp = {};
			_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
			_temp.lParam = (DWORD_PTR)GetGameObject();
			CEventMgr::GetInst()->AddEvent(_temp);
	}
}
