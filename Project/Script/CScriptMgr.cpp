#include "pch.h"
#include "CScriptMgr.h"

#include "CBarbedBlockScript.h"
#include "CBlockScript.h"
#include "CBombFlowerScript.h"
#include "CBombScript.h"

#include "CBreakableStoneScript.h"
#include "CBtnScript.h"
#include "CBugMonsterScript.h"
#include "CCameraScript.h"
#include "CCharacterSelectScript.h"
#include "CCutSceneScript.h"
#include "CDamageFontScript.h"
#include "CDropMissileScript.h"
#include "CElecBlockScript.h"
#include "CElecChildScript.h"
#include "CElecEffectScript.h"
#include "CElecTowerScript.h"
#include "CEndBlockScript.h"
#include "CFireBowlScript.h"
#include "CFireWoodScript.h"
#include "CFSMScript.h"
#include "CHiteffectScript.h"
#include "CHitScript.h"
#include "CHPHarScript.h"
#include "CInvaderScript.h"
#include "CJumpUpScript.h"
#include "CMapScript.h"
#include "CMinotauros.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CObjEventScript.h"
#include "CObjState.h"
#include "CObjTileCol.h"
#include "CPlayerPosSetScript.h"
#include "CPlayerScript.h"
#include "CPosSetTargetScript.h"
#include "CPushSmallStoneScript.h"
#include "CPushStoneScript.h"
#include "CRadianDIRScript.h"
#include "CRedButtonScript.h"
#include "CSapa.h"
#include "CSoundScript.h"
#include "CSpeedUpScript.h"
#include "CSpinBulletScript.h"
#include "CStoneDoorScript.h"
#include "CTargetSearchScript.h"
#include "CTargetToAuto.h"
#include "CTileCollsion.h"
#include "CTouchScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBarbedBlockScript");
	_vec.push_back(L"CBlockScript");
	_vec.push_back(L"CBombFlowerScript");
	_vec.push_back(L"CBombScript");
	_vec.push_back(L"CBreakableSmallStoneScript");
	_vec.push_back(L"CBreakableStoneScript");
	_vec.push_back(L"CBtnScript");
	_vec.push_back(L"CBugMonsterScript");
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CCharacterSelectScript");
	_vec.push_back(L"CCutSceneScript");
	_vec.push_back(L"CDamageFontScript");
	_vec.push_back(L"CDropMissileScript");
	_vec.push_back(L"CElecBlockScript");
	_vec.push_back(L"CElecChildScript");
	_vec.push_back(L"CElecEffectScript");
	_vec.push_back(L"CElecTowerScript");
	_vec.push_back(L"CEndBlockScript");
	_vec.push_back(L"CFireBowlScript");
	_vec.push_back(L"CFireWoodScript");
	_vec.push_back(L"CFSMScript");
	_vec.push_back(L"CHiteffectScript");
	_vec.push_back(L"CHitScript");
	_vec.push_back(L"CHPHarScript");
	_vec.push_back(L"CInvaderScript");
	_vec.push_back(L"CJumpUpScript");
	_vec.push_back(L"CMapScript");
	_vec.push_back(L"CMinotauros");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CObjEventScript");
	_vec.push_back(L"CObjState");
	_vec.push_back(L"CObjTileCol");
	_vec.push_back(L"CPlayerPosSetScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CPosSetTargetScript");
	_vec.push_back(L"CPushSmallStoneScript");
	_vec.push_back(L"CPushStoneScript");
	_vec.push_back(L"CRadianDIRScript");
	_vec.push_back(L"CRedButtonScript");
	_vec.push_back(L"CSapa");
	_vec.push_back(L"CSoundScript");
	_vec.push_back(L"CSpeedUpScript");
	_vec.push_back(L"CSpinBulletScript");
	_vec.push_back(L"CStoneDoorScript");
	_vec.push_back(L"CTargetSearchScript");
	_vec.push_back(L"CTargetToAuto");
	_vec.push_back(L"CTileCollsion");
	_vec.push_back(L"CTouchScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBarbedBlockScript" == _strScriptName)
		return new CBarbedBlockScript;
	if (L"CBlockScript" == _strScriptName)
		return new CBlockScript;
	if (L"CBombFlowerScript" == _strScriptName)
		return new CBombFlowerScript;
	if (L"CBombScript" == _strScriptName)
		return new CBombScript;

	if (L"CBreakableStoneScript" == _strScriptName)
		return new CBreakableStoneScript;
	if (L"CBtnScript" == _strScriptName)
		return new CBtnScript;
	if (L"CBugMonsterScript" == _strScriptName)
		return new CBugMonsterScript;
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CCharacterSelectScript" == _strScriptName)
		return new CCharacterSelectScript;
	if (L"CCutSceneScript" == _strScriptName)
		return new CCutSceneScript;
	if (L"CDamageFontScript" == _strScriptName)
		return new CDamageFontScript;
	if (L"CDropMissileScript" == _strScriptName)
		return new CDropMissileScript;
	if (L"CElecBlockScript" == _strScriptName)
		return new CElecBlockScript;
	if (L"CElecChildScript" == _strScriptName)
		return new CElecChildScript;
	if (L"CElecEffectScript" == _strScriptName)
		return new CElecEffectScript;
	if (L"CElecTowerScript" == _strScriptName)
		return new CElecTowerScript;
	if (L"CEndBlockScript" == _strScriptName)
		return new CEndBlockScript;
	if (L"CFireBowlScript" == _strScriptName)
		return new CFireBowlScript;
	if (L"CFireWoodScript" == _strScriptName)
		return new CFireWoodScript;
	if (L"CFSMScript" == _strScriptName)
		return new CFSMScript;
	if (L"CHiteffectScript" == _strScriptName)
		return new CHiteffectScript;
	if (L"CHitScript" == _strScriptName)
		return new CHitScript;
	if (L"CHPHarScript" == _strScriptName)
		return new CHPHarScript;
	if (L"CInvaderScript" == _strScriptName)
		return new CInvaderScript;
	if (L"CJumpUpScript" == _strScriptName)
		return new CJumpUpScript;
	if (L"CMapScript" == _strScriptName)
		return new CMapScript;
	if (L"CMinotauros" == _strScriptName)
		return new CMinotauros;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CObjEventScript" == _strScriptName)
		return new CObjEventScript;
	if (L"CObjState" == _strScriptName)
		return new CObjState;
	if (L"CObjTileCol" == _strScriptName)
		return new CObjTileCol;
	if (L"CPlayerPosSetScript" == _strScriptName)
		return new CPlayerPosSetScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CPosSetTargetScript" == _strScriptName)
		return new CPosSetTargetScript;
	if (L"CPushSmallStoneScript" == _strScriptName)
		return new CPushSmallStoneScript;
	if (L"CPushStoneScript" == _strScriptName)
		return new CPushStoneScript;
	if (L"CRadianDIRScript" == _strScriptName)
		return new CRadianDIRScript;
	if (L"CRedButtonScript" == _strScriptName)
		return new CRedButtonScript;
	if (L"CSapa" == _strScriptName)
		return new CSapa;
	if (L"CSoundScript" == _strScriptName)
		return new CSoundScript;
	if (L"CSpeedUpScript" == _strScriptName)
		return new CSpeedUpScript;
	if (L"CSpinBulletScript" == _strScriptName)
		return new CSpinBulletScript;
	if (L"CStoneDoorScript" == _strScriptName)
		return new CStoneDoorScript;
	if (L"CTargetSearchScript" == _strScriptName)
		return new CTargetSearchScript;
	if (L"CTargetToAuto" == _strScriptName)
		return new CTargetToAuto;
	if (L"CTileCollsion" == _strScriptName)
		return new CTileCollsion;
	if (L"CTouchScript" == _strScriptName)
		return new CTouchScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BARBEDBLOCKSCRIPT:
		return new CBarbedBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::BLOCKSCRIPT:
		return new CBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBFLOWERSCRIPT:
		return new CBombFlowerScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBSCRIPT:
		return new CBombScript;
		break;
	
	case (UINT)SCRIPT_TYPE::BREAKABLESTONESCRIPT:
		return new CBreakableStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::BTNSCRIPT:
		return new CBtnScript;
		break;
	case (UINT)SCRIPT_TYPE::BUGMONSTERSCRIPT:
		return new CBugMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::CHARACTERSELECTSCRIPT:
		return new CCharacterSelectScript;
		break;
	case (UINT)SCRIPT_TYPE::CUTSCENESCRIPT:
		return new CCutSceneScript;
		break;
	case (UINT)SCRIPT_TYPE::DAMAGEFONTSCRIPT:
		return new CDamageFontScript;
		break;
	case (UINT)SCRIPT_TYPE::DROPMISSILESCRIPT:
		return new CDropMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECBLOCKSCRIPT:
		return new CElecBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECCHILDSCRIPT:
		return new CElecChildScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECEFFECTSCRIPT:
		return new CElecEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::ELECTOWERSCRIPT:
		return new CElecTowerScript;
		break;
	case (UINT)SCRIPT_TYPE::ENDBLOCKSCRIPT:
		return new CEndBlockScript;
		break;
	case (UINT)SCRIPT_TYPE::FIREBOWLSCRIPT:
		return new CFireBowlScript;
		break;
	case (UINT)SCRIPT_TYPE::FIREWOODSCRIPT:
		return new CFireWoodScript;
		break;
	case (UINT)SCRIPT_TYPE::FSMSCRIPT:
		return new CFSMScript;
		break;
	case (UINT)SCRIPT_TYPE::HITEFFECTSCRIPT:
		return new CHiteffectScript;
		break;
	case (UINT)SCRIPT_TYPE::HITSCRIPT:
		return new CHitScript;
		break;
	case (UINT)SCRIPT_TYPE::HPHARSCRIPT:
		return new CHPHarScript;
		break;
	case (UINT)SCRIPT_TYPE::INVADERSCRIPT:
		return new CInvaderScript;
		break;
	case (UINT)SCRIPT_TYPE::JUMPUPSCRIPT:
		return new CJumpUpScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPSCRIPT:
		return new CMapScript;
		break;
	case (UINT)SCRIPT_TYPE::MINOTAUROS:
		return new CMinotauros;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::OBJEVENTSCRIPT:
		return new CObjEventScript;
		break;
	case (UINT)SCRIPT_TYPE::OBJSTATE:
		return new CObjState;
		break;
	case (UINT)SCRIPT_TYPE::OBJTILECOL:
		return new CObjTileCol;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERPOSSETSCRIPT:
		return new CPlayerPosSetScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::POSSETTARGETSCRIPT:
		return new CPosSetTargetScript;
		break;
	case (UINT)SCRIPT_TYPE::PUSHSMALLSTONESCRIPT:
		return new CPushSmallStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::PUSHSTONESCRIPT:
		return new CPushStoneScript;
		break;
	case (UINT)SCRIPT_TYPE::RADIANDIRSCRIPT:
		return new CRadianDIRScript;
		break;
	case (UINT)SCRIPT_TYPE::REDBUTTONSCRIPT:
		return new CRedButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::SAPA:
		return new CSapa;
		break;
	case (UINT)SCRIPT_TYPE::SOUNDSCRIPT:
		return new CSoundScript;
		break;
	case (UINT)SCRIPT_TYPE::SPEEDUPSCRIPT:
		return new CSpeedUpScript;
		break;
	case (UINT)SCRIPT_TYPE::SPINBULLETSCRIPT:
		return new CSpinBulletScript;
		break;
	case (UINT)SCRIPT_TYPE::STONEDOORSCRIPT:
		return new CStoneDoorScript;
		break;
	case (UINT)SCRIPT_TYPE::TARGETSEARCHSCRIPT:
		return new CTargetSearchScript;
		break;
	case (UINT)SCRIPT_TYPE::TARGETTOAUTO:
		return new CTargetToAuto;
		break;
	case (UINT)SCRIPT_TYPE::TILECOLLSION:
		return new CTileCollsion;
		break;
	case (UINT)SCRIPT_TYPE::TOUCHSCRIPT:
		return new CTouchScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BARBEDBLOCKSCRIPT:
		return L"CBarbedBlockScript";
		break;

	case SCRIPT_TYPE::BLOCKSCRIPT:
		return L"CBlockScript";
		break;

	case SCRIPT_TYPE::BOMBFLOWERSCRIPT:
		return L"CBombFlowerScript";
		break;

	case SCRIPT_TYPE::BOMBSCRIPT:
		return L"CBombScript";
		break;

	case SCRIPT_TYPE::BREAKABLESMALLSTONESCRIPT:
		return L"CBreakableSmallStoneScript";
		break;

	case SCRIPT_TYPE::BREAKABLESTONESCRIPT:
		return L"CBreakableStoneScript";
		break;

	case SCRIPT_TYPE::BTNSCRIPT:
		return L"CBtnScript";
		break;

	case SCRIPT_TYPE::BUGMONSTERSCRIPT:
		return L"CBugMonsterScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
		break;

	case SCRIPT_TYPE::CHARACTERSELECTSCRIPT:
		return L"CCharacterSelectScript";
		break;

	case SCRIPT_TYPE::CUTSCENESCRIPT:
		return L"CCutSceneScript";
		break;

	case SCRIPT_TYPE::DAMAGEFONTSCRIPT:
		return L"CDamageFontScript";
		break;

	case SCRIPT_TYPE::DROPMISSILESCRIPT:
		return L"CDropMissileScript";
		break;

	case SCRIPT_TYPE::ELECBLOCKSCRIPT:
		return L"CElecBlockScript";
		break;

	case SCRIPT_TYPE::ELECCHILDSCRIPT:
		return L"CElecChildScript";
		break;

	case SCRIPT_TYPE::ELECEFFECTSCRIPT:
		return L"CElecEffectScript";
		break;

	case SCRIPT_TYPE::ELECTOWERSCRIPT:
		return L"CElecTowerScript";
		break;

	case SCRIPT_TYPE::ENDBLOCKSCRIPT:
		return L"CEndBlockScript";
		break;

	case SCRIPT_TYPE::FIREBOWLSCRIPT:
		return L"CFireBowlScript";
		break;

	case SCRIPT_TYPE::FIREWOODSCRIPT:
		return L"CFireWoodScript";
		break;

	case SCRIPT_TYPE::FSMSCRIPT:
		return L"CFSMScript";
		break;

	case SCRIPT_TYPE::HITEFFECTSCRIPT:
		return L"CHiteffectScript";
		break;

	case SCRIPT_TYPE::HITSCRIPT:
		return L"CHitScript";
		break;

	case SCRIPT_TYPE::HPHARSCRIPT:
		return L"CHPHarScript";
		break;

	case SCRIPT_TYPE::INVADERSCRIPT:
		return L"CInvaderScript";
		break;

	case SCRIPT_TYPE::JUMPUPSCRIPT:
		return L"CJumpUpScript";
		break;

	case SCRIPT_TYPE::MAPSCRIPT:
		return L"CMapScript";
		break;

	case SCRIPT_TYPE::MINOTAUROS:
		return L"CMinotauros";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::OBJEVENTSCRIPT:
		return L"CObjEventScript";
		break;

	case SCRIPT_TYPE::OBJSTATE:
		return L"CObjState";
		break;

	case SCRIPT_TYPE::OBJTILECOL:
		return L"CObjTileCol";
		break;

	case SCRIPT_TYPE::PLAYERPOSSETSCRIPT:
		return L"CPlayerPosSetScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::POSSETTARGETSCRIPT:
		return L"CPosSetTargetScript";
		break;

	case SCRIPT_TYPE::PUSHSMALLSTONESCRIPT:
		return L"CPushSmallStoneScript";
		break;

	case SCRIPT_TYPE::PUSHSTONESCRIPT:
		return L"CPushStoneScript";
		break;

	case SCRIPT_TYPE::RADIANDIRSCRIPT:
		return L"CRadianDIRScript";
		break;

	case SCRIPT_TYPE::REDBUTTONSCRIPT:
		return L"CRedButtonScript";
		break;

	case SCRIPT_TYPE::SAPA:
		return L"CSapa";
		break;

	case SCRIPT_TYPE::SOUNDSCRIPT:
		return L"CSoundScript";
		break;

	case SCRIPT_TYPE::SPEEDUPSCRIPT:
		return L"CSpeedUpScript";
		break;

	case SCRIPT_TYPE::SPINBULLETSCRIPT:
		return L"CSpinBulletScript";
		break;

	case SCRIPT_TYPE::STONEDOORSCRIPT:
		return L"CStoneDoorScript";
		break;

	case SCRIPT_TYPE::TARGETSEARCHSCRIPT:
		return L"CTargetSearchScript";
		break;

	case SCRIPT_TYPE::TARGETTOAUTO:
		return L"CTargetToAuto";
		break;

	case SCRIPT_TYPE::TILECOLLSION:
		return L"CTileCollsion";
		break;

	case SCRIPT_TYPE::TOUCHSCRIPT:
		return L"CTouchScript";
		break;

	}
	return nullptr;
}