#include "pch.h"
#include "CState_Trace.h"


#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CLayer.h>



void CState_Trace::awake()
{
}

void CState_Trace::Exit()
{
	


}

void CState_Trace::update()
{
	const CGameObject* pPlayer = CSceneMgr::GetInst()->GetCurScene()->GetLayer(0)->GetObjects()[0];


}