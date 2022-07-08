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

#include <Script\CPlayerScript.h>

#include <Script\CMissileScript.h>

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

#include <Script\CTargetSearchScript.h>
#include <Script\CTileCollsion.h>
#include <Script\CObjEventScript.h>
#include <Script\CMapScript.h>
#include <Script\CJumpUpScript.h>
#include <Script\CEndBlockScript.h>
#include <Script\CElecChildScript.h>
#include <Script\CElecBlockScript.h>
#include <Script\CElecTowerScript.h>
#include <Script\CPlayerPosSetScript.h>
#include <Script\CTargetToAuto.h>
#include <Script\CRadianDIRScript.h>
#include <Script\CMinotauros.h>
#include <Script\CPosSetTargetScript.h>
#include <Script\CSapa.h>
#include <Script/CInvaderScript.h>
#include <Script/CBugMonsterScript.h>
#include <Script/CSpinBulletScript.h>
#include <Script/CDropMissileScript.h>
#include <Script\CObjState.h>
#include <Script\CHitScript.h>
#include <Script\CHiteffectScript.h>
#include <Script\CMonsterScript.h>
#include "CSaveLoadMgr.h"
#include <Script\CPushSmallStoneScript.h>
#include <Script\CHPHarScript.h>
#include <Script\CElecEffectScript.h>
#include <Script\CDamageFontScript.h>
#include <Script\CCutSceneScript.h>
#include <Script\CTouchScript.h>
#include <Script/CObjTileCol.h>
#include <Script\CSoundScript.h>
#include <Script\CBtnScript.h>
#include <Script\CCharacterSelectScript.h>
#define CSIZE 128

