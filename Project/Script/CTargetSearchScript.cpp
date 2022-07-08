#include "pch.h"
#include "CTargetSearchScript.h"

#include "CPlayerScript.h"

CTargetSearchScript::CTargetSearchScript() :CScript((int)SCRIPT_TYPE::TARGETSEARCHSCRIPT)
, m_Target(nullptr)
, m_fMinDistance(0.f)
{

}


CTargetSearchScript::~CTargetSearchScript()
{
}



void CTargetSearchScript::awake()
{

}

void CTargetSearchScript::update()
{
	Vec2 vDistance;
	m_Target = nullptr;
	for (size_t i = 0; i < m_TargetList.size(); i++)
	{
		Vec3 Pos = GetGameObject()->GetParent()->Transform()->GetLocalPos();
		Vec3 TargetPos = m_TargetList[i]->Transform()->GetLocalPos();

		vDistance.x = TargetPos.x - Pos.x;
		vDistance.y = TargetPos.y - Pos.y;
		float m_fDistance = vDistance.Length();
		if (i == 0)
			m_fMinDistance = m_fDistance;
		if (m_fMinDistance >= m_fDistance)
		{
			m_Target = m_TargetList[i];
		}
	}
	

	if (m_Target != nullptr)
	{
		if (!m_Target->IsDead())
		{	
		CPlayerScript* Player = (CPlayerScript*)GetGameObject()->GetParent()->GetScript(L"CPlayerScript");
		Player->SetTarget(m_Target);
		}
	}

}
void CTargetSearchScript::OnCollisionEnter(CGameObject* _pOther)
{
	if (_pOther->GetLayerIndex() == 3)
	{
		m_TargetList.push_back(_pOther);
	}
}

void CTargetSearchScript::OnCollisionExit(CGameObject* _pOther)
{
	if (_pOther->GetLayerIndex() == 3)
	{
		vector<CGameObject*>::iterator iter = m_TargetList.begin();
		for (; iter != m_TargetList.end(); iter++)
		{
			if ((*iter) == _pOther)
			{
				m_TargetList.erase(iter);
				break;
			}
		}
		m_Target = nullptr;
		CPlayerScript* Player = (CPlayerScript*)GetGameObject()->GetParent()->GetScript(L"CPlayerScript");
		Player->SetTarget(m_Target);
	}
	
	
}

void CTargetSearchScript::OnCollision(CGameObject* _pOther)
{
}

