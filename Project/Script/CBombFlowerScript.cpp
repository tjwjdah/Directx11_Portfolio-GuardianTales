#include "pch.h"
#include "CBombFlowerScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine/CEventMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine/CCollisionMgr.h>
#include <Engine/CCollider2D.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"
#include "CBombScript.h"
#include "CMissileScript.h"
#include "CObjEventScript.h"

CBombFlowerScript::CBombFlowerScript()
    : CScript((int)SCRIPT_TYPE::BOMBFLOWERSCRIPT)
    , m_eState(FLOWER_STATE::IDLE)
    , m_IsOnCol(false)
    , m_bExp(false)
    , m_fAtime(0.f)
{
    m_pTex1 = CResMgr::GetInst()->FindRes<CTexture>(L"bombflower");
    m_pTex2 = CResMgr::GetInst()->FindRes<CTexture>(L"flower");
    m_pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"BombFlowerMtrl");
    m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex1.Get());
}

CBombFlowerScript::~CBombFlowerScript()
{
}

void CBombFlowerScript::awake()
{
    //스크립트
    //CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
    //m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
    m_bomb = CResMgr::GetInst()->FindRes<CPrefab>(L"Bomb");
    m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"BombEffect");
}

void CBombFlowerScript::update()
{
    CheckState();
    Excute();
}


void CBombFlowerScript::CheckState()
{

    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

    PLAYER_STATE _curstate = pPS->GetPlayerState();
    //PLAYER_STATE _prevstate = pPS->GetPlayerPrevState();

    //충돌상태이면서, 플레이어가 아이템 상태일때
    if (m_eState == FLOWER_STATE::COL && _curstate == PLAYER_STATE::ITEM && pPS->GetPlayerItem() == PLAYER_ITEM::BOMB) m_eState = FLOWER_STATE::BOMB;

    //머리 위에 있었는데, 플레이어가 놓았을 때
    if (m_eState == FLOWER_STATE::HEAD && _curstate == PLAYER_STATE::IDLE)
    {
        //아무것도 없는 상태
        m_eState = FLOWER_STATE::NONE;
    }

}

void CBombFlowerScript::Excute()
{

    if (m_eState == FLOWER_STATE::BOMB)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;
        CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

        // 폭탄 없는 꽃으로 이미지 변경
        m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex2.Get());

        // 플레이어 머리 위에 폭탄 생성
        Vec3 _PlayerPos = pPS->Transform()->GetLocalPos();

        // ===============
        // Bomb (폭탄)
        // ===============
        //CGameObject* pObj = new CGameObject;
        //pObj->SetName(L"Bomb"); /////
        //pObj->AddComponent(new CTransform);
        //pObj->AddComponent(new CMeshRender);
        //pObj->AddComponent(new CCollider2D);
        //pObj->AddComponent(new CBombScript); ////
        //pObj->Transform()->SetLocalPos(_PlayerPos);
        //pObj->Transform()->SetLocalScale(Vec3(40, 50, 1.f));
        //pObj->Transform()->SetLocalRot(Vec3(0.f, 0.f, 0.f));
        //pObj->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
        //pObj->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"BombMtrl"));/////
        //pObj->Collider2D()->SetCollider2DType(COLLIDER2D_TYPE::RECT);

        CGameObject* pObj = m_bomb->Instantiate();
        _PlayerPos.z = 399.f;
        pObj->Transform()->SetLocalPos(_PlayerPos);

        tEvent even = {};
        even.eEvent = EVENT_TYPE::CREATE_OBJECT;
        even.lParam = (DWORD_PTR)pObj;
        even.wParam = (DWORD_PTR)4;
        CEventMgr::GetInst()->AddEvent(even);

        //만든 후 head 상태로
        m_eState = FLOWER_STATE::HEAD;
    }
    else if (m_eState == FLOWER_STATE::NONE)
    {
        //3초후 폭탄 생성
        m_fAtime += fDT;
        if (m_fAtime >= 5.5f)
        {
            m_eState = FLOWER_STATE::MAKEBOMB;
            m_fAtime = 0.f;
        }
    }
    else if (m_eState == FLOWER_STATE::MAKEBOMB)
    {
        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_respawn");
        pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

        //폭탄 다시 생성 후 idle (처음) 상태로
        m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex1.Get());
        m_eState = FLOWER_STATE::IDLE;
    }
    else if (m_eState == FLOWER_STATE::EXP)
    {
        Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_bombfuse");
        pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)
        m_fAtime += fDT;
        if (m_fAtime >= 5.f)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"eff_bombexp");
            pSound->Play(1); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            // 폭탄 없는 꽃으로 이미지 변경
            m_pMtrl->SetData(SHADER_PARAM::TEX_0, m_pTex2.Get());

            //폭발 이펙트
            Vec3 _Pos = Transform()->GetLocalPos();
            _Pos.z = 399.f;
            CGameObject* m_pObject = m_effect->Instantiate();
            m_pObject->Transform()->SetLocalPos(Vec3(_Pos.x, _Pos.y + 25, _Pos.z));

            tEvent _temp = {};
            _temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
            _temp.lParam = (DWORD_PTR)m_pObject;
            CEventMgr::GetInst()->AddEvent(_temp);

            m_eState = FLOWER_STATE::NONE;
            m_fAtime = 0.f;
        }

    }
}


void CBombFlowerScript::OnCollisionEnter(CGameObject* _pOther)
{
    //부딪힌 오브젝트 이름 받아옴
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        CPlayerScript* _pPS = (CPlayerScript*)_pOther->GetScript();
        PLAYER_STATE _pstate = _pPS->GetPlayerState();

        //idle상태일때만 
        if (m_eState == FLOWER_STATE::IDLE && (_pstate == PLAYER_STATE::IDLE || _pstate == PLAYER_STATE::MOVE))
        {
            m_eState = FLOWER_STATE::COL;

        }
        else if (m_eState == FLOWER_STATE::IDLE && (_pstate == PLAYER_STATE::ITEM))
        {
            if (_pPS->GetPlayerItem() == PLAYER_ITEM::FIREBOWL)
            {
                m_eState = FLOWER_STATE::EXP;
            }
        }
    }
}

void CBombFlowerScript::OnCollisionExit(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript") && m_eState == FLOWER_STATE::COL) m_eState = FLOWER_STATE::IDLE;
}

void CBombFlowerScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CBombFlowerScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}