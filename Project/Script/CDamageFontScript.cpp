#include "pch.h"
#include "CDamageFontScript.h"

#include <Engine/CTransform.h>
#include <Engine/CTexture.h>
#include <Engine/CResMgr.h>
#include <Engine/CStructuredBuffer.h>
#include <Engine/CConstBuffer.h>
#include <Engine\CEventMgr.h>
#include <Engine\CMeshRender.h>
#include <Engine\CMaterial.h>
CDamageFontScript::CDamageFontScript():CScript((int)SCRIPT_TYPE::DAMAGEFONTSCRIPT)
, m_Damage_x(0)
, m_Damage_y(0)
, m_DamageUv_x(0.2f)
, m_DamageUv_y(0.5f)
,m_DamageSize(0)
,m_Player(true)
, m_Time(0)
, m_iDamage(0)
{
	m_DamageBuffer = new CStructuredBuffer;
	m_TSharedBuffer = new CStructuredBuffer;
	m_TSharedBuffer->Create(sizeof(tDamageFontShared), 1, nullptr);

	
}
CDamageFontScript::CDamageFontScript(const CDamageFontScript& _origin):
	CScript((int)SCRIPT_TYPE::DAMAGEFONTSCRIPT)
	, m_Damage_x(0)
	, m_Damage_y(0)
	, m_DamageUv_x(0.2f)
	, m_DamageUv_y(0.5f)
	, m_DamageSize(0)
	, m_Player(_origin.m_Player)
	, m_Time(0.f)
	, m_iDamage(0.f)
{
	m_DamageShared.iTileXSize = 0;
	m_DamageShared.iTileYSize = 0;
	m_DamageBuffer = new CStructuredBuffer;
	m_TSharedBuffer = new CStructuredBuffer;
	m_TSharedBuffer->Create(sizeof(tDamageFontShared), 1, nullptr);
}


CDamageFontScript::~CDamageFontScript()
{
	delete m_DamageBuffer;
	delete m_TSharedBuffer;
}




void CDamageFontScript::SetDamageNum(int _Damage)
{
	m_iDamage = _Damage;
	int a = _Damage;
	int	n = 0;
	while (a) {
		a /= 10;
		n++;
	}

	Transform()->SetLocalScale(Vec3((float)n * 40, 40, 1.f));
	m_Damage.resize(n);
	m_DamageSize = n;
	m_Damage_x = n;
	m_Damage_y = 1;
	a = _Damage;
	n = 0;
	while (a) {
		
		n++;
		int z = a % 10;
		SetDamage(m_DamageSize - n, 0, (z));
		a /= 10;
		
	}
}

void CDamageFontScript::SetDamage(int _x, int _y, int index)
{
	
	int z = _y * m_DamageShared.iTileXSize + _x;

	if (index >= 5)
	{
		int n = index % 5;
		m_Damage[(size_t)z].vLeftTop.x = n* m_DamageUv_x;
		m_Damage[(size_t)z].vLeftTop.y = 1 * m_DamageUv_y;
	}
	else
	{
		m_Damage[(size_t)z].vLeftTop.x = index * m_DamageUv_x;
		m_Damage[(size_t)z].vLeftTop.y = 0 * m_DamageUv_y;
	}
	


}

void CDamageFontScript::awake()
{
	Ptr<CTexture> pTex;
	if (m_Player)
	{
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"DamageFont");
	}
	else
	{
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"MonDamageFont");
	}
	MeshRender()->GetCloneMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
}

void CDamageFontScript::update()
{
	if (GetGameObject()->IsDead())
		return;
	//int a = m_iDamage;
	//MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_2, &a);
	m_DamageShared.iTileXSize = m_Damage_x;
	m_DamageShared.iTileYSize = m_Damage_y;
	m_DamageBuffer->Clear();
	if (m_DamageBuffer->GetElementCount() < m_DamageSize)
		m_DamageBuffer->Create(sizeof(tDamageFont), m_DamageSize, nullptr);

	m_DamageBuffer->SetData(m_Damage.data(), sizeof(tDamageFont), (UINT)m_Damage.size());
	m_DamageBuffer->UpdateData(103);
	m_TSharedBuffer->SetData(&m_DamageShared, sizeof(tDamageFontShared), (UINT)1);
	m_TSharedBuffer->UpdateData(104);
	

	
	float Y = Transform()->GetLocalPos().y;

	Y += fDT * 100;
	m_Time += fDT;
	Transform()->SetLocalPosY(Y);

	if (m_Time > 0.2f)
	{
		m_Time = 0;
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}

	
}

void CDamageFontScript::render()
{
	
}

void CDamageFontScript::SaveToScene(FILE* _pFile)
{
}

void CDamageFontScript::LoadFromScene(FILE* _pFile)
{
}
