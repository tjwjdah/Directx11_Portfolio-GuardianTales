#include "pch.h"
#include "TestScene.h"

#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CTransform.h>
#include <Engine\CMeshRender.h>
#include <Engine\CCamera.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CCollider2D.h>
#include <Engine\CParticleSystem.h>
#include <Engine\CLight2D.h>
#include <Engine\CTexture.h>
#include <Engine\CPathMgr.h>
#include <Engine\CCollisionMgr.h>
#include <Engine\CCopyShaderCS.h>
#include <Engine\CSceneMgr.h>
#include <Engine\CSound.h>
#include <Script\CPlayerScript.h>

#include <Script\CMinotauros.h>
#include <Script\CSapa.h>
#include <Script/CBugMonsterScript.h>
#include <Script\CInvaderScript.h>

// Obj script
#include <Script/CRedButtonScript.h>
#include <Script/CStoneDoorScript.h>
#include <Script/CPushStoneScript.h>
#include <Script/CSpeedUpScript.h>
#include <Script/CBlockScript.h>
#include <Script/CBarbedBlockScript.h>
#include <Script/CBreakableStoneScript.h>
#include <Script/CBombFlowerScript.h>
#include <Script/CBombScript.h>
#include <Script/CFireBowlScript.h>
#include <Script/CFireWoodScript.h>
#include <Script/CEndBlockScript.h>
#include <Script/CJumpUpScript.h>
#include <Script/CElecTowerScript.h>
#include <Script/CElecBlockScript.h>
#include <Script/CElecChildScript.h>
#include <Script\CBtnScript.h>
#include <Script\CTargetSearchScript.h>
#include <Script\CTileCollsion.h>
#include <Script\CObjEventScript.h>
#include <Script\CMapScript.h>
#include <Script\CObjState.h>
#include "CSaveLoadMgr.h"
#include <Script\CCharacterSelectScript.h>
#include <Script\CHPHarScript.h>
#include <Script\CSoundScript.h>
void CreateTestScene()
{
	SceneInit();
	CreateSamplePrefab();
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Scene Load
	//CSaveLoadMgr::LoadScene(pCurScene, L"scene\\Title.scene");
	//return;
	
	// =================== 
	// Compute Shader Test
	// ===================
	// Texture Create
	/*Ptr<CTexture> pRWTex = CResMgr::GetInst()->CreateTexture(L"RWTex", 256, 256
		, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS
		, DXGI_FORMAT_R8G8B8A8_UNORM);*/
		//Ptr<CCopyShaderCS> pCS = (CCopyShaderCS*)CResMgr::GetInst()->FindRes<CComputeShader>(L"CopyTextureShader").Get();
		//pCS->SetDestTex(pRWTex);
		//pCS->Excute();
	
	CGameObject* pObj = nullptr;
	
	// =============
	// Camera Object
	// =============
	pObj = new CGameObject;
	pObj->SetName(L"Camera Object");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCamera);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pObj->Camera()->SetLayerAllCheck();
	pCurScene->AddObject(pObj, 0);

	// =======
	// Light2D
	// =======
	pObj = new CGameObject;
	pObj->SetName(L"Light2D Object");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CLight2D);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Light2D()->SetLightType(LIGHT_TYPE::DIR);
	pObj->Light2D()->SetAmbient(Vec3(1.f, 1.f, 1.f));
	pObj->Light2D()->SetRange(100.f);
	pCurScene->AddObject(pObj, 0);

	// =======
// bgm
// =======
	

	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(0.f, 0.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//Camera->SetMapTile(pObj);
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl"));
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"TILE");
	if (nullptr == pTex)
		pTex = CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 0);



	/*
		pObj = new CGameObject;
	pObj->SetName(L"bgm");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CSoundScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	CSoundScript* pSS = (CSoundScript*)pObj->GetScript(L"CSoundScript");
	pSS->SetBgmName(BGM_NAME::BOSSMAIN);
	pCurScene->AddObject(pObj, 0);
	
		CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Nari").Get()->Instantiate();
		pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
		CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
		Player->SetAuto(i);
		Scene->AddObject(pObject, 1);

	
		CGameObject* pObject = 
		pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
		
		Scene->AddObject(pObject, 1);
	
		CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Garam").Get()->Instantiate();
		pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
		CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
		Player->SetAuto(i);
		Scene->AddObject(pObject, 1);

		CGameObject* pObject = CResMgr::GetInst()->FindRes<CPrefab>(L"Eva").Get()->Instantiate();
		pObject->Transform()->SetLocalPos(Vec3(0.f, -64.f * i, 400.f));
		CPlayerScript* Player = (CPlayerScript*)pObject->GetScript(L"CPlayerScript");
		Player->SetAuto(i);
		Scene->AddObject(pObject, 1);
	*/
	/*
	pObj = CResMgr::GetInst()->FindRes<CPrefab>(L"Marina").Get()->Instantiate();
	CPlayerScript* Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetAuto(0);
	
	
	pCurScene->AddObject(pObj, 1);

	pObj = CResMgr::GetInst()->FindRes<CPrefab>(L"Nari").Get()->Instantiate();
	Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetAuto(1);


	pCurScene->AddObject(pObj, 1);

	pObj = CResMgr::GetInst()->FindRes<CPrefab>(L"Garam").Get()->Instantiate();
	Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetAuto(2);


	pCurScene->AddObject(pObj, 1);

	pObj = CResMgr::GetInst()->FindRes<CPrefab>(L"Eva").Get()->Instantiate();
	Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetAuto(3);


	pCurScene->AddObject(pObj, 1);
	
	/*

	pObj = CResMgr::GetInst()->FindRes<CPrefab>(L"touchtostart").Get()->Instantiate();
	pObj->Transform()->SetLocalPosZ(9.f);

	CGameObject* pChildObj = CResMgr::GetInst()->FindRes<CPrefab>(L"HPBar").Get()->Instantiate();
	pObj->Transform()->SetLocalPosZ(10.f);
	CHPHarScript* hphar = (CHPHarScript*)pChildObj->GetScript(L"CHPHarScript");
	hphar->SetPlayer(false);
	CScript::AddChild(pObj, pChildObj);
	
	pCurScene->AddObject(pObj, 3);
	*/

	
	/*

	pObj = new CGameObject;
	pObj->SetName(L"Select");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SelectMtrl"));
	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Select");
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, m_pTexture.Get());



	pCurScene->AddObject(pObj, 0);
	
	pObj = new CGameObject;
	pObj->SetName(L"Select_Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCharacterSelectScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));



	pCurScene->AddObject(pObj, 10);

	*/

	// ==========
