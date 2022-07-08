#include "pch.h"
#include "CPlayerScript.h"

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

#include "CBreakableStoneScript.h"
#include "CPushStoneScript.h"

#include "CFireBowlScript.h"
#include "CBombFlowerScript.h"
#include "CObjState.h"

void CPlayerScript::AutoPlayer()
{

	if (m_Target != nullptr)
	{
		
		Vec2 TargetVec;
		TargetVec.x = m_Target->Transform()->GetWorldPos().x - Transform()->GetWorldPos().x;
		TargetVec.y = m_Target->Transform()->GetWorldPos().y - Transform()->GetWorldPos().y;
		float m_fDistance = TargetVec.Length();

		TargetVec.Normalize();
		if (m_ePrevState == PLAYER_STATE::ATTACK && m_ePrevState != m_eCurState)
		{
			AttackEndComboState();
		}
		m_ePrevState = m_eCurState;
		m_PreAinmDir = m_AnimDir;
		if (TargetVec.y >= 0)
		{
			if (TargetVec.y > fabs(TargetVec.x)) {
				if (m_AnimDir != DIR::UP)
				{
					m_ftime += fDT;
					if (m_ftime > 0.3f)
					{
						m_AnimDir = DIR::UP;
						m_ftime = 0;
					}

				}

			}
			else
			{
				if (TargetVec.x > 0)
				{

					if (m_AnimDir != DIR::RIGHT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::RIGHT;
							m_ftime = 0;
						}

					}
				}
				else
				{

					if (m_AnimDir != DIR::LEFT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::LEFT;
							m_ftime = 0;
						}

					}

				}
			}
		}
		else
		{
			if (fabs(TargetVec.y) > fabs(TargetVec.x)) {

				if (m_AnimDir != DIR::DOWN)
				{
					m_ftime += fDT;
					if (m_ftime > 0.3f)
					{
						m_AnimDir = DIR::DOWN;
						m_ftime = 0;
					}

				}

			}
			else
			{
				if (TargetVec.x > 0)
				{
					if (m_AnimDir != DIR::RIGHT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::RIGHT;
							m_ftime = 0;
						}

					}

				}
				else
				{

					if (m_AnimDir != DIR::LEFT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::LEFT;
							m_ftime = 0;
						}

					}

				}
			}
		}




		if (Animator2D()->GetCurAnim()->IsFinish() && m_eCurState == PLAYER_STATE::ATTACK)
		{
			if (m_CurrentCombo == m_MaxCombo)
			{
				AttackEndComboState();
			}
			else if (m_IsComboInputOn)
			{
				AttackStartComboState();
			}
			else if (!m_IsComboInputOn)
			{
				m_fAtime += fDT;
				if (m_fMaxtime < m_fAtime)
				{
					AttackEndComboState();
					m_fAtime = 0.f;
				}
			}

		}
		float d = m_State->GetTargetRange();
		if (m_fDistance <= m_State->GetTargetRange())
		{

				m_ftime += fDT;
				if (m_ftime > 0.3f)
				{
					m_eCurState = PLAYER_STATE::ATTACK;
					Attacking();
					m_ftime = 0;
				}

		}
		else
		{
			if (m_eCurState != PLAYER_STATE::RUN)
			{
				m_ftime += fDT;
				if (m_ftime > 0.3f)
				{
					m_eCurState = PLAYER_STATE::RUN;
					m_ftime = 0;
				}

			}

			
		}
	}
	else
	{
		CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(m_iPartyNum-1);
		Vec2 m_vTargetDir;
		m_vTargetDir.x = pPlayer->Transform()->GetWorldPos().x - Transform()->GetWorldPos().x;
		m_vTargetDir.y = pPlayer->Transform()->GetWorldPos().y - Transform()->GetWorldPos().y;
		float m_fDistance = m_vTargetDir.Length();
		m_vTargetDir.Normalize();



		m_ePrevState = m_eCurState;
		m_PreAinmDir = m_AnimDir;
		


		if (m_vTargetDir.y >= 0)
		{
			if (m_vTargetDir.y > fabs(m_vTargetDir.x)) {
				if (m_AnimDir != DIR::UP)
				{
					m_ftime += fDT;
					if (m_ftime > 0.3f)
					{
						m_AnimDir = DIR::UP;
						m_ftime = 0;
					}
					
				}
						
			}
			else
			{
				if (m_vTargetDir.x > 0)
				{
					
					if (m_AnimDir != DIR::RIGHT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::RIGHT;
							m_ftime = 0;
						}

					}
				}
				else
				{
					
					if (m_AnimDir != DIR::LEFT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::LEFT;
							m_ftime = 0;
						}

					}
							
				}
			}
		}
		else
		{
			if (fabs(m_vTargetDir.y) > fabs(m_vTargetDir.x)) {
				
				if (m_AnimDir != DIR::DOWN)
				{
					m_ftime += fDT;
					if (m_ftime > 0.3f)
					{
						m_AnimDir = DIR::DOWN;
						m_ftime = 0;
					}

				}
				
			}
			else
			{
				if (m_vTargetDir.x > 0)
				{
					if (m_AnimDir != DIR::RIGHT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::RIGHT;
							m_ftime = 0;
						}

					}
			
				}
				else
				{
				
					if (m_AnimDir != DIR::LEFT)
					{
						m_ftime += fDT;
						if (m_ftime > 0.3f)
						{
							m_AnimDir = DIR::LEFT;
							m_ftime = 0;
						}

					}
				
				}
			}
		}

		
		if (m_fDistance <= 70.f)
		{
			
			if (m_eCurState != PLAYER_STATE::IDLE)
			{
				m_ftime += fDT;
				if (m_ftime > 0.3f)
				{
					m_eCurState = PLAYER_STATE::IDLE;
					m_ftime = 0;
				}

			}
					
					
			
		}
		else if(m_fDistance > 70.f && m_fDistance <=300.f)
		{
			CPlayerScript* PScript =(CPlayerScript*)pPlayer->GetScript(L"CPlayerScript");
			if(PScript->GetPlayerState() == PLAYER_STATE::RUN)
				m_eCurState = PLAYER_STATE::RUN;
			else
				m_eCurState = PLAYER_STATE::MOVE;
		}
		else if(m_fDistance > 300.f)
		m_eCurState = PLAYER_STATE::RUN;
		}

}

