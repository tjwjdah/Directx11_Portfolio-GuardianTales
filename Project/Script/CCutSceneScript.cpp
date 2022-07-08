#include "pch.h"
#include "CCutSceneScript.h"


#include <Engine\CEventMgr.h>
CCutSceneScript::CCutSceneScript():CScript((int)SCRIPT_TYPE::CUTSCENESCRIPT)
, m_fTime(0.f)
, m_CCharacter(Character::MARINA)
{
}

CCutSceneScript::~CCutSceneScript()
{
}
void CCutSceneScript::update()
{
	if (GetGameObject()->IsDead())
		return;

	m_fTime += fDT;

	Vec3 Pos = Transform()->GetLocalPos();
	if (m_fTime < 0.4)
	{
		if(Pos.y> CamaraPos.y +140.f)
			Pos.y -= fDT * 1500;
	
	}
	else if (m_fTime>=0.4 &&m_fTime < 0.8)
	{
		Pos.x = CamaraPos.x + 100.f;
		Pos.y = CamaraPos.y + 140.f;
		
	}
	else if (m_fTime >= 0.8 && m_fTime < 1.f)
	{
		Pos.y -= fDT * 2000;
		float y = Transform()->GetLocalScale().y;
		y -= fDT * 900;
		Transform()->SetLocalScaleY(y);
	}
	else if (m_fTime >=1.f)
	{
	
		tEvent _temp = {};
		_temp.eEvent = EVENT_TYPE::DELETE_OBJECT;
		_temp.lParam = (DWORD_PTR)GetGameObject();
		CEventMgr::GetInst()->AddEvent(_temp);
	}
	

	Transform()->SetLocalPos(Pos);
}

void CCutSceneScript::awake()
{
	Ptr<CTexture> pTex;
	switch (m_CCharacter)
	{
	case Character::NARI:
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"NariCut");
		break;
	case Character::MARINA:
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"MarinaCut");
		break;
	case Character::GARAM:
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"GaramCut");
		break;
	case Character::EVA:
		pTex = CResMgr::GetInst()->FindRes<CTexture>(L"EvaCut");
		break;

	}
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	int a = 2;
	MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::INT_1, &a);
	Vec3 Pos;
	Pos.x= CamaraPos.x+100;
	
	Pos.y = CamaraPos.y+740;
	Pos.z = 400.f;
	Transform()->SetLocalPos(Pos);
}