// Background
// ==========
	/*
	pObj = new CGameObject;
	pObj->SetName(L"bossback");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(1000.f, 1000.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BossBackMtrl"));

	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"bossback");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BossBackMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTexture.Get());

	//pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	pCurScene->AddObject(pObj, 0);


	// ==============
	// Monster Object
	// ==============
	pObj = new CGameObject;
	pObj->SetName(L"Mino11");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->AddComponent(new CAnimator2D);
	pObj->Transform()->SetLocalPos(Vec3(300.f, 70.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Mino");
	pObj->Animator2D()->CreateAnimation(L"DEAD_DOWN", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 45, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");
	CBtnScript* pScript = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	pScript->SetSName(L"scene\\Snack4.scene");
	pCurScene->AddObject(pObj, 5);

	pObj = new CGameObject;
	pObj->SetName(L"Sapa11");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->AddComponent(new CAnimator2D);
	pObj->Transform()->SetLocalPos(Vec3(-60.f, 105.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Sapa");
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 128.f * 50), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");
	CBtnScript* pScript1 = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	pScript1->SetSName(L"scene\\Dun123.scene");
	pCurScene->AddObject(pObj, 5);

	pObj = new CGameObject;
	pObj->SetName(L"Bug11");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->AddComponent(new CAnimator2D);
	pObj->Transform()->SetLocalPos(Vec3(-50, -190, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug");
	pObj->Animator2D()->CreateAnimation(L"IDLE", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 30, 0.04f);
	pObj->Animator2D()->PlayAnimation(L"IDLE", true);
	CBtnScript* pScript2 = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	pScript2->SetSName(L"scene\\dessertmap.scene");
	pCurScene->AddObject(pObj, 5);

	pObj = new CGameObject;
	pObj->SetName(L"Invader11");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->AddComponent(new CAnimator2D);
	pObj->Transform()->SetLocalPos(Vec3(-370.f, -70.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader");
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN", true);

	CBtnScript* pScript3 = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	pScript3->SetSName(L"scene\\Town123.scene");
	pCurScene->AddObject(pObj, 5);


	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(1000.f, 1000.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//Camera->SetMapTile(pObj);
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl"));
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"TILE");
	if (nullptr == pTex)
		pTex = CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pCurScene->AddObject(pObj, 0);
	*/





	// ==============
	// Player Object
	// ==============
	/*
	pObj = new CGameObject;
	pObj->SetName(L"Player");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(-288.f, 288.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva");
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 36, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 11, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 18, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 16, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2", m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP3", m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 36, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 36, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 23, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 35), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 128.f * 36), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture, Vec2(0.f, 128.f * 37), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3", m_pTexture, Vec2(0.f, 128.f * 38), Vec2(128.f, 128.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 39), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 128.f * 40), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 128.f * 41), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 42), Vec2(128.f, 128.f), 9, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 43), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 128.f * 44), Vec2(128.f, 128.f), 10, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);
	CPlayerScript* Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");

	Player->SetCharacter(Character::EVA);
	Player->SetAuto(0);
	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.f, 2.f, 1.f));
	CScript::AddChild(pObj, pChildObj);



	pCurScene->AddObject(pObj, 1);

	/*

	pObj = new CGameObject;
	pObj->SetName(L"Marina");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(-288.f, 288.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina");

	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP3", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP4", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_UP", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 22, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3", m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT4", m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_RIGHT", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN4", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 35), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 128.f * 36), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_DOWN", m_pTexture, Vec2(0.f, 128.f * 37), Vec2(128.f, 128.f), 15, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 128.f * 38), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 128.f * 39), Vec2(128.f, 128.f), 22, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture, Vec2(0.f, 128.f * 40), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3", m_pTexture, Vec2(0.f, 128.f * 41), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT4", m_pTexture, Vec2(0.f, 128.f * 42), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture, Vec2(0.f, 128.f * 43), Vec2(128.f, 128.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 128.f * 44), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 45), Vec2(128.f, 128.f), 15, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 128.f * 46), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 47), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 48), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 49), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 128.f * 50), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_LEFT", m_pTexture, Vec2(0.f, 128.f * 51), Vec2(128.f, 128.f), 15, 0.03f, true);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);
	 Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");

	Player->SetCharacter(Character::MARINA);
	Player->SetAuto(1);
	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.f, 2.f, 1.f));
	CScript::AddChild(pObj, pChildObj);


	pCurScene->AddObject(pObj, 1);

	pObj = new CGameObject;
	pObj->SetName(L"Nari");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(-288.f, 288.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari");
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 16, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 11, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 55, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_UP", m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 55, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_DOWN", m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 128.f * 35), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 36), Vec2(128.f, 128.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 37), Vec2(128.f, 128.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 38), Vec2(128.f, 128.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 128.f * 39), Vec2(128.f, 128.f), 18, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);
	Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetCharacter(Character::NARI);
	Player->SetAuto(2);
	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.f, 2.f, 1.f));
	CScript::AddChild(pObj, pChildObj);
	pCurScene->AddObject(pObj, 1);

	pObj = new CGameObject;
	pObj->SetName(L"Garam");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(-288.f, 288.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Garam");

	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_DOWN", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 26, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 29, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 29, 0.04f, true);  //x
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 30, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 9, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_UP", m_pTexture, Vec2(0.f, 128.f * 35), Vec2(128.f, 128.f), 26, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 36), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 37), Vec2(128.f, 128.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture, Vec2(0.f, 128.f * 38), Vec2(128.f, 128.f), 10, 0.04f);

	pObj->Animator2D()->PlayAnimation(L"WALKBOMB_RIGHT", true);
	CPlayerScript* Player2 = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player2->SetCharacter(Character::GARAM);
	Player2->SetAuto(3);
	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.f, 2.f, 1.f));
	CScript::AddChild(pObj, pChildObj);

	pCurScene->AddObject(pObj, 1);
	*/
	// ==========
	// Background
	// ==========
	

	// ==============
	// Monster Object
	// ==============
	/*
	pObj = new CGameObject;
	pObj->SetName(L"Mino");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMinotauros);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

 m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Mino");

	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP",			m_pTexture, Vec2(0.f, 128.f * 0),  Vec2(128.f, 128.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_UP",		m_pTexture, Vec2(0.f, 128.f * 1),  Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP_UP",	m_pTexture, Vec2(0.f, 128.f * 2),  Vec2(128.f, 128.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP",			m_pTexture, Vec2(0.f, 128.f * 3),  Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP",				m_pTexture, Vec2(0.f, 128.f * 4),  Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",				m_pTexture, Vec2(0.f, 128.f * 5),  Vec2(128.f, 128.f), 40, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 6),  Vec2(128.f, 128.f), 38, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_RIGHT",	m_pTexture, Vec2(0.f, 128.f * 7),  Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 8),  Vec2(128.f, 128.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGE_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 9),  Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADY_RIGHT",	m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADYLP_RIGHT", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 40, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT",			m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 38, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_LEFT",	m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLP_LEFT",	m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 6, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGE_LEFT",			m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADY_LEFT",	m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADYLP_LEFT",	m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT",		m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT",			m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",			m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 40, 0.03f, true);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_DOWN", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP_DOWN", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_DOWN", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 45, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWEND_DOWN", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWSTART_DOWN", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 40, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");
	pCurScene->AddObject(pObj, 3);
	*/
	
	
	/*pObj = new CGameObject;
	pObj->SetName(L"Sapa");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CSapa);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Sapa");

	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1",		m_pTexture, Vec2(0.f,128.f * 0), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BACK_UP",			m_pTexture, Vec2(0.f,128.f * 1), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_UP",	m_pTexture, Vec2(0.f,128.f * 2), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP",		m_pTexture, Vec2(0.f,128.f * 3), Vec2(128.f, 128.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_UP",	m_pTexture, Vec2(0.f,128.f * 4), Vec2(128.f, 128.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP",			m_pTexture, Vec2(0.f,128.f * 5), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_UP",		m_pTexture, Vec2(0.f,128.f * 6), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_UP",		m_pTexture, Vec2(0.f,128.f * 7), Vec2(128.f, 128.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",			m_pTexture, Vec2(0.f,128.f * 8), Vec2(128.f, 128.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKEFFECT_RIGHT",	m_pTexture, Vec2(0.f, 128.f * 9),  Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2",		m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3",		m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_RIGHT3",	m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY2_RIGHT3",	m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT2",		m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT3",		m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT1",		m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 9, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_RIGHT",		m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SIDE_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",			m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKEFFECT_LEFT",	m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2",		m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3",		m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 25, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_LEFT3",	m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY2_LEFT3",	m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 25, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_LEFT",		m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT2",		m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT3",		m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT1",		m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 5, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_LEFT",		m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT",			m_pTexture, Vec2(0.f, 128.f * 35), Vec2(128.f, 128.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_LEFT",			m_pTexture, Vec2(0.f, 128.f * 36), Vec2(128.f, 128.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_LEFT",			m_pTexture, Vec2(0.f, 128.f * 37), Vec2(128.f, 128.f), 9, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_LEFT",		m_pTexture, Vec2(0.f, 128.f * 38), Vec2(128.f, 128.f), 8, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SIDE_LEFT",			m_pTexture, Vec2(0.f, 128.f * 39), Vec2(128.f, 128.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",			m_pTexture, Vec2(0.f, 128.f * 40), Vec2(128.f, 128.f), 35, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1",		m_pTexture, Vec2(0.f, 128.f * 41), Vec2(128.f, 128.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2",		m_pTexture, Vec2(0.f, 128.f * 42), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3",		m_pTexture, Vec2(0.f, 128.f * 43), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN4",		m_pTexture, Vec2(0.f, 128.f * 44), Vec2(128.f, 128.f), 23, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN5",		m_pTexture, Vec2(0.f, 128.f * 45), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CIRCLEWAVE_DOWN",		m_pTexture, Vec2(0.f, 128.f * 46), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN",		m_pTexture, Vec2(0.f, 128.f * 47), Vec2(128.f, 128.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_DOWN",		m_pTexture, Vec2(0.f, 128.f * 48), Vec2(128.f, 128.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"FRONT_DOWN",			m_pTexture, Vec2(0.f, 128.f * 49), Vec2(128.f, 128.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN",			m_pTexture, Vec2(0.f, 128.f * 50), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_DOWN",			m_pTexture, Vec2(0.f, 128.f * 51), Vec2(128.f, 128.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_DOWN",			m_pTexture, Vec2(0.f, 128.f * 52), Vec2(128.f, 128.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_DOWN1",		m_pTexture, Vec2(0.f, 128.f * 53), Vec2(128.f, 128.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_DOWN2",		m_pTexture, Vec2(0.f, 128.f * 54), Vec2(128.f, 128.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBEND_DOWN",		m_pTexture, Vec2(0.f, 128.f * 55), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBLOOP_DOWN1",		m_pTexture, Vec2(0.f, 128.f * 56), Vec2(128.f, 128.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBLOOP_DOWN2",		m_pTexture, Vec2(0.f, 128.f * 57), Vec2(128.f, 128.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBREADY_DOWN",		m_pTexture, Vec2(0.f, 128.f * 58), Vec2(128.f, 128.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN",			m_pTexture, Vec2(0.f, 128.f * 59), Vec2(128.f, 128.f), 35, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");

	pCurScene->AddObject(pObj, 3);
	

	// ==============
	// Invader
	// ==============
	
	pObj = new CGameObject;
	pObj->SetName(L"Invader");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CInvaderScript);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256*2.f, 256*2.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	//Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader");
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader");

	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 40, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_UP", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURD_UP", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 1, 0.04f);  //위로 돌진
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 30, 0.04f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 20, 0.04f);  //1
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 40, 0.04f);   //2 -> 1-> IDLE
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_DOWN", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 20, 0.04f); //돌진공격 끝나고 대기상태 ->IDLE
	pObj->Animator2D()->CreateAnimation(L"GAURD_DOWN", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 1, 0.04f);   //아래로 돌진
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 128.f * 12), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THUNDEREND_DOWN", m_pTexture, Vec2(0.f, 128.f * 13), Vec2(128.f, 128.f), 30, 0.04f); //공격 끝
	pObj->Animator2D()->CreateAnimation(L"THUNDERSTART_DOWN", m_pTexture, Vec2(0.f, 128.f * 14), Vec2(128.f, 128.f), 35, 0.04f); //공격 준비, 시작
	pObj->Animator2D()->CreateAnimation(L"THUNDER2_DOWN", m_pTexture, Vec2(0.f, 128.f * 15), Vec2(128.f, 128.f), 6, 0.04f); //공격
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 128.f * 16), Vec2(128.f, 128.f), 35, 0.04f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture, Vec2(0.f, 128.f * 17), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture, Vec2(0.f, 128.f * 18), Vec2(128.f, 128.f), 40, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT", m_pTexture, Vec2(0.f, 128.f * 19), Vec2(128.f, 128.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_RIGHT", m_pTexture, Vec2(0.f, 128.f * 20), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASH_RIGHT", m_pTexture, Vec2(0.f, 128.f * 21), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASHREADY_RIGHT", m_pTexture, Vec2(0.f, 128.f * 22), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURD_RIGHT", m_pTexture, Vec2(0.f, 128.f * 23), Vec2(128.f, 128.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT", m_pTexture, Vec2(0.f, 128.f * 24), Vec2(128.f, 128.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 128.f * 25), Vec2(128.f, 128.f), 30, 0.04f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture, Vec2(0.f, 128.f * 26), Vec2(128.f, 128.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture, Vec2(0.f, 128.f * 27), Vec2(128.f, 128.f), 40, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT", m_pTexture, Vec2(0.f, 128.f * 28), Vec2(128.f, 128.f), 1, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_LEFT", m_pTexture, Vec2(0.f, 128.f * 29), Vec2(128.f, 128.f), 20, 0.04f, true);  //돌진 공격 끝나고 윙 ? 상태 -> IDLE
	pObj->Animator2D()->CreateAnimation(L"GAURDDASH_LEFT", m_pTexture, Vec2(0.f, 128.f * 30), Vec2(128.f, 128.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASHREADY_LEFT", m_pTexture, Vec2(0.f, 128.f * 31), Vec2(128.f, 128.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"GAURD_LEFT", m_pTexture, Vec2(0.f, 128.f * 32), Vec2(128.f, 128.f), 1, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT", m_pTexture, Vec2(0.f, 128.f * 33), Vec2(128.f, 128.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 128.f * 34), Vec2(128.f, 128.f), 30, 0.04f, true);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN", true);
	pCurScene->AddObject(pObj, 3);
	


	// ==============
	// Bug
	// ==============
	/*
	pObj = new CGameObject;
	pObj->SetName(L"Bug");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CBugMonsterScript);

	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f * 2, 256.f * 2, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	//Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug");
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug");

	pObj->Animator2D()->CreateAnimation(L"ATTACK", m_pTexture, Vec2(0.f, 128.f * 0), Vec2(128.f, 128.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY", m_pTexture, Vec2(0.f, 128.f * 1), Vec2(128.f, 128.f), 35, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP", m_pTexture, Vec2(0.f, 128.f * 2), Vec2(128.f, 128.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD", m_pTexture, Vec2(0.f, 128.f * 3), Vec2(128.f, 128.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GROGGY", m_pTexture, Vec2(0.f, 128.f * 4), Vec2(128.f, 128.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IDLE", m_pTexture, Vec2(0.f, 128.f * 5), Vec2(128.f, 128.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IN", m_pTexture, Vec2(0.f, 128.f * 6), Vec2(128.f, 128.f), 26, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"OUT1", m_pTexture, Vec2(0.f, 128.f * 7), Vec2(128.f, 128.f), 30, 0.03f); //돌공격 이랑 같이 나옴
	pObj->Animator2D()->CreateAnimation(L"OUT2", m_pTexture, Vec2(0.f, 128.f * 8), Vec2(128.f, 128.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SPIN", m_pTexture, Vec2(0.f, 128.f * 9), Vec2(128.f, 128.f), 7, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SPINCASTLP", m_pTexture, Vec2(0.f, 128.f * 10), Vec2(128.f, 128.f), 5, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SPINCASTREADY", m_pTexture, Vec2(0.f, 128.f * 11), Vec2(128.f, 128.f), 25, 0.04f);

	pObj->Animator2D()->PlayAnimation(L"IDLE", true);
	pCurScene->AddObject(pObj, 3);
	*/

	// =============
	// PostEffect
	// =============
	///*CGameObject* pPostEffect = new CGameObject;
	//pPostEffect->SetName(L"PostEffect Object");
	//pPostEffect->AddComponent(new CTransform);
	//pPostEffect->AddComponent(new CMeshRender);
	//pPostEffect->Transform()->SetLocalPos(Vec3(0.f, 0.f, 100.f));
	//pPostEffect->Transform()->SetLocalScale(Vec3(1600.f, 900.f, 1.f));
	//pPostEffect->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pPostEffect->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PostEffectMtrl"));
	//pCurScene->AddObject(pPostEffect, 1);*/

	// ===============
	// particle object
	// ===============
	/*CGameObject* pParticleObject = new CGameObject;
	pParticleObject->AddComponent(new CTransform);
	pParticleObject->AddComponent(new CParticleSystem);
	pParticleObject->Transform()->SetLocalPos(Vec3(0.f, 0.f, 300.f));
	pCurScene->AddObject(pParticleObject, 0);
	*/

	// ===============
	// Button object (빨간버튼)
	//// ===============
	//CGameObject* redbutton = new CGameObject;
	//redbutton->SetName(L"RedButton");////////

	//redbutton->AddComponent(new CTransform);
	//redbutton->AddComponent(new CMeshRender);
	//redbutton->AddComponent(new CCollider2D);
	//redbutton->AddComponent(new CRedButtonScript);////////
	//redbutton->AddComponent(new CObjEventScript);
	//redbutton->Transform()->SetLocalPos(Vec3(-95.f, 286.f, 400.f));
	//redbutton->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));
	//redbutton->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	//redbutton->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//redbutton->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl"));////////

	//redbutton->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(redbutton, 3);


	// ===============
	// stonedoor object (열리는 돌문)
	// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"StoneDoor");//////////

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CStoneDoorScript);////////
	//pObj->AddComponent(new CObjEventScript);

	//pObj->Transform()->SetLocalPos(Vec3(191.f,-111.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));////////////

	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	//dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->SetEventType(EventType::TriggerOnOff);
	//dynamic_cast<CObjEventScript*>(pObj->GetScript(L"CObjEventScript"))->PushEvnetChild(redbutton);

	//pCurScene->AddObject(pObj, 2);


	//// ===============
	//// push stone object (미는 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"PushStone"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CPushStoneScript); ////
	//pObj->AddComponent(new CObjEventScript);
	//pObj->Transform()->SetLocalPos(Vec3(-286.f, 170.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	// ===============
	// Speed Up Board ( 스피드 업 발판 )
	// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"SpeedUp"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CSpeedUpScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-30.f, 160.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	//pCurScene->AddObject(pObj, 3);

	//// ===============
	//// Barbed Block (가시 있는 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"BarbedBlock"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBarbedBlockScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(228.f, 200.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	//// ===============
	//// Block (일반 장애물)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"Block"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBlockScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-222.f, -222.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlockMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	// ===============
	// BreakableStone (부술 수 있는 돌)
	// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"BreakableStone"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBreakableStoneScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-224.f, -30.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 2);

	//// ===============
	//// BombFlower (폭탄꽃)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"BombFlower"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CBombFlowerScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(32.f, 45.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(60, 80, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 3);

	//Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->FindRes<CTexture>(L"Burn");

	//// ===============
	//// FireWood (장작)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"FireWood"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CFireWoodScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-32.f, 300.f, 400.f));
	//pObj->Transform()->SetLocalScale(Vec3(42, 60, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//dynamic_cast<CFireWoodScript*>(pObj->GetScript(L"CFireWoodScript"))->SetFireTime(5.f); //5초 설정, 아무것도 설정하지 않으면 계속 켜져있는 것
	//pObj->AddComponent(new CObjEventScript);
	//pCurScene->AddObject(pObj, 3);

	//// 불 애니메이션
	//CGameObject* pChildObj = new CGameObject;
	//pChildObj->SetName(L"FireWoodChild");
	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);
	//pChildObj->AddComponent(new CAnimator2D);
	//pChildObj->Transform()->SetLocalScale(Vec3(1.1, 1.5, 0.f));
	//pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.7f, 0.f));
	//pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	//pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	//pChildObj->Animator2D()->CreateAnimation(L"NONE", pSmokeTex, Vec2(0.f, 0.f), Vec2(0.f, 1.f), 5, 0.1f);
	//pChildObj->Animator2D()->PlayAnimation(L"NONE", true);
	//pCurScene->AddObject(pChildObj, 3);
	//CScript::AddChild(pObj, pChildObj);

	//// ===============
	////  FireBowl (화로)
	//// ===============
	//pObj = new CGameObject;
	//pObj->SetName(L"FireBowl"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CFireBowlScript); ////
	//pObj->Transform()->SetLocalPos(Vec3(-158.f, 227.f, 401.f));
	//pObj->Transform()->SetLocalScale(Vec3(60, 60, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl"));/////
	//pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pCurScene->AddObject(pObj, 3);

	//// 불 애니메이션
	//pChildObj = new CGameObject;
	//pChildObj->SetName(L"FireBowlChild");
	//pChildObj->AddComponent(new CTransform);
	//pChildObj->AddComponent(new CMeshRender);
	//pChildObj->AddComponent(new CAnimator2D);
	//pChildObj->Transform()->SetLocalScale(Vec3(1, 2, 0.f));
	//pChildObj->Transform()->SetLocalPos(Vec3(0, 0.63, 0.f));
	//pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	//pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	//pChildObj->Animator2D()->PlayAnimation(L"BURN", true);
	//pCurScene->AddObject(pChildObj, 3);

	//CScript::AddChild(pObj, pChildObj);
	
	// ===============
	// EndBlock (ENd Block)
	// ===============
	/*
	pObj = new CGameObject;
	pObj->SetName(L"EndBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CEndBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(0.f, -210.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(150, 200, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"EndBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.5f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -50.f));
	pCurScene->AddObject(pObj, 2);

	// ===============
	// Jump Up Board ( 점프 발판 )
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"JumpUp"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CJumpUpScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-220.f, 160.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"JumpUpMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	pCurScene->AddObject(pObj, 3);

	// ===============
	// Elec Tower (전기 생성 탑)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecTower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecTowerScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-288.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecTowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pCurScene->AddObject(pObj, 2);

	// Elec Tower (자식)
	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"ElecChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CElecChildScript); ////
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));/////
	pChildObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pChildObj->Transform()->SetLocalScale(Vec3(10.f, 10.0f, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pCurScene->AddObject(pChildObj, 2);
	CScript::AddChild(pObj, pChildObj);

	// ===============
	// Elec Block (전기 블록)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-32.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	pCurScene->AddObject(pObj, 3);

	// ===============
	// Elec Block (전기 블록) 2222
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecBlock2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecBlockScript); ////
	pObj->Transform()->SetLocalPos(Vec3(-32.f, 170.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));
	pCurScene->AddObject(pObj, 3);

	// 0번 Player / 1번 배경 / 2번 장애물 / 3번 버튼,폭탄꽃

	//test
	//pObj = new CGameObject;
	//pObj->SetName(L"FireBowl"); /////
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 401.f));
	//pObj->Transform()->SetLocalScale(Vec3(500, 500, 1.f));
	//pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	//pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std2DMtrl"));/////
	//pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));
	// pTex = CResMgr::GetInst()->FindRes<CTexture>(L"dd");
	//if (nullptr == pTex)
	//	pTex = CResMgr::GetInst()->Load<CTexture>(L"dd", L"texture\\dd.png");
	//pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	//pCurScene->AddObject(pObj, 3);
	//CScript::AddChild(pObj, pChildObj);
	*/
	// Collision Check
	   // Collision Check