void CreateSamplePrefab()
{
	//TileCollsion
	CGameObject* pObject = new CGameObject;
	pObject->AddComponent(new CTransform);
	pObject->AddComponent(new CCollider2D);
	pObject->AddComponent(new CTileCollsion);

	pObject->Transform()->SetLocalScale(Vec3(TileSize_X, TileSize_Y, 400.f));


	Ptr<CPrefab> pPrefab = new CPrefab(pObject);
	pPrefab->Save(L"prefab\\TileCollsion.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"TileCollsion", pPrefab);
	
	//===============
// Button object (빨간버튼)
// ===============
	CGameObject* redbutton = new CGameObject;
	redbutton->SetName(L"RedButton");////////

	redbutton->AddComponent(new CTransform);
	redbutton->AddComponent(new CMeshRender);
	redbutton->AddComponent(new CCollider2D);
	redbutton->AddComponent(new CRedButtonScript);////////
	redbutton->AddComponent(new CObjEventScript);
	redbutton->Transform()->SetLocalScale(Vec3(40.f, 40.f, 1.f));
	redbutton->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	redbutton->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	redbutton->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"RedButtonMtrl"));////////

	redbutton->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(redbutton);

	pPrefab->Save(L"prefab\\redbutton.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"redbutton", pPrefab);

	//// ===============
	//// stonedoor object (열리는 돌문)
	//// ===============
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"StoneDoor");//////////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CStoneDoorScript);////////
	pObj->AddComponent(new CObjEventScript);
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"StoneDoorMtrl"));////////////

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.5f));
	//pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, 8.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 48.f));
	pPrefab->Save(L"prefab\\StoneDoor.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"StoneDoor", pPrefab);

	//// ===============
	//// push stone object (미는 장애물)
	//// ===============
	pObj = new CGameObject;
	pObj->SetName(L"PushStone"); /////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CPushStoneScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(128, 160, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PushStoneMtrl"));/////

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -16.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 48.f));
	pPrefab->Save(L"prefab\\PushStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"PushStone", pPrefab);

	//// ===============
	//// push Small stone object (미는 장애물) 작은거
	//// ===============
	pObj = new CGameObject;
	pObj->SetName(L"PushSmallStone"); /////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CPushSmallStoneScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PushSmallStoneMtrl"));/////

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.9f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -7.f));


	// 연기 이펙트 (미는바위)
	Ptr<CTexture> pushtex = CResMgr::GetInst()->FindRes<CTexture>(L"smoke"); //42.6  43 9
	CGameObject* pushchildobj = new CGameObject;
	pushchildobj->SetName(L"PushEffect");
	pushchildobj->AddComponent(new CTransform);
	pushchildobj->AddComponent(new CMeshRender);
	pushchildobj->AddComponent(new CAnimator2D);

	pushchildobj->Transform()->SetLocalScale(Vec3(1.f, 0.5f, 1.f));
	pushchildobj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pushchildobj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SmokeEffectMtrl"));/////
	pushchildobj->Animator2D()->CreateAnimation(L"NONE", pushtex, Vec2(0.f, 0.f), Vec2(1.f, 1.f), 1, 1.f);//25630
	pushchildobj->Animator2D()->CreateAnimation(L"SMOKE", pushtex, Vec2(0.f, 0.f), Vec2(42.6f, 43.f), 9, 0.07f);//25630
	pushchildobj->Animator2D()->PlayAnimation(L"NONE", false);
	CScript::AddChild(pObj, pushchildobj);

	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\PushSmallStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"PushSmallStone", pPrefab);


	//// ===============
	//// Speed Up Board ( 스피드 업 발판 )
	//// ===============
	pObj = new CGameObject;
	pObj->SetName(L"SpeedUp"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CSpeedUpScript); ////
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SpeedUpMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SpeedUp.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SpeedUp", pPrefab);

	// ===============
	// Barbed Block (가시 있는 장애물)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BarbedBlock"); /////

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBarbedBlockScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BarbedBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -8.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\BarbedBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BarbedBlock", pPrefab);


	// ===============
	// Block (일반 장애물)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Block"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBlockScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(64, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.8f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -8.f));

	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\Block.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Block", pPrefab);



	// ===============
	// BreakableStone (부술 수 있는 돌)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BreakableStone"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBreakableStoneScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BreakableStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BreakableStone", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"BreakableSmallStone"); ///// 작은거
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBreakableStoneScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BreakableStoneMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BreakableSmallStone.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BreakableSmallStone", pPrefab);

	// ===============
	// BombFlower (폭탄꽃)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BombFlower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombFlowerScript); ////
	pObj->AddComponent(new CTileCollsion);  //***************************************

	pObj->Transform()->SetLocalScale(Vec3(60, 80, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->SetOffSet(Vec2(0.f, 40.f));
	pPrefab->Save(L"prefab\\BombFlower.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BombFlower", pPrefab);

	// ===============
	// Bomb (폭탄)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Bomb"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CBombScript); ////
	pObj->Transform()->SetLocalScale(Vec3(40, 50, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	//pObj->Collider2D()->SetvOffsetScale(Vec2(2.f, 1.5f));

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Bomb.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Bomb", pPrefab);  //5번 레이어


	// ===============
	// FireWood (장작)   
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireWood"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CTileCollsion);  //***************************************
	pObj->AddComponent(new CObjTileCol);
	pObj->AddComponent(new CObjEventScript);
	pObj->AddComponent(new CFireWoodScript); ////
	pObj->Transform()->SetLocalScale(Vec3(42, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireWoodMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	Ptr<CTexture> pSmokeTex = CResMgr::GetInst()->FindRes<CTexture>(L"Burn");

	CGameObject* pChildObj = new CGameObject;
	pChildObj->SetName(L"FireWoodChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->Transform()->SetLocalScale(Vec3(1.1, 1.5, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0.f, 0.7f, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	pChildObj->Animator2D()->CreateAnimation(L"NONE", pSmokeTex, Vec2(0.f, 0.f), Vec2(0.f, 1.f), 5, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"NONE", true);

	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireWood.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireWood", pPrefab);

	// ===============
	//  FireBowl (화로)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"FireBowl"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CFireBowlScript); ////
	pObj->Transform()->SetLocalScale(Vec3(60, 60, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	// 불 애니메이션
	pChildObj = new CGameObject;
	pChildObj->SetName(L"FireBowlChild");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CAnimator2D);
	pChildObj->Transform()->SetLocalScale(Vec3(1, 2, 0.f));
	pChildObj->Transform()->SetLocalPos(Vec3(0, 0.63, -1.f));
	//pChildObj->Transform()->SetLocalPos(Vec3(0, 0.63, 0.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));/////
	pChildObj->Animator2D()->CreateAnimation(L"BURN", pSmokeTex, Vec2(0.f, 0.f), Vec2(64.f, 128.f), 32, 0.1f);
	pChildObj->Animator2D()->PlayAnimation(L"BURN", true);

	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireBowl.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireBowl", pPrefab);



	// ===============
	// EndBlock (ENd Block)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"EndBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CEndBlockScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalPos(Vec3(0.f, -210.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(150, 200, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"EndBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.5f));
	pObj->Collider2D()->SetvOffsetPos(Vec2(0.f, -50.f));


	// end block 자식 ( effect )
	Ptr<CTexture> endtex = CResMgr::GetInst()->FindRes<CTexture>(L"smoke"); /////////////////////////////////
	CGameObject* endchildobj = new CGameObject;
	endchildobj->SetName(L"EndSmokeEffect");
	endchildobj->AddComponent(new CTransform);
	endchildobj->AddComponent(new CMeshRender);
	endchildobj->AddComponent(new CAnimator2D);
	endchildobj->Transform()->SetLocalScale(Vec3(1.f, 0.5f, 1.f));
	endchildobj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	endchildobj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SmokeEffectMtrl"));////////////////////////////////
	endchildobj->Animator2D()->CreateAnimation(L"NONE", endtex, Vec2(0.f, 0.f), Vec2(1.f, 1.f), 1, 1.f);//25630
	endchildobj->Animator2D()->CreateAnimation(L"SMOKE", endtex, Vec2(0.f, 0.f), Vec2(42.6f, 43.f), 9, 0.07f);//25630
	endchildobj->Animator2D()->PlayAnimation(L"NONE", false);
	CScript::AddChild(pObj, endchildobj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EndBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EndBlock", pPrefab);

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

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\JumpUp.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"JumpUp", pPrefab);

	// ===============
	// Elec Tower (전기 생성 탑)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecTower"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecTowerScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalPos(Vec3(-288.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecTowerMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));

	// Elec Tower (자식)
	pChildObj = new CGameObject;
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
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ElecTower.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ElecTower", pPrefab);


	// ===============
	// Elec Block (전기 블록)
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"ElecBlock"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecBlockScript); ////
	pObj->AddComponent(new CTileCollsion);
	pObj->AddComponent(new CObjTileCol);
	pObj->Transform()->SetLocalPos(Vec3(-32.f, -88.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(64, 64, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ElecBlock.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ElecBlock", pPrefab);






	pObj = new CGameObject;
	pObj->SetName(L"TargetSearch");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CTargetSearchScript);
	pObj->Transform()->SetLocalScale(Vec3(2.5f, 2.5f, 1.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\TargetSearch.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"TargetSearch", pPrefab);
	

	Ptr<CTexture> pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar_Green");
	pObj = new CGameObject;
	pObj->SetName(L"HPBar_Green");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPGreenMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\HPBar_Green.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"HPBar_Green", pPrefab);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar_Red");
	pObj = new CGameObject;
	pObj->SetName(L"HPBar_Red");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPRedMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\HPBar_Red.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"HPBar_Red", pPrefab);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar_Skyblue");
	pObj = new CGameObject;
	pObj->SetName(L"HPBar_Skyblue");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPSkyBlueMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\HPBar_Skyblue.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"HPBar_Skyblue", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pObj = new CGameObject;
	pObj->SetName(L"HPBar");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CHPHarScript);
	pObj->Transform()->SetLocalPosY(-0.17f);
	pObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\HPBar.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"HPBar", pPrefab);


	//Character
	// ===============
	//  Marina 마리나    ------------------------------------------------------------------------------------------------------------------------------------------------ 마리나
	// ===============

	pObj = new CGameObject;
	pObj->SetName(L"Marina");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina");

	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture,			  Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture,		  Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2", m_pTexture,		  Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP3", m_pTexture,		  Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP4", m_pTexture,		  Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP", m_pTexture,	  Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP", m_pTexture,		      Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP", m_pTexture,           Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP", m_pTexture,	      Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP", m_pTexture,       Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP", m_pTexture,           Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_UP", m_pTexture,         Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 15, 0.03f);
																							 				 
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture,        Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1", m_pTexture,     Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 22, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture,     Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3", m_pTexture,     Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT4", m_pTexture,     Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT", m_pTexture,        Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT", m_pTexture,         Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT", m_pTexture,       Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT", m_pTexture,        Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT", m_pTexture,    Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture,   Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT", m_pTexture,    Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT", m_pTexture,        Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_RIGHT", m_pTexture,      Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 15, 0.03f);
																							 				 
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture,         Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture,      Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture,      Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3", m_pTexture,      Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN4", m_pTexture,      Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN", m_pTexture,    Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN", m_pTexture,          Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN", m_pTexture,         Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN", m_pTexture,     Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN", m_pTexture,     Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN", m_pTexture,         Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_DOWN", m_pTexture,       Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 15, 0.03f);
																											 
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture,         Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1", m_pTexture,      Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 22, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture,      Vec2(0.f, 256.f * 40), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3", m_pTexture,      Vec2(0.f, 256.f * 41), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT4", m_pTexture,      Vec2(0.f, 256.f * 42), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT", m_pTexture,         Vec2(0.f, 256.f * 43), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT", m_pTexture,          Vec2(0.f, 256.f * 44), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT", m_pTexture,        Vec2(0.f, 256.f * 45), Vec2(256.f, 256.f), 15, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT", m_pTexture,         Vec2(0.f, 256.f * 46), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT", m_pTexture,     Vec2(0.f, 256.f * 47), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT", m_pTexture,    Vec2(0.f, 256.f * 48), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT", m_pTexture,     Vec2(0.f, 256.f * 49), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT", m_pTexture,         Vec2(0.f, 256.f * 50), Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL2_LEFT", m_pTexture,       Vec2(0.f, 256.f * 51), Vec2(256.f, 256.f), 15, 0.03f, true);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);


	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.5f, 2.5f, 1.f));
	CScript::AddChild(pObj, pChildObj);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBar");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());



	CScript::AddChild(pObj, pChildObj);


	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Marina.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Marina", pPrefab);

	// Effect
	// ===============
	// Marina Attack
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"MarinaAttack"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP1", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN1", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT1", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.033f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT1", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.033f);

	pObj->Animator2D()->CreateAnimation(L"Attack_UP3", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN3", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT3", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT3", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack2");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP2", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN2", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT2", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT2", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Attack3");

	pObj->Animator2D()->CreateAnimation(L"Attack_UP4", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN4", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT4", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.015f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT4", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.015f);

	pObj->Animator2D()->PlayAnimation(L"Attack_UP1");

	CMissileScript* Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	CHitScript* Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetbHitDeleteOn(false);
	Hit->SetCCType(CC::NONE);
	Hit->SetType(ObjType::Player);
	Missile->SetTime(0.66f);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaAttack.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaAttack", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"MarinaAttackeffect"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Hiteffect");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(117.f, 102.f), 15, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect",false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaAttackeffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaAttackeffect", pPrefab);




	// ===============
	// Marina Skill
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"MarinaSkill"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CPlayerPosSetScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Skill1");

	pObj->Animator2D()->CreateAnimation(L"Skill", m_pTexture, Vec2(0.f, 0.f ), Vec2(128.f, 128.f), 95, 0.03125f);
	pObj->Animator2D()->PlayAnimation(L"Skill");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	
	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetCCType(CC::DOWN);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetCCValue(10.f);
	Hit->SetfDamageTime(0.3f);
	Hit->SetType(ObjType::Player);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaSkill1", pPrefab);

	// ===============
	// Marina Skill2
	// ===============
	pObj = new CGameObject;

	pObj->SetName(L"MarinaSkill2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Transform()->SetLocalScale(Vec3(96.f, 128.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Marina_SkillMtrl"));/////Std2DMtrl SkillMtrl
	CTargetToAuto* Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(800.f);

	
	Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Skill2");
	Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"Marina_SkillMtrl");
	pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());
	
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);
	
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaSkill2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaSkill2", pPrefab);



	pObj = new CGameObject;
	pObj->SetName(L"MarinaAttackeffect2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Marina_Hiteffect2");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(72.f, 72.f), 31, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MarinaAttackeffect2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MarinaAttackeffect2", pPrefab);
	
	// ===============
	//   Nari 나리    ------------------------------------------------------------------------------------------------------------------------------------------------ 나리
	// ===============

	pObj = new CGameObject;
	pObj->SetName(L"Nari");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari");
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",		m_pTexture, Vec2(0.f, 256.f * 0),  Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1",	m_pTexture, Vec2(0.f, 256.f * 1),  Vec2(256.f, 256.f), 16, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT",		m_pTexture, Vec2(0.f, 256.f * 2),  Vec2(256.f, 256.f), 10, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 3),  Vec2(256.f, 256.f), 11, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT",		m_pTexture, Vec2(0.f, 256.f * 4),  Vec2(256.f, 256.f), 55, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT",		m_pTexture, Vec2(0.f, 256.f * 5),  Vec2(256.f, 256.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT",		m_pTexture, Vec2(0.f, 256.f * 6),  Vec2(256.f, 256.f), 19, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT",m_pTexture, Vec2(0.f, 256.f * 7),  Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT",		m_pTexture, Vec2(0.f, 256.f * 8),  Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 9),  Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",			m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1",		m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP",	m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP",			m_pTexture, Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP",			m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_UP",		m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP",			m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP",		m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP",		m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1",	m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 55, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT",m_pTexture,Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT",	m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT",	m_pTexture, Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN",		m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1",	m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN",		m_pTexture, Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_DOWN",		m_pTexture, Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN",		m_pTexture, Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN",		m_pTexture, Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 18, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);
	CPlayerScript* Player = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player->SetCharacter(Character::NARI);

	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.5f, 2.5f, 1.f));
	CScript::AddChild(pObj, pChildObj);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBar");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Nari.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Nari", pPrefab);

	// ===============
	// Nari Attack
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariAttack"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack1");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);

	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);
	Auto->SetCoSetPos(Vec2(20.f, 20.f));


	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttack1", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"NariAttackeffect"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Hiteffect");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f), 21, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\NariAttackeffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttackeffect", pPrefab);


	// ===============
	// Nari Attack2
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariAttack2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 37.f*2.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack2");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);
	

	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);
	Auto->SetCoSetPos(Vec2(25.f, 25.f));
	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttack2", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"NariAttackeffect2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Hiteffect2");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f), 21, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\NariAttackeffect2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttackeffect2", pPrefab);

	// ===============
	// Nari SKill
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"NariSkill"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(96.f, 64.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Skill1", m_pTexture, Vec2(0.f, 37.f * 1.f), Vec2(62.f, 37.f), 32, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Skill1");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(200.f);
	Auto->SetCoSetPos(Vec2(20.f, 20.f));

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);
	Hit->SetCCType(CC::INJURE);
	Hit->SetCCValue(8);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\NariSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariSkill1", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"NariAttackeffect3"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Nari_Hiteffect3");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(70.f, 70.f), 21, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\NariAttackeffect3.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"NariAttackeffect3", pPrefab);

	// ===============
	// Eva 에바    ------------------------------------------------------------------------------------------------------------------------------------------------ 에바
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Eva");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0., 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva");
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",		m_pTexture, Vec2(0.f, 256.f * 0),  Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1",	m_pTexture, Vec2(0.f, 256.f * 1),  Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2",	m_pTexture, Vec2(0.f, 256.f * 2),  Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3",	m_pTexture, Vec2(0.f, 256.f * 3),  Vec2(256.f, 256.f), 36, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT",		m_pTexture, Vec2(0.f, 256.f * 4),  Vec2(256.f, 256.f), 11, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT",		m_pTexture, Vec2(0.f, 256.f * 5),  Vec2(256.f, 256.f), 18, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 6),  Vec2(256.f, 256.f), 16, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT",		m_pTexture, Vec2(0.f, 256.f * 7),  Vec2(256.f, 256.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT",m_pTexture, Vec2(0.f, 256.f * 8),  Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT",		m_pTexture, Vec2(0.f, 256.f * 9),  Vec2(256.f, 256.f), 21, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 17, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT",	m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 21, 0.03f, true);																			  
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",			m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1",		m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2",		m_pTexture, Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP3",		m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 36, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP",	m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP",			m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP",			m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP",		m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP",		m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP",			m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 18, 0.03f);																		  
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1",	m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2",	m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3",	m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 36, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 18, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT",m_pTexture,Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT",		m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 23, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT",	m_pTexture, Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT",	m_pTexture, Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 21, 0.03f);																		  
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN",		m_pTexture, Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 17, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1",	m_pTexture, Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2",	m_pTexture, Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3",	m_pTexture, Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 19, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN",		m_pTexture, Vec2(0.f, 256.f * 40), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN",		m_pTexture, Vec2(0.f, 256.f * 41), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 42), Vec2(256.f, 256.f), 9, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN",	m_pTexture, Vec2(0.f, 256.f * 43), Vec2(256.f, 256.f), 11, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN",		m_pTexture, Vec2(0.f, 256.f * 44), Vec2(256.f, 256.f), 10, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"STOP_DOWN", true);
	CPlayerScript* Player1 = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player1->SetCharacter(Character::EVA);

	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.5f, 2.5f, 1.f));
	CScript::AddChild(pObj, pChildObj);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBar");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Eva.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Eva", pPrefab);


	// ===============
	// Eva Attack1
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"EvaAttack1"); 
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(150.f, 70.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva_Attack1"); 

	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(69.f, 35.f), 25, 0.01f);
	pObj->Animator2D()->PlayAnimation(L"Attack1");
	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(5.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(300.f);
	Auto->SetCoSetPos(Vec2(30.f, 30.f));

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EvaAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EvaAttack1", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"EvaAttackeffect"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva_Hiteffect");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(147.f, 135.f), 27, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EvaAttackeffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EvaAttackeffect", pPrefab);

	// ===============
	// Eva Attack2
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"EvaAttack2");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(200.f, 70.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva_Attack2");
	pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 0.f), Vec2(128.f, 68.f), 30, 0.03f);
	//pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 0.f), Vec2(117.f, 65.f), 28, 0.03f); xxx
	pObj->Animator2D()->PlayAnimation(L"Attack2");
	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(5.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);

	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(300.f);
	Auto->SetCoSetPos(Vec2(40.f, 40.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EvaAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EvaAttack2", pPrefab);


	// ===============
	// Eva 스킬 
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"EvaSkill1"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(204.f, 256.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.5f, 0.5f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Eva_Skill1");

	pObj->Animator2D()->CreateAnimation(L"Skill", m_pTexture, Vec2(0.f, 0.f), Vec2(204.f, 256.f), 88, 0.03125f);
	pObj->Animator2D()->PlayAnimation(L"Skill");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);


	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetCCType(CC::AIRBORNE);
	Hit->SetfDamageTime(0.3f);
	Hit->SetCCValue(10);
	
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\EvaSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"EvaSkill1", pPrefab);


	// ===============
	//  Garam  가람   ------------------------------------------------------------------------------------------------------------------------------------------------ 가람
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Garam");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"PlayerMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Garam");

	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN",		m_pTexture, Vec2(0.f,256.f * 0),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1",	m_pTexture, Vec2(0.f,256.f * 1),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_DOWN",		m_pTexture, Vec2(0.f,256.f * 2),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_DOWN",		m_pTexture, Vec2(0.f,256.f * 3),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_DOWN",		m_pTexture, Vec2(0.f,256.f * 4),  Vec2(256.f, 256.f), 26, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_DOWN",	m_pTexture, Vec2(0.f,256.f * 5),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_DOWN",	m_pTexture, Vec2(0.f,256.f * 6),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_DOWN",	m_pTexture, Vec2(0.f,256.f * 7),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_DOWN",		m_pTexture, Vec2(0.f,256.f * 8),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",		m_pTexture, Vec2(0.f,256.f * 9),  Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1",	m_pTexture, Vec2(0.f,256.f * 10), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_RIGHT", m_pTexture, Vec2(0.f,256.f * 11), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_RIGHT",		m_pTexture, Vec2(0.f,256.f * 12), Vec2(256.f, 256.f), 29, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_RIGHT",		m_pTexture, Vec2(0.f,256.f * 13), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_RIGHT",m_pTexture,Vec2(0.f,256.f * 14), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_RIGHT",		m_pTexture, Vec2(0.f,256.f * 15), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_RIGHT",		m_pTexture, Vec2(0.f,256.f * 16), Vec2(256.f, 256.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_RIGHT",	m_pTexture, Vec2(0.f,256.f * 17), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_RIGHT",	m_pTexture, Vec2(0.f,256.f * 18), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_RIGHT",		m_pTexture, Vec2(0.f,256.f * 19), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",		m_pTexture, Vec2(0.f,256.f * 20), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1",	m_pTexture, Vec2(0.f,256.f * 21), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_LEFT",	m_pTexture, Vec2(0.f,256.f * 22), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"DEAD_LEFT",		m_pTexture, Vec2(0.f,256.f * 23), Vec2(256.f, 256.f), 29, 0.04f, true);  //x
	pObj->Animator2D()->CreateAnimation(L"RUN_LEFT",		m_pTexture, Vec2(0.f,256.f * 24), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"LINKEDSKILL_LEFT",m_pTexture, Vec2(0.f,256.f * 25), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"STOP_LEFT",		m_pTexture, Vec2(0.f,256.f * 26), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"SKILL_LEFT",		m_pTexture, Vec2(0.f,256.f * 27), Vec2(256.f, 256.f), 30, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_LEFT",	m_pTexture, Vec2(0.f,256.f * 28), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_LEFT",	m_pTexture, Vec2(0.f,256.f * 29), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"PUSH_LEFT",		m_pTexture, Vec2(0.f,256.f * 30), Vec2(256.f, 256.f), 10, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",			m_pTexture, Vec2(0.f,256.f * 31), Vec2(256.f, 256.f), 9, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1",		m_pTexture, Vec2(0.f,256.f * 32), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"RUN_UP",			m_pTexture, Vec2(0.f,256.f * 33), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOP_UP",			m_pTexture, Vec2(0.f,256.f * 34), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SKILL_UP",		m_pTexture, Vec2(0.f,256.f * 35), Vec2(256.f, 256.f), 26, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALKBOMB_UP",		m_pTexture, Vec2(0.f,256.f * 36), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THROWBOMB_UP",	m_pTexture, Vec2(0.f,256.f * 37), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"STOPBOMB_UP",		m_pTexture, Vec2(0.f,256.f * 38), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"PUSH_UP",			m_pTexture, Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 10, 0.04f);
	pObj->Animator2D()->PlayAnimation(L"WALKBOMB_RIGHT", true);
	CPlayerScript* Player2 = (CPlayerScript*)pObj->GetScript(L"CPlayerScript");
	Player2->SetCharacter(Character::GARAM);

	pChildObj = new CGameObject;
	pChildObj->SetName(L"TargetSearch");

	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CCollider2D);
	pChildObj->AddComponent(new CTargetSearchScript);
	pChildObj->Transform()->SetLocalScale(Vec3(2.5f, 2.5f, 1.f));
	CScript::AddChild(pObj, pChildObj);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBar");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	CScript::AddChild(pObj, pChildObj);


	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Garam.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Garam", pPrefab);

	
	
	

	
	// ===============
	// Garam Attack1
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"GaramAttack1");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Garam_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack_LEFT1", m_pTexture, Vec2(0.f, 256.f), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"Attack_RIGHT1", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"Attack_UP1", m_pTexture, Vec2(0.f, 256.f*3), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"Attack_DOWN1", m_pTexture, Vec2(0.f, 256.f*2), Vec2(256.f, 256.f), 35, 0.03f);

	//pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(270.f, 176.f), 32, 0.01f);
	pObj->Animator2D()->PlayAnimation(L"Attack_DOWN1");
	
	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(1.05f);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\GaramAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"GaramAttack1", pPrefab);

	pObj = new CGameObject;

	pObj->SetName(L"GaramAttack2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Transform()->SetLocalScale(Vec3(384.f, 256.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.2f, 0.2f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////Std2DMtrl SkillMtrl

	pTex = CResMgr::GetInst()->FindRes<CTexture>(L"Garam_Attack2");

	pObj->Animator2D()->CreateAnimation(L"Arrow", pTex, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.03f);
	

	//pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(270.f, 176.f), 32, 0.01f);
	pObj->Animator2D()->PlayAnimation(L"Arrow");

	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(800.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(2.0f);

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\GaramAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"GaramAttack2", pPrefab);




	pObj = new CGameObject;
	pObj->SetName(L"GaramAttackeffect"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Garam_Hiteffect");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(146.f, 144.f), 28, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\GaramAttackeffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"GaramAttackeffect", pPrefab);


	// ===============
	// Garam Skill 1
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"GaramSkill1"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f*4.f, 128.f * 4.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Garam_Skill1");

	pObj->Animator2D()->CreateAnimation(L"Skill", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 56, 0.03125f);
	pObj->Animator2D()->PlayAnimation(L"Skill",false);


	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\GaramaSkill1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"GaramSkill1", pPrefab);


	//////////////
	pObj = new CGameObject;
	pObj->SetName(L"GaramSkill2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f, 230.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.7f, 0.5f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////Std2DMtrl SkillMtrl

	pTex = CResMgr::GetInst()->FindRes<CTexture>(L"Garam_Skill2");

	pObj->Animator2D()->CreateAnimation(L"Skill", pTex, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 52, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Skill");

	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(800.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Player);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(false);
	Hit->SetCCType(CC::DOWN);
	Hit->SetCCValue(35);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(2.0f);

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\GaramSkill2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"GaramSkill2", pPrefab);


	
	
	pObj = new CGameObject;
	pObj->SetName(L"Minotauros");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMinotauros);
	pObj->AddComponent(new CMonsterScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Mino");
																											   
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP", m_pTexture, Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_UP", m_pTexture, Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP_UP", m_pTexture, Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP", m_pTexture, Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP", m_pTexture, Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture, Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 40, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT", m_pTexture, Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 38, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_RIGHT", m_pTexture, Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLP_RIGHT", m_pTexture, Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGE_RIGHT", m_pTexture, Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADY_RIGHT", m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADYLP_RIGHT", m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT", m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT", m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture, Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 40, 0.03f);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT", m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 38, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_LEFT", m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLP_LEFT", m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 6, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGE_LEFT", m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADY_LEFT", m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CHARGEREADYLP_LEFT", m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT", m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT", m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 40, 0.03f, true);

	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN", m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_DOWN", m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP_DOWN", m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 6, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN", m_pTexture, Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD_DOWN", m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 45, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWEND_DOWN", m_pTexture, Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 10, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"THROWSTART_DOWN", m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 40, 0.03f);

	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");

	CMonsterScript* MonsterSc = (CMonsterScript*)pObj->GetScript(L"CMonsterScript");
	MonsterSc->SetmMonster(Monster::MINO);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBarMonster");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	CHPHarScript* HpMonster = (CHPHarScript*)pChildObj->GetScript(L"CHPHarScript");
	HpMonster->SetPlayer(false);
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Mino.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Mino", pPrefab);
	
	


	// ===============
	// Mino Effect
	// ===============

	//Mino Fireball
	pObj = new CGameObject;
	pObj->SetName(L"MinoFireball"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CRadianDIRScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(350.f, 350.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.1f, 0.1f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"MinoFireball");

	pObj->Animator2D()->CreateAnimation(L"Fireball", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.05f);
	pObj->Animator2D()->PlayAnimation(L"Fireball");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(true);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\MinoFireball.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MinoFireball", pPrefab);

	//Mino Wave
	pObj = new CGameObject;
	pObj->SetName(L"MinoWave"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CRadianDIRScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(1024.f, 1024.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.5f, 0.5f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);


	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"MInoWave");

	pObj->Animator2D()->CreateAnimation(L"WaveUp", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 20, 0.1f);
	pObj->Animator2D()->CreateAnimation(L"WaveLeft", m_pTexture, Vec2(0.f, 256.f * 1.f), Vec2(256.f, 256.f), 20, 0.1f);
	pObj->Animator2D()->CreateAnimation(L"WaveDown", m_pTexture, Vec2(0.f, 256.f * 2.f), Vec2(256.f, 256.f), 20, 0.1f);
	pObj->Animator2D()->CreateAnimation(L"WaveRight", m_pTexture, Vec2(0.f, 256.f * 3.f), Vec2(256.f, 256.f), 20, 0.1f);
	pObj->Animator2D()->PlayAnimation(L"WaveUp");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(2.0f);

	CRadianDIRScript* Dir = (CRadianDIRScript*)pObj->GetScript(L"CRadianDIRScript");

	Dir->SetSpeed(500.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(false);
	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\MinoWave.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MinoWave", pPrefab);








	pObj = new CGameObject;
	pObj->SetName(L"Sapa");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CSapa);
	pObj->AddComponent(new CMonsterScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Sapa");

	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1", m_pTexture,               Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BACK_UP", m_pTexture,                  Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_UP", m_pTexture,             Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP", m_pTexture,               Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_UP", m_pTexture,             Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP", m_pTexture,                  Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_UP", m_pTexture,                Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_UP", m_pTexture,               Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP", m_pTexture,                  Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKEFFECT_RIGHT", m_pTexture,       Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2", m_pTexture,            Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT3", m_pTexture,            Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_RIGHT3", m_pTexture,       Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY2_RIGHT3", m_pTexture,      Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_RIGHT", m_pTexture,          Vec2(0.f, 256.f * 14), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT2", m_pTexture,           Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT3", m_pTexture,           Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT1", m_pTexture,           Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_RIGHT", m_pTexture,          Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT", m_pTexture,               Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_RIGHT", m_pTexture,             Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_RIGHT", m_pTexture,              Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 9, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_RIGHT", m_pTexture,            Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SIDE_RIGHT", m_pTexture,               Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT", m_pTexture,               Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKEFFECT_LEFT", m_pTexture,        Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2", m_pTexture,             Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT3", m_pTexture,             Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 25, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY_LEFT3", m_pTexture,        Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY2_LEFT3", m_pTexture,       Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 25, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"CICLEWAVE_LEFT", m_pTexture,           Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT2", m_pTexture,            Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT3", m_pTexture,            Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT1", m_pTexture,            Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 5, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_LEFT", m_pTexture,           Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 20, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT", m_pTexture,                Vec2(0.f, 256.f * 35), Vec2(256.f, 256.f), 40, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_LEFT", m_pTexture,              Vec2(0.f, 256.f * 36), Vec2(256.f, 256.f), 30, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_LEFT", m_pTexture,               Vec2(0.f, 256.f * 37), Vec2(256.f, 256.f), 9, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_LEFT", m_pTexture,             Vec2(0.f, 256.f * 38), Vec2(256.f, 256.f), 8, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"SIDE_LEFT", m_pTexture,                Vec2(0.f, 256.f * 39), Vec2(256.f, 256.f), 1, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT", m_pTexture,                Vec2(0.f, 256.f * 40), Vec2(256.f, 256.f), 35, 0.03f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1", m_pTexture,             Vec2(0.f, 256.f * 41), Vec2(256.f, 256.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2", m_pTexture,             Vec2(0.f, 256.f * 42), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN3", m_pTexture,             Vec2(0.f, 256.f * 43), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN4", m_pTexture,             Vec2(0.f, 256.f * 44), Vec2(256.f, 256.f), 23, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN5", m_pTexture,             Vec2(0.f, 256.f * 45), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"CIRCLEWAVE_DOWN", m_pTexture,          Vec2(0.f, 256.f * 46), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN", m_pTexture,             Vec2(0.f, 256.f * 47), Vec2(256.f, 256.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEATHFIST_DOWN", m_pTexture,           Vec2(0.f, 256.f * 48), Vec2(256.f, 256.f), 25, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"FRONT_DOWN", m_pTexture,               Vec2(0.f, 256.f * 49), Vec2(256.f, 256.f), 1, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN", m_pTexture,                Vec2(0.f, 256.f * 50), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"JINGAK_DOWN", m_pTexture,              Vec2(0.f, 256.f * 51), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"LAUGH_DOWN", m_pTexture,               Vec2(0.f, 256.f * 52), Vec2(256.f, 256.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_DOWN1", m_pTexture,            Vec2(0.f, 256.f * 53), Vec2(256.f, 256.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"ORARUSH_DOWN2", m_pTexture,            Vec2(0.f, 256.f * 54), Vec2(256.f, 256.f), 8, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBEND_DOWN", m_pTexture,             Vec2(0.f, 256.f * 55), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBLOOP_DOWN1", m_pTexture,           Vec2(0.f, 256.f * 56), Vec2(256.f, 256.f), 20, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBLOOP_DOWN2", m_pTexture,           Vec2(0.f, 256.f * 57), Vec2(256.f, 256.f), 40, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"BOMBREADY_DOWN", m_pTexture,           Vec2(0.f, 256.f * 58), Vec2(256.f, 256.f), 15, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN", m_pTexture,                Vec2(0.f, 256.f * 59), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN");


	MonsterSc = (CMonsterScript*)pObj->GetScript(L"CMonsterScript");
	MonsterSc->SetmMonster(Monster::SAPA);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBarMonster");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	HpMonster = (CHPHarScript*)pChildObj->GetScript(L"CHPHarScript");
	HpMonster->SetPlayer(false);
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Sapa.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Sapa", pPrefab);











	// ===============
	// Sapa Effect
	// ===============

	//Telpo
	pObj = new CGameObject;
	pObj->SetName(L"Telpo"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->Transform()->SetLocalScale(Vec3(384.f, 320.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.0f, 0.0f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Telpo");

	pObj->Animator2D()->CreateAnimation(L"Telpo", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 61, 0.015f);
	pObj->Animator2D()->PlayAnimation(L"Telpo",false);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(0.915f);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\Telpo.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Telpo", pPrefab);

	//BobmStart
	pObj = new CGameObject;
	pObj->SetName(L"BobmStart"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f,512.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.0f, 0.0f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"BobmStart");

	pObj->Animator2D()->CreateAnimation(L"BobmStart", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 59, 0.05f);
	pObj->Animator2D()->PlayAnimation(L"BobmStart", false);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(2.95f);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\BobmStart.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BobmStart", pPrefab);

	//Bobm
	pObj = new CGameObject;
	pObj->SetName(L"Bobm"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CPosSetTargetScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);



	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bobm");

	pObj->Animator2D()->CreateAnimation(L"Bobm", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 30, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Bobm");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(5.0f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(true);

	
	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\Bobm.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Bobm", pPrefab);
	
	//Bobm
	pObj = new CGameObject;
	pObj->SetName(L"Jin"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.8f, 0.8f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Jin");

	pObj->Animator2D()->CreateAnimation(L"Jin", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 33, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Jin",false);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(1.0f);
	pPrefab = new CPrefab(pObj);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(false);

	pPrefab->Save(L"prefab\\Jin.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Jin", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"Ora"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(192.f, 128.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetfDamageTime(0.3f);
	pPrefab = new CPrefab(pObj);

	

	pPrefab->Save(L"prefab\\Ora.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Ora", pPrefab);


	/*pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);

	pObj->AddComponent(new CMapScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetLocalScale(Vec3(1000.f, 1000.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));


	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MaptoolRenderMtrl"));
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Background.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Background", pPrefab);
	*/
	//CResMgr::GetInst()->Load<CPrefab>(L"TileCollsion", L"prefab\\TileCollsion.pref");




	// ==============
	// Bug Object
	// ==============
	pObj = new CGameObject;
	pObj->SetName(L"Bug");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CBugMonsterScript);
	pObj->AddComponent(new CMonsterScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256.f * 2, 256.f * 2, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug");

	pObj->Animator2D()->CreateAnimation(L"ATTACK", m_pTexture, Vec2(0.f, 256.f * 0), Vec2(256.f, 256.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADY", m_pTexture, Vec2(0.f, 256.f * 1), Vec2(256.f, 256.f), 35, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACKREADYLOOP", m_pTexture, Vec2(0.f, 256.f * 2), Vec2(256.f, 256.f), 5, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"DEAD", m_pTexture, Vec2(0.f, 256.f * 3), Vec2(256.f, 256.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GROGGY", m_pTexture, Vec2(0.f, 256.f * 4), Vec2(256.f, 256.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IDLE", m_pTexture, Vec2(0.f, 256.f * 5), Vec2(256.f, 256.f), 30, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IN", m_pTexture, Vec2(0.f, 256.f * 6), Vec2(256.f, 256.f), 25, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"OUT1", m_pTexture, Vec2(0.f, 256.f * 7), Vec2(256.f, 256.f), 30, 0.03f); //돌공격 이랑 같이 나옴
	pObj->Animator2D()->CreateAnimation(L"OUT2", m_pTexture, Vec2(0.f, 256.f * 8), Vec2(256.f, 256.f), 35, 0.03f);
	pObj->Animator2D()->CreateAnimation(L"SPIN", m_pTexture, Vec2(0.f, 256.f * 9), Vec2(256.f, 256.f), 7, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SPINCASTLP", m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 5, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"SPINCASTREADY", m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 25, 0.04f);

	pObj->Animator2D()->PlayAnimation(L"IDLE", true);

	MonsterSc = (CMonsterScript*)pObj->GetScript(L"CMonsterScript");
	MonsterSc->SetmMonster(Monster::BUG);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBarMonster");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	 HpMonster = (CHPHarScript*)pChildObj->GetScript(L"CHPHarScript");
	HpMonster->SetPlayer(false);
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Bug.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Bug", pPrefab);


	// ===============
	// Attack 1
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BugAttack1");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CDropMissileScript);
	pObj->Transform()->SetLocalScale(Vec3(136.f, 200.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug_Attack1");

	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(103.f, 148.f), 48, 0.02f);
	pObj->Animator2D()->PlayAnimation(L"Attack1");
	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\BugAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BugAttack1", pPrefab);


	// ===============
	// Attack11 
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"BugAttack11"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CPlayerPosSetScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(250.f, 200.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.5f, 0.5f));



	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug_Attack11");

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetfDamageTime(0.2);
	Hit->SetiDamage(5);


	pObj->Animator2D()->CreateAnimation(L"Attack11", m_pTexture, Vec2(0.f, 0.f), Vec2(150.f, 105.f), 100, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack11");

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(3.f);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BugAttack11.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BugAttack11", pPrefab);


	// ===============
	// Attack 2 가시
	// ===============
	pObj = new CGameObject;
	pObj->SetName(L"Bug_Attack2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->AddComponent(new CSpinBulletScript);
	pObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Bug_Attack2");

	pObj->Animator2D()->CreateAnimation(L"Shoot", m_pTexture, Vec2(0.f, 0.f), Vec2(30.f, 49.f), 1, 1.f);
	pObj->Animator2D()->PlayAnimation(L"Shoot");

	
	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(true);
	
	//Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	//Missile->SetTime(3.f);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BugAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BugAttack2", pPrefab);


	// ===============
	// Invader 인베이더 몬스터
	// ==============


	pObj = new CGameObject;
	pObj->SetName(L"Invader");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CInvaderScript);
	pObj->AddComponent(new CMonsterScript);
	pObj->AddComponent(new CObjState);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(256 * 2.f, 256 * 2.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));

	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"MonsterMtrl"));

	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);
	pObj->Collider2D()->SetvOffsetScale(Vec2(0.25f, 0.25f));

	//Ptr<CTexture> m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader");
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader");

	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP1",		     m_pTexture, Vec2(0.f, 256.f * 0),  Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_UP2",		     m_pTexture, Vec2(0.f, 256.f * 1),  Vec2(256.f, 256.f), 40, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_UP",		     m_pTexture, Vec2(0.f, 256.f * 2),  Vec2(256.f, 256.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_UP",		     m_pTexture, Vec2(0.f, 256.f * 3),  Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURD_UP",		     m_pTexture, Vec2(0.f, 256.f * 4),  Vec2(256.f, 256.f), 1, 0.04f);  //위로 돌진
	pObj->Animator2D()->CreateAnimation(L"IDLE_UP",			     m_pTexture, Vec2(0.f, 256.f * 5),  Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_UP",			     m_pTexture, Vec2(0.f, 256.f * 6),  Vec2(256.f, 256.f), 30, 0.04f);
															     					  					
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN1",	     m_pTexture, Vec2(0.f, 256.f * 7),  Vec2(256.f, 256.f), 20, 0.04f);  //1
	pObj->Animator2D()->CreateAnimation(L"ATTACK_DOWN2",	     m_pTexture, Vec2(0.f, 256.f * 8),  Vec2(256.f, 256.f), 40, 0.04f);   //2 -> 1-> IDLE
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_DOWN",	     m_pTexture, Vec2(0.f, 256.f * 9),  Vec2(256.f, 256.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_DOWN",		     m_pTexture, Vec2(0.f, 256.f * 10), Vec2(256.f, 256.f), 20, 0.04f); //돌진공격 끝나고 대기상태 ->IDLE
	pObj->Animator2D()->CreateAnimation(L"GAURD_DOWN",		     m_pTexture, Vec2(0.f, 256.f * 11), Vec2(256.f, 256.f), 1, 0.04f);   //아래로 돌진
	pObj->Animator2D()->CreateAnimation(L"IDLE_DOWN",		     m_pTexture, Vec2(0.f, 256.f * 12), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"THUNDEREND_DOWN",      m_pTexture, Vec2(0.f, 256.f * 13), Vec2(256.f, 256.f), 30, 0.04f); //공격 끝
	pObj->Animator2D()->CreateAnimation(L"THUNDERSTART_DOWN"     ,m_pTexture, Vec2(0.f,256.f * 14), Vec2(256.f, 256.f), 35, 0.04f); //공격 준비, 시작
	pObj->Animator2D()->CreateAnimation(L"THUNDER2_DOWN",	     m_pTexture, Vec2(0.f, 256.f * 15), Vec2(256.f, 256.f), 6, 0.04f); //공격
	pObj->Animator2D()->CreateAnimation(L"WALK_DOWN",		     m_pTexture, Vec2(0.f, 256.f * 16), Vec2(256.f, 256.f), 35, 0.04f);
															     					  					
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT1",	     m_pTexture, Vec2(0.f, 256.f * 17), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_RIGHT2",	     m_pTexture, Vec2(0.f, 256.f * 18), Vec2(256.f, 256.f), 40, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_RIGHT",	     m_pTexture, Vec2(0.f, 256.f * 19), Vec2(256.f, 256.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_RIGHT",	     m_pTexture, Vec2(0.f, 256.f * 20), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASH_RIGHT",      m_pTexture, Vec2(0.f, 256.f * 21), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASHREADY_RIGHT", m_pTexture, Vec2(0.f, 256.f * 22), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"GAURD_RIGHT",		     m_pTexture, Vec2(0.f, 256.f * 23), Vec2(256.f, 256.f), 1, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"IDLE_RIGHT",		     m_pTexture, Vec2(0.f, 256.f * 24), Vec2(256.f, 256.f), 20, 0.04f);
	pObj->Animator2D()->CreateAnimation(L"WALK_RIGHT",		     m_pTexture, Vec2(0.f, 256.f * 25), Vec2(256.f, 256.f), 30, 0.04f);
															     					  					
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT1",	     m_pTexture, Vec2(0.f, 256.f * 26), Vec2(256.f, 256.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"ATTACK_LEFT2",	     m_pTexture, Vec2(0.f, 256.f * 27), Vec2(256.f, 256.f), 40, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"DAMAGED_LEFT",	     m_pTexture, Vec2(0.f, 256.f * 28), Vec2(256.f, 256.f), 1, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"EMBARR_LEFT",		     m_pTexture, Vec2(0.f, 256.f * 29), Vec2(256.f, 256.f), 20, 0.04f, true);  //돌진 공격 끝나고 윙 ? 상태 -> IDLE
	pObj->Animator2D()->CreateAnimation(L"GAURDDASH_LEFT",	     m_pTexture, Vec2(0.f, 256.f * 30), Vec2(256.f, 256.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"GAURDDASHREADY_LEFT",  m_pTexture, Vec2(0.f, 256.f * 31), Vec2(256.f, 256.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"GAURD_LEFT",		     m_pTexture, Vec2(0.f, 256.f * 32), Vec2(256.f, 256.f), 1, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"IDLE_LEFT",		     m_pTexture, Vec2(0.f, 256.f * 33), Vec2(256.f, 256.f), 20, 0.04f, true);
	pObj->Animator2D()->CreateAnimation(L"WALK_LEFT",		     m_pTexture, Vec2(0.f, 256.f * 34), Vec2(256.f, 256.f), 30, 0.04f, true);

	pObj->Animator2D()->PlayAnimation(L"IDLE_DOWN", true);
	MonsterSc = (CMonsterScript*)pObj->GetScript(L"CMonsterScript");
	MonsterSc->SetmMonster(Monster::INVADER);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"HPBar");
	pChildObj = new CGameObject;
	pChildObj->SetName(L"HPBarMonster");
	pChildObj->AddComponent(new CTransform);
	pChildObj->AddComponent(new CMeshRender);
	pChildObj->AddComponent(new CHPHarScript);
	pChildObj->Transform()->SetLocalPosY(-0.17f);
	pChildObj->Transform()->SetLocalScale(Vec3(0.26f, 0.1f, 1.f));
	pChildObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pChildObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"HPMtrl"));
	pChildObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	HpMonster = (CHPHarScript*)pChildObj->GetScript(L"CHPHarScript");
	HpMonster->SetPlayer(false);
	CScript::AddChild(pObj, pChildObj);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Invader.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Invader", pPrefab);





	// 인베이더 스킬1 (보라 바닥 구체)
	pObj = new CGameObject;
	pObj->SetName(L"InvaderAttack1"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHitScript); 
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(136.f, 200.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader_Attack2"); //160 96

	pObj->Animator2D()->CreateAnimation(L"Attack2none", m_pTexture, Vec2(0.f, 0.f), Vec2(0.1f, 0.1f), 1, 2.f);
	//pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 0.f), Vec2(160.f, 160.f), 96, 0.03f); //ori
	pObj->Animator2D()->CreateAnimation(L"Attack2", m_pTexture, Vec2(0.f, 0.f), Vec2(140.f, 150.f), 104, 0.03f); //140 150 104

	

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetfDamageTime(0.3);

	pPrefab = new CPrefab(pObj);

	pPrefab->Save(L"prefab\\InvaderAttack1.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InvaderAttack1", pPrefab);


	// 스킬 1 이펙트만 (떨어지는것)
	pObj = new CGameObject;
	pObj->SetName(L"InvaderAttack1_effect"); 
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CDropMissileScript);
	pObj->Transform()->SetLocalScale(Vec3(136.f, 200.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader_Attack1"); //136 200 35

	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(136.f, 200.f), 35, 0.03f);   //140150104
	pObj->Animator2D()->PlayAnimation(L"Attack1");
	pPrefab = new CPrefab(pObj);


	pPrefab->Save(L"prefab\\InvaderAttack1_effect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InvaderAttack1_effect", pPrefab);

	//스킬 1 떨어진 후 4방향으로 나가는것
	pObj = new CGameObject;
	pObj->SetName(L"InvaderAttack1_four"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CTargetToAuto);
	pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(200.f, 300.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"Invader_Attack3"); //136 200 35
	pObj->Animator2D()->CreateAnimation(L"Attack1", m_pTexture, Vec2(0.f, 0.f), Vec2(141.f, 90.f), 40, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Attack1", false);

	Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	Missile->SetTime(2.f);
	Auto = (CTargetToAuto*)pObj->GetScript(L"CTargetToAuto");
	Auto->SetSpeed(400.f);

	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(true);
	Hit->SetbHitDeleteOn(true);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\InvaderAttack1_four.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InvaderAttack1_four", pPrefab);



	// 인베이더 스킬2 일반공격
	pObj = new CGameObject;
	pObj->SetName(L"InvaderAttack2"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);

	pObj->AddComponent(new CHitScript);
	pObj->Transform()->SetLocalScale(Vec3(300.f, 300.f, 0.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

	
	Hit = (CHitScript*)pObj->GetScript(L"CHitScript");
	Hit->SetType(ObjType::Monster);
	Hit->SetbDamageColEnter(false);
	Hit->SetbHitDeleteOn(false);
	Hit->SetfDamageTime(0.3f);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\InvaderAttack2.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InvaderAttack2", pPrefab);

	

	pObj = new CGameObject;
	pObj->SetName(L"AttackHit"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(128.f, 128.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"AttackHit");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(99.f, 99.f), 20, 0.05f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\AttackHit.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"AttackHit", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"FireHit"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(192.f, 192.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"FireHit");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 21, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\FireHit.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"FireHit", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"InveHit"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"InveHit");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\InveHit.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InveHit", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"RockHit"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(256.f, 256.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"RockHit");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 16, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\RockHit.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"RockHit", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"SapaHit"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"SapaHit");
	pObj->Animator2D()->CreateAnimation(L"Hiteffect", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 26, 0.03f);
	pObj->Animator2D()->PlayAnimation(L"Hiteffect", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SapaHit.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SapaHit", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"SapaDie"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"SapaDie");
	pObj->Animator2D()->CreateAnimation(L"Die", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.0625f);
	pObj->Animator2D()->PlayAnimation(L"Die", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SapaDie.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SapaDie", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"BugDie"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"BugDie");
	pObj->Animator2D()->CreateAnimation(L"Die", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.0625f);
	pObj->Animator2D()->PlayAnimation(L"Die", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BugDie.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BugDie", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"InveDie"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"InveDie");
	pObj->Animator2D()->CreateAnimation(L"Die", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.0625f);
	pObj->Animator2D()->PlayAnimation(L"Die", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\InveDie.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InveDie", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"MinoDie"); /////
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(512.f, 512.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SkillMtrl"));/////
	m_pTexture = CResMgr::GetInst()->FindRes<CTexture>(L"MinoDie");
	pObj->Animator2D()->CreateAnimation(L"Die", m_pTexture, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 40, 0.0625f);
	pObj->Animator2D()->PlayAnimation(L"Die", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MinoDie.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MinoDie", pPrefab);





	// ========
 // effect
 // ========
 // 연기 이펙트
	Ptr<CTexture> smoketex = CResMgr::GetInst()->FindRes<CTexture>(L"smoke"); //42.6  43 9
	pObj = new CGameObject;
	pObj->SetName(L"SmokeEffect");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(110, 110, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SmokeEffectMtrl"));/////
	pObj->Animator2D()->CreateAnimation(L"SMOKE", smoketex, Vec2(0.f, 0.f), Vec2(42.6f, 43.f), 9, 0.07f);//25630
	pObj->Animator2D()->PlayAnimation(L"SMOKE", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SmokeEffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SmokeEffect", pPrefab);

	//폭발 이펙트
	Ptr<CTexture> bombtex = CResMgr::GetInst()->FindRes<CTexture>(L"explosion"); //42.6  43 9
	pObj = new CGameObject;
	pObj->SetName(L"BombEffect");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(250, 250, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombEffectMtrl"));/////
	pObj->Animator2D()->CreateAnimation(L"BOMB", bombtex, Vec2(0.f, 0.f), Vec2(256.f, 256.f), 30, 0.02f);//25630
	pObj->Animator2D()->PlayAnimation(L"BOMB", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BombEffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BombEffect", pPrefab);



	/// <summary>
/// background img
/// </summary>

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Desert");
	float size_ratio = 0.6;
	pObj = new CGameObject;
	pObj->SetName(L"BackImg_Desert");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(pTe1x->Width()* size_ratio, pTe1x->Height()* size_ratio, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DessertMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BackImg_Desert.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BackImg_Desert", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Dungeon");
	pObj = new CGameObject;
	pObj->SetName(L"BackImg_Dungeon");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(pTe1x->Width()* size_ratio, pTe1x->Height()* size_ratio, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DungeonMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BackImg_Dungeon.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BackImg_Dungeon", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Snack");
	pObj = new CGameObject;
	pObj->SetName(L"BackImg_Snack");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(pTe1x->Width()* size_ratio, pTe1x->Height()* size_ratio, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SnakMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BackImg_Snack.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BackImg_Snack", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Town");
	pObj = new CGameObject;
	pObj->SetName(L"BackImg_Town");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(pTe1x->Width()* size_ratio, pTe1x->Height()* size_ratio, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"TownMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BackImg_Town.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BackImg_Town", pPrefab);




	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"bossback");
	pObj = new CGameObject;
	pObj->SetName(L"bossback");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 480.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BossBackMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\bossback.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"bossback", pPrefab);




	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Select");
	pObj = new CGameObject;
	pObj->SetName(L"Select");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"SelectMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select", pPrefab);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Select_Eva");
	pObj = new CGameObject;
	pObj->SetName(L"Select_Eva");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, -110.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Select_EvaMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select_Eva.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select_Eva", pPrefab);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Select_Marina");
	pObj = new CGameObject;
	pObj->SetName(L"Select_Marina");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, -110.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Select_MarinanMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select_Marina.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select_Marina", pPrefab);

	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Select_Garam");
	pObj = new CGameObject;
	pObj->SetName(L"Select_Garam");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f, -110.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Select_GaramMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select_Garam.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select_Garam", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Select_Nari");
	pObj = new CGameObject;
	pObj->SetName(L"Select_Nari");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->Transform()->SetLocalPos(Vec3(0.f,-110.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(320.f, 500.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Select_NariMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select_Nari.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select_Nari", pPrefab);







	// elec effect
	Ptr<CTexture> m_pText = CResMgr::GetInst()->FindRes<CTexture>(L"eleceffect"); // 100 200 8
	pObj = new CGameObject;
	pObj->SetName(L"ElecEffect");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CElecEffectScript);
	pObj->Transform()->SetLocalScale(Vec3(64, 258, 0.f));
	pObj->Collider2D()->SetvOffsetScale(Vec2(1.f, 0.5f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ElecEffectMtrl"));/////
	pObj->Animator2D()->CreateAnimation(L"NONE", m_pText, Vec2(0.f, 0.f), Vec2(1.f, 1.f), 1, 1.f);
	pObj->Animator2D()->CreateAnimation(L"ELECEFFECT", m_pText, Vec2(0.f, 0.f), Vec2(256.f, 64.f), 16, 0.01f);
	pObj->Animator2D()->PlayAnimation(L"ELECEFFECT", true);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ElecEffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ElecEffect", pPrefab);

	// exp effect
	Ptr<CTexture> exptex = CResMgr::GetInst()->FindRes<CTexture>(L"expeffect"); //100010016
	pObj = new CGameObject;
	pObj->SetName(L"ExpEffect");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHiteffectScript);
	pObj->Transform()->SetLocalScale(Vec3(100, 100, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"ExpEffectMtrl"));///////////////////////////////
	pObj->Animator2D()->CreateAnimation(L"EXPLOSION", exptex, Vec2(0.f, 0.f), Vec2(100.f, 100.f), 16, 0.03f);//25630
	pObj->Animator2D()->PlayAnimation(L"EXPLOSION", false);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\ExpEffect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"ExpEffect", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"DamageFont");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CDamageFontScript);
	pObj->Transform()->SetLocalScale(Vec3(100, 100, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DamageFontMtrl"));///////////////////////////////
	//Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	//Missile->SetTime(2.f);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\DamageFont.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"DamageFont", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"CharacterCutScene");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CMissileScript);
	pObj->AddComponent(new CCutSceneScript);
	pObj->Transform()->SetLocalScale(Vec3(600.f, 300.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 1.2f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"CutSceneMtrl"));///////////////////////////////
	//Missile = (CMissileScript*)pObj->GetScript(L"CMissileScript");
	//Missile->SetTime(2.f);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\CharacterCutScene.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"CharacterCutScene", pPrefab);




	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Main");
	pObj = new CGameObject;
	pObj->SetName(L"Main");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CBtnScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"titleMtrl"));

	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());

	pObj->Animator2D()->CreateAnimation(L"Main", pTe1x, Vec2(0.f, 0.f), Vec2(200.f,113.f), 25, 0.1f);//25630
	pObj->Animator2D()->PlayAnimation(L"Main");

	CBtnScript* Btn = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	Btn->SetPlayerAdd(false);
	Btn->SetSName(L"scene\\BossSelete.scene");
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Main.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Main", pPrefab);



	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"touchtostart");
	pObj = new CGameObject;
	pObj->SetName(L"touchtostart");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CTouchScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(350.f, 50.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"touchtostartMtrl"));
	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\touchtostart.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"touchtostart", pPrefab);



	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"Backspace");
	pObj = new CGameObject;
	pObj->SetName(L"Backspace");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(100.f,100.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BackspaceMtrl"));

	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());

	 Btn = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	Btn->SetPlayerAdd(false);
	Btn->SetSName(L"scene\\BossSelete.scene");
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Backspace.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Backspace", pPrefab);


	pTe1x = CResMgr::GetInst()->FindRes<CTexture>(L"CharacterSelect");
	pObj = new CGameObject;
	pObj->SetName(L"CharacterSelect");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBtnScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0, 400.f));
	pObj->Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"CharacterSelectMtrl"));

	pObj->MeshRender()->GetSharedMaterial()->SetData(SHADER_PARAM::TEX_0, pTe1x.Get());

	Btn = (CBtnScript*)pObj->GetScript(L"CBtnScript");
	Btn->SetPlayerAdd(false);
	Btn->SetSName(L"scene\\characterselect.scene");
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\CharacterSelect.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"CharacterSelect", pPrefab);




	pObj = new CGameObject;
	pObj->SetName(L"Select_Player");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCharacterSelectScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 480.f));
	pObj->Transform()->SetLocalScale(Vec3(1280.f, 720.f, 1.f));
	pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\Select_Player.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"Select_Player", pPrefab);

	// BGM ***************************************************************
	pObj = new CGameObject;
	pObj->SetName(L"bgm");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CSoundScript);
	pObj->Transform()->SetLocalPos(Vec3(0.f, 0.f, 0.f));
	CSoundScript* pSS = (CSoundScript*)pObj->GetScript(L"CSoundScript");
	pSS->SetBgmName(BGM_NAME::NONE);

	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\bgm.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"bgm", pPrefab);



	//CBtnScript
	

	pObj = new CGameObject;
	pObj->SetName(L"MinoBtn");
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
	pScript->SetSName(L"scene\\maze0.scene");
	pScript->SetPlayerAdd(true);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\MinoBtn.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"MinoBtn", pPrefab);

	pObj = new CGameObject;
	pObj->SetName(L"SapaBtn");
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
	pScript1->SetSName(L"scene\\maze1.scene");
	pScript1->SetPlayerAdd(true);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\SapaBtn.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"SapaBtn", pPrefab);


	pObj = new CGameObject;
	pObj->SetName(L"BugBtn");
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
	pScript2->SetSName(L"scene\\maze2.scene");
	pScript2->SetPlayerAdd(true);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\BugBtn.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"BugBtn", pPrefab);



	pObj = new CGameObject;
	pObj->SetName(L"InvaderBtn");
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
	pScript3->SetSName(L"scene\\maze3.scene");
	pScript3->SetPlayerAdd(true);
	pPrefab = new CPrefab(pObj);
	pPrefab->Save(L"prefab\\InvaderBtn.pref");
	CResMgr::GetInst()->AddRes<CPrefab>(L"InvaderBtn", pPrefab);







}
