#include "pch.h"
#include "CElecBlockScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CCollider2D.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CElecBlockScript::CElecBlockScript()
    : CScript((int)SCRIPT_TYPE::ELECBLOCKSCRIPT)
    , m_bIsCol(false)
    , m_bIsLinked(false)
    //, m_pPlayerScript(nullptr)
    , m_pEventScript(nullptr)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"elecblock");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ElecBlockMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());

    AddDesc(tDataDesc(SCRIPT_DATA_TYPE::INT, "m_bIsLinked", &m_bIsLinked));
}

CElecBlockScript::~CElecBlockScript()
{
}

void CElecBlockScript::awake()
{
    m_pEventScript = dynamic_cast<CObjEventScript*>(GetGameObject()->GetScript(L"CObjEventScript"));
    Transform()->SetLocalPosZ(401.f);
}

void CElecBlockScript::update()
{
    if (m_bIsLinked)
    {
        m_pEventScript->SetTrigger(true);
    }
    else
        m_pEventScript->SetTrigger(false);
    Vec3 vPos = Transform()->GetLocalPos();

    CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
    if (pPlayer == nullptr)
        return;

    CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();
    PLAYER_STATE _curstate = pPS->GetPlayerState();
    DIR _curdir = pPS->GetPlayerDir();

    //충돌상태이고 플레이어가 z키를 누르고있을때 
    if (m_bIsPushed == true && _curstate == PLAYER_STATE::PUSH)
    {
        if (_curdir == DIR::RIGHT && _curdir == m_pushdir && m_eColliderDir.b_RIGHT == false)
        {
            vPos.x += 150.f * fDT;
        }
        if (_curdir == DIR::LEFT && _curdir == m_pushdir && m_eColliderDir.b_LEFT == false)
        {
            vPos.x -= 150.f * fDT;
        }
        if (_curdir == DIR::DOWN && _curdir == m_pushdir && m_eColliderDir.b_DOWN == false)
        {
            vPos.y -= 150.f * fDT;
        }
        if (_curdir == DIR::UP && _curdir == m_pushdir && m_eColliderDir.b_UP == false)
        {
            vPos.y += 150.f * fDT;
        }
        //m_prevdir = _curdir;
    }

    Transform()->SetLocalPos(vPos);

}

void CElecBlockScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CObjTileCol"))
    {
        float cleft = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (Transform()->GetLocalPos().x - _pOther->Transform()->GetLocalPos().x);
        float cdown = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (Transform()->GetLocalPos().y - _pOther->Transform()->GetLocalPos().y);
        float cright = (_pOther->Collider2D()->GetScale().x / 2) + (Collider2D()->GetScale().x / 2) - (_pOther->Transform()->GetLocalPos().x - Transform()->GetLocalPos().x);
        float cup = (_pOther->Collider2D()->GetScale().y / 2) + (Collider2D()->GetScale().y / 2) - (_pOther->Transform()->GetLocalPos().y - Transform()->GetLocalPos().y);

        if (cleft < cdown && cleft < cright && cleft < cup)
        {
            m_eColliderDir.b_LEFT = true;

        }
        else if (cdown < cleft && cdown < cright && cdown < cup)
        {
            m_eColliderDir.b_DOWN = true;

        }
        else if (cright < cdown && cright < cleft && cright < cup)
        {
            m_eColliderDir.b_RIGHT = true;

        }
        else if (cup < cdown && cup < cright && cup < cleft)
        {
            m_eColliderDir.b_UP = true;
        }
    }

    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = true;
        Vec3 _PlayerPos = _pOther->Transform()->GetLocalPos();
        Vec3 _pos = Transform()->GetLocalPos();
        Vec2 _scale = Collider2D()->GetScale();

        if ((_PlayerPos.x < _pos.x + _scale.x / 2) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::RIGHT;
        }
        else if ((_pos.x + _scale.x / 2 < _PlayerPos.x) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::LEFT;
        }
        else if (_pos.y + _scale.y / 2 < _PlayerPos.y && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::DOWN;
        }
        else if (_PlayerPos.y < _pos.y - _scale.y / 2 && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::UP;
        }
        else m_pushdir = DIR::NONE;
    }

}

void CElecBlockScript::OnCollisionOn(CGameObject* _pOther)
{
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = true;

        Vec3 _PlayerPos = _pOther->Transform()->GetLocalPos();
        Vec3 _pos = Transform()->GetLocalPos();
        Vec2 _scale = Collider2D()->GetScale();//Transform()->GetLocalScale();

        if ((_PlayerPos.x < _pos.x + _scale.x / 2) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::RIGHT;
        }
        else if ((_pos.x + _scale.x / 2 < _PlayerPos.x) && (_pos.y - _scale.y / 2 <= _PlayerPos.y && _PlayerPos.y <= _pos.y + _scale.y / 2))
        {
            m_pushdir = DIR::LEFT;
        }
        else if (_pos.y + _scale.y / 2 < _PlayerPos.y && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::DOWN;
        }
        else if (_PlayerPos.y < _pos.y - _scale.y / 2 && (_pos.x - _scale.x / 2 <= _PlayerPos.x && _PlayerPos.x <= _pos.x + _scale.x / 2))
        {
            m_pushdir = DIR::UP;
        }
        else m_pushdir = DIR::NONE;
    }
}

void CElecBlockScript::OnCollisionExit(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CObjTileCol"))
    {
        m_eColliderDir.b_RIGHT = false;

        m_eColliderDir.b_LEFT = false;

        m_eColliderDir.b_UP = false;

        m_eColliderDir.b_DOWN = false;
    }

    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_bIsPushed = false;
    }
}

void CElecBlockScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CElecBlockScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}