CCollisionMgr::GetInst()->CollisionCheck(1, 3);
CCollisionMgr::GetInst()->CollisionCheck(2, 3);
CCollisionMgr::GetInst()->CollisionCheck(1, 31);
CCollisionMgr::GetInst()->CollisionCheck(3, 31);
CCollisionMgr::GetInst()->CollisionCheck(1, 30);
CCollisionMgr::GetInst()->CollisionCheck(3, 30);

// player - obj
CCollisionMgr::GetInst()->CollisionCheck(1, 5); //막
CCollisionMgr::GetInst()->CollisionCheck(1, 4); //안막
CCollisionMgr::GetInst()->CollisionCheck(4, 5); // 폭탄 - 바위 ,전기 - 전기탑
CCollisionMgr::GetInst()->CollisionCheck(5, 5); // 폭탄 - 바위 ,전기 - 전기탑
	 //막
	 //안막
	
	// Scene Save
	CSaveLoadMgr::SaveScene(pCurScene, L"scene\\TestScene.scene");
	
	// Scene Initialize()
	//pCurScene->awake();
	//pCurScene->start();
}

//이미지 로드
void SceneInit()
{
	// Load GUI UI
	CResMgr::GetInst()->Load<CTexture>(L"LoadButton", L"icon\\loadbutton.png");
	CResMgr::GetInst()->Load<CTexture>(L"SaveButton", L"icon\\savebutton.png");
	CResMgr::GetInst()->Load<CTexture>(L"TILE", L"texture\\TIle.bmp");

	// Load Player Img ================================================================================================================ Player
	CResMgr::GetInst()->Load<CTexture>(L"Marina", L"texture\\player\\marina\\marina.png");	//마리나
	CResMgr::GetInst()->Load<CTexture>(L"Nari", L"texture\\player\\nari\\nari.png");		//나리
	CResMgr::GetInst()->Load<CTexture>(L"Eva", L"texture\\player\\eva\\eva.png");			//에바
	CResMgr::GetInst()->Load<CTexture>(L"Garam", L"texture\\player\\garam\\garam.png");	    //가람

	// Load Attack Effect
	// Marina
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack1", L"texture\\player\\marina\\skill\\Attack1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack2", L"texture\\player\\marina\\skill\\Attack2.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Attack3", L"texture\\player\\marina\\skill\\Attack3.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Skill1", L"texture\\player\\marina\\skill\\Skill1_1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Skill2", L"texture\\player\\marina\\skill\\hook.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Hiteffect", L"texture\\player\\marina\\skill\\Hiteffect.png");
	CResMgr::GetInst()->Load<CTexture>(L"Marina_Hiteffect2", L"texture\\player\\marina\\skill\\Hiteffect2.png");


	//Nari
	CResMgr::GetInst()->Load<CTexture>(L"Nari_Attack1", L"texture\\player\\nari\\skill\\Attack1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Nari_Hiteffect", L"texture\\player\\nari\\skill\\Hiteffect.png");
	CResMgr::GetInst()->Load<CTexture>(L"Nari_Hiteffect2", L"texture\\player\\nari\\skill\\Hiteffect2.png");
	CResMgr::GetInst()->Load<CTexture>(L"Nari_Hiteffect3", L"texture\\player\\nari\\skill\\Hiteffect3.png");


	//Eva 에바
	CResMgr::GetInst()->Load<CTexture>(L"Eva_Attack1", L"texture\\player\\eva\\skill\\Attack1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Eva_Attack2", L"texture\\player\\eva\\skill\\Attack2.png");
	CResMgr::GetInst()->Load<CTexture>(L"Eva_Skill1", L"texture\\player\\eva\\skill\\Skill1.png");//88_204_256
	CResMgr::GetInst()->Load<CTexture>(L"Eva_Hiteffect", L"texture\\player\\eva\\skill\\Hiteffect.png");


	//garam 가람
	CResMgr::GetInst()->Load<CTexture>(L"Garam_Attack1", L"texture\\player\\garam\\skill\\Attack1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Garam_Attack2", L"texture\\player\\garam\\skill\\Attack11.png");
	CResMgr::GetInst()->Load<CTexture>(L"Garam_Skill1", L"texture\\player\\garam\\skill\\Skill1.png");
	CResMgr::GetInst()->Load<CTexture>(L"Garam_Skill2", L"texture\\player\\garam\\skill\\Skill11.png");
	CResMgr::GetInst()->Load<CTexture>(L"Garam_Hiteffect", L"texture\\player\\garam\\skill\\Hiteffect.png");



	// Load Player Img ================================================================================================================ Monster
	CResMgr::GetInst()->Load<CTexture>(L"Bug", L"texture\\monster\\bug\\bug.png");			 //사막벌레
	CResMgr::GetInst()->Load<CTexture>(L"Invader", L"texture\\monster\\invader\\invader.png");//인베이더
	CResMgr::GetInst()->Load<CTexture>(L"Mino", L"texture\\monster\\mino\\mino.png");		 //미노타
	CResMgr::GetInst()->Load<CTexture>(L"Sapa", L"texture\\monster\\sapa\\sapa.png");	     //대머리아저씨
	
	// Load Attack Effect
	//bug
	CResMgr::GetInst()->Load<CTexture>(L"Bug_Attack1", L"texture\\monster\\bug\\skill\\Attack1.png");	     //103_148_50
	CResMgr::GetInst()->Load<CTexture>(L"Bug_Attack11", L"texture\\monster\\bug\\skill\\Attack11.png");      //150_105_100
	CResMgr::GetInst()->Load<CTexture>(L"Bug_Attack2", L"texture\\monster\\bug\\skill\\skill.png");

	//invader
	CResMgr::GetInst()->Load<CTexture>(L"Invader_Attack1", L"texture\\monster\\invader\\skill\\Attack1.png"); //136 200 35 
	CResMgr::GetInst()->Load<CTexture>(L"Invader_Attack2", L"texture\\monster\\invader\\skill\\Attack2.png"); //190 190 74 
	CResMgr::GetInst()->Load<CTexture>(L"Invader_Attack3", L"texture\\monster\\invader\\skill\\Attack3.png"); //141 90 40



	//mino
	CResMgr::GetInst()->Load<CTexture>(L"MinoFireball", L"texture\\monster\\mino\\skill\\MinoFireball.png");			 //사막벌레
	CResMgr::GetInst()->Load<CTexture>(L"MInoWave", L"texture\\monster\\mino\\skill\\MInoWave.png");			 //사막벌레


	//sapa
	CResMgr::GetInst()->Load<CTexture>(L"Bobm", L"texture\\monster\\sapa\\skill\\Bobm.png");			 
	CResMgr::GetInst()->Load<CTexture>(L"BobmStart", L"texture\\monster\\sapa\\skill\\BobmStart.png");			 
	CResMgr::GetInst()->Load<CTexture>(L"Jin", L"texture\\monster\\sapa\\skill\\Jin.png");			
	CResMgr::GetInst()->Load<CTexture>(L"Telpo", L"texture\\monster\\sapa\\skill\\Telpo.png");			


	CResMgr::GetInst()->Load<CTexture>(L"AttackHit", L"texture\\monster\\AttackHit.png");
	CResMgr::GetInst()->Load<CTexture>(L"FireHit", L"texture\\monster\\FireHit.png");
	CResMgr::GetInst()->Load<CTexture>(L"InveHit", L"texture\\monster\\InveHit.png");
	CResMgr::GetInst()->Load<CTexture>(L"RockHit", L"texture\\monster\\RockHit.png");
	CResMgr::GetInst()->Load<CTexture>(L"SapaHit", L"texture\\monster\\SapaHit.png");

	CResMgr::GetInst()->Load<CTexture>(L"MinoDie", L"texture\\monster\\MinoDie.png");
	CResMgr::GetInst()->Load<CTexture>(L"InveDie", L"texture\\monster\\InveDie.png");
	CResMgr::GetInst()->Load<CTexture>(L"BugDie", L"texture\\monster\\BugDie.png");
	CResMgr::GetInst()->Load<CTexture>(L"SapaDie", L"texture\\monster\\SapaDie.png");
	
	// Load Obj Img ===================================================================================================================== Obj
	CResMgr::GetInst()->Load<CTexture>(L"redbutton", L"texture\\object\\8.png");			//빨간 버튼
	CResMgr::GetInst()->Load<CTexture>(L"stonedoor", L"texture\\object\\6.png");			//돌로 된 문 (버튼을 밟으면 열림)
	CResMgr::GetInst()->Load<CTexture>(L"stonedoor2", L"texture\\object\\6-1.png");			//돌로 된 문 (버튼을 밟으면 열림)
	CResMgr::GetInst()->Load<CTexture>(L"pushstone", L"texture\\object\\17.png");			//밀 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"pushsmallstone", L"texture\\object\\12.png");		//밀 수 있는 작은돌
	CResMgr::GetInst()->Load<CTexture>(L"breakablestone", L"texture\\object\\15.png");		//부실 수 있는 돌
	CResMgr::GetInst()->Load<CTexture>(L"block", L"texture\\object\\18.png");				//지나갈 수 없는 장애물
	CResMgr::GetInst()->Load<CTexture>(L"barbedblock", L"texture\\object\\13.png");			//가시 달린 장애물
	CResMgr::GetInst()->Load<CTexture>(L"speedup", L"texture\\object\\9.png");				//스피드 업 발판
	CResMgr::GetInst()->Load<CTexture>(L"jumpup", L"texture\\object\\7.png");				//점픛 업 발판
	CResMgr::GetInst()->Load<CTexture>(L"bombflower", L"texture\\object\\14.png");			//폭탄꽃
	CResMgr::GetInst()->Load<CTexture>(L"flower", L"texture\\object\\14-1.png");			//꽃
	CResMgr::GetInst()->Load<CTexture>(L"bomb", L"texture\\object\\14-3.png");				//폭탄
	CResMgr::GetInst()->Load<CTexture>(L"firewood", L"texture\\object\\5.png");				//장작
	CResMgr::GetInst()->Load<CTexture>(L"firebowl", L"texture\\object\\4.png");				//화로
	CResMgr::GetInst()->Load<CTexture>(L"endblock", L"texture\\object\\1.png");				//End block
	CResMgr::GetInst()->Load<CTexture>(L"endblock2", L"texture\\object\\1-1.png");			//End block 부셔진것
	CResMgr::GetInst()->Load<CTexture>(L"elecblock", L"texture\\object\\10.png");			//Electric Block
	CResMgr::GetInst()->Load<CTexture>(L"electower", L"texture\\object\\11.png");			//Electirc Tower

		// BackGround Img
	CResMgr::GetInst()->Load<CTexture>(L"Desert", L"texture\\BackGround\\Desert.bmp");
	CResMgr::GetInst()->Load<CTexture>(L"Dungeon", L"texture\\BackGround\\Dungeon.bmp");
	CResMgr::GetInst()->Load<CTexture>(L"Snack", L"texture\\BackGround\\Snack.bmp");
	CResMgr::GetInst()->Load<CTexture>(L"Town", L"texture\\BackGround\\Town.bmp");
	CResMgr::GetInst()->Load<CTexture>(L"bossback", L"texture\\BackGround\\bossback.bmp");

	CResMgr::GetInst()->Load<CTexture>(L"Select", L"texture\\BackGround\\Select.png");

	CResMgr::GetInst()->Load<CTexture>(L"Select_Eva", L"texture\\player\\Select_Eva.png");
	CResMgr::GetInst()->Load<CTexture>(L"Select_Marina", L"texture\\player\\Select_Marina.png");
	CResMgr::GetInst()->Load<CTexture>(L"Select_Garam", L"texture\\player\\Select_Garam.png");
	CResMgr::GetInst()->Load<CTexture>(L"Select_Nari", L"texture\\player\\Select_Nari.png");
	// Texture 로딩 테스트
	

	// effect
	CResMgr::GetInst()->Load<CTexture>(L"Burn", L"texture\\object\\fire.png");               //fire eff
	CResMgr::GetInst()->Load<CTexture>(L"smoke", L"texture\\object\\smoke.png");            // 42.6  43 9
	CResMgr::GetInst()->Load<CTexture>(L"eleceffect", L"texture\\object\\eleceffect.png");        //Electirc Tower effect 
	CResMgr::GetInst()->Load<CTexture>(L"explosion", L"texture\\object\\bombeffect.png");        //Electirc Tower effect 
      //Electirc Tower effect expeffect
	CResMgr::GetInst()->Load<CTexture>(L"expeffect", L"texture\\object\\expeffect.png");
	//UI
	CResMgr::GetInst()->Load<CTexture>(L"HPBar", L"texture\\player\\HPBar.png");
	CResMgr::GetInst()->Load<CTexture>(L"HPBar_Green", L"texture\\player\\HPBar_Green1.png");
	CResMgr::GetInst()->Load<CTexture>(L"HPBar_Red", L"texture\\player\\HPBar_Red1.png");
	CResMgr::GetInst()->Load<CTexture>(L"HPBar_Skyblue", L"texture\\player\\HPBar_Skyblue1.png");
	

	//damage

	CResMgr::GetInst()->Load<CTexture>(L"DamageFont", L"texture\\Damage.png");
	CResMgr::GetInst()->Load<CTexture>(L"MonDamageFont", L"texture\\MonDamage.png");

	//cut
	CResMgr::GetInst()->Load<CTexture>(L"EvaCut", L"texture\\player\\EvaCut.png");
	CResMgr::GetInst()->Load<CTexture>(L"GaramCut", L"texture\\player\\GaramCut.png");
	CResMgr::GetInst()->Load<CTexture>(L"MarinaCut", L"texture\\player\\MarinaCut.png");
	CResMgr::GetInst()->Load<CTexture>(L"NariCut", L"texture\\player\\NariCut.png");




	CResMgr::GetInst()->Load<CTexture>(L"Main", L"texture\\Main.png");
	CResMgr::GetInst()->Load<CTexture>(L"touchtostart", L"texture\\touch_to_start.png");

	CResMgr::GetInst()->Load<CTexture>(L"Backspace", L"texture\\Backspace.png");
	CResMgr::GetInst()->Load<CTexture>(L"CharacterSelect", L"texture\\CharacterSelect.png");

	
	//bgm
	CResMgr::GetInst()->Load<CSound>(L"bgm_dungeon", L"sound\\BGM\\bgm_portal_dungeon.wav");
	CResMgr::GetInst()->Load<CSound>(L"bgm_bossmain", L"sound\\BGM\\bgm_bossmain.wav");
	CResMgr::GetInst()->Load<CSound>(L"bgm_changechar", L"sound\\BGM\\bgm_changechar.wav");
	CResMgr::GetInst()->Load<CSound>(L"bgm_bossintro", L"sound\\BGM\\bgm_battle_boss.wav");
	
	//ui eff
	CResMgr::GetInst()->Load<CSound>(L"eff_button", L"sound\\ui\\eff_button.wav");     //버튼클릭시
	CResMgr::GetInst()->Load<CSound>(L"eff_end", L"sound\\ui\\eff_start.wav");      //보스 시작시
	CResMgr::GetInst()->Load<CSound>(L"eff_start", L"sound\\ui\\01_pvp_start_01.wav");      //보스 시작시
	//obj eff
	CResMgr::GetInst()->Load<CSound>(L"eff_bombexp", L"sound\\obj\\eff_bombexp.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_bombfuse", L"sound\\obj\\eff_bombfuse.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_breakstone", L"sound\\obj\\eff_breakstone.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_endblock", L"sound\\obj\\eff_endblock.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_fire", L"sound\\obj\\eff_fire.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_jumpup", L"sound\\obj\\eff_jumpup.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_pushstone", L"sound\\obj\\eff_pushstone.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_respawn", L"sound\\obj\\eff_respawn.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_slide", L"sound\\obj\\eff_slide.wav");
	CResMgr::GetInst()->Load<CSound>(L"eff_pushstone2", L"sound\\obj\\eff_pushstone2.wav");
	//character sound

	CResMgr::GetInst()->Load<CSound>(L"eff_dash", L"sound\\eff_dash.wav");
	//eva
	CResMgr::GetInst()->Load<CSound>(L"eva_char", L"sound\\eva\\eva_char.wav");      //캐릭터선택시 목소리
	CResMgr::GetInst()->Load<CSound>(L"eva_attack1", L"sound\\eva\\eva_attack1.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"eva_attack2", L"sound\\eva\\eva_attack2.wav");      //일반공격2
	CResMgr::GetInst()->Load<CSound>(L"eva_attack3", L"sound\\eva\\eva_attack3.wav");      //일반공격3
	CResMgr::GetInst()->Load<CSound>(L"eva_skill0", L"sound\\eva\\eva_skill0.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"eva_skill1", L"sound\\eva\\eva_skill1.wav");      //필살기
	CResMgr::GetInst()->Load<CSound>(L"eva_skill2", L"sound\\eva\\eva_skill2.wav");      //필
	CResMgr::GetInst()->Load<CSound>(L"eva_skill3", L"sound\\eva\\eva_skill3.wav");      //필
	//garam
	CResMgr::GetInst()->Load<CSound>(L"garam_char", L"sound\\garam\\garam_char.wav");      //캐릭터선택시 목소리
	CResMgr::GetInst()->Load<CSound>(L"garam_attack1", L"sound\\garam\\garam_attack1.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"garam_skill0", L"sound\\garam\\garam_skill0.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"garam_skill1", L"sound\\garam\\garam_skill1.wav");      //필 쏘는소리
	CResMgr::GetInst()->Load<CSound>(L"garam_skill2", L"sound\\garam\\garam_skill2.wav");      //필 터지는소리
	//마리나
	CResMgr::GetInst()->Load<CSound>(L"marina_char", L"sound\\marina\\marina_char.wav");      //캐릭터선택시 목소리
	CResMgr::GetInst()->Load<CSound>(L"marina_attack1", L"sound\\marina\\marina_attack1.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"marina_attack2", L"sound\\marina\\marina_attack2.wav");      //일반공격2
	CResMgr::GetInst()->Load<CSound>(L"marina_attack3", L"sound\\marina\\marina_attack3.wav");      //일반공격3
	CResMgr::GetInst()->Load<CSound>(L"marina_skill0", L"sound\\marina\\marina_skill0.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"marina_skill1", L"sound\\marina\\marina_skill1.wav");      //필살기
	CResMgr::GetInst()->Load<CSound>(L"marina_skill2", L"sound\\marina\\marina_hook.wav");      //필
	   //나리
	CResMgr::GetInst()->Load<CSound>(L"nari_char", L"sound\\nari\\nari_char.wav");      //캐릭터선택시 목소리
	CResMgr::GetInst()->Load<CSound>(L"nari_attack1", L"sound\\nari\\nari_attack1.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"nari_attack2", L"sound\\nari\\nari_attack2.wav");      //일반공격2
	CResMgr::GetInst()->Load<CSound>(L"nari_skill0", L"sound\\nari\\nari_skill0.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"nari_skill1", L"sound\\nari\\nari_skill1.wav");      //필살기


	CResMgr::GetInst()->Load<CSound>(L"bgm_title_main", L"sound\\BGM\\bgm_title_main.wav");  //시작화면sound

	//sapa
	CResMgr::GetInst()->Load<CSound>(L"sapa_tel", L"sound\\sapa\\01_teleport_02.wav");      //캐릭터선택시 목소리
	CResMgr::GetInst()->Load<CSound>(L"sapa_jingak", L"sound\\sapa\\01_jingak_01.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"sapa_fist", L"sound\\sapa\\02_energy_fist_01.wav");      //일반공격2
	CResMgr::GetInst()->Load<CSound>(L"sapa_shout", L"sound\\sapa\\02_boss_sapa_shout_01.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"sapa_damaged", L"sound\\sapa\\02_boss_sapa_damaged_01.wav");      //필살기
	CResMgr::GetInst()->Load<CSound>(L"sapa_breath", L"sound\\sapa\\02_boss_sapa_breath_01.wav");      //필살기

	//invader
	CResMgr::GetInst()->Load<CSound>(L"invader_attack", L"sound\\invader\\02_invader_boss_attack_01.wav");      //일반공격2
	CResMgr::GetInst()->Load<CSound>(L"invader_roar", L"sound\\invader\\02_invader_boss_roar_01.wav");      //필살기 목소리
	CResMgr::GetInst()->Load<CSound>(L"invader_thunderbolt", L"sound\\invader\\02_invader_boss_thunderbolt_01.wav");      //필살기

	//mino
	CResMgr::GetInst()->Load<CSound>(L"mino_slash", L"sound\\mino\\02_minotaurs_slash_01.wav");      //칼 목소리
	CResMgr::GetInst()->Load<CSound>(L"mino_shout", L"sound\\mino\\02_minotaurs_shout_01.wav");      //일반공격1
	CResMgr::GetInst()->Load<CSound>(L"mino_stomp", L"sound\\mino\\02_minotaurs_stomp_01.wav");      //dash
	CResMgr::GetInst()->Load<CSound>(L"mino_walk", L"sound\\mino\\02_minotaurs_walk_01.wav");      //필살기
	   //bug
	CResMgr::GetInst()->Load<CSound>(L"bug_idle", L"sound\\bug\\02_boss_worm_idle_01.wav");      //칼 목소리
	CResMgr::GetInst()->Load<CSound>(L"bug_pos", L"sound\\bug\\02_explosion_water_01.wav");      //일반공격1
	
}