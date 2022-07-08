#include "pch.h"
#include "CFireBowlScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>

#include "CPlayerScript.h"

#include "CObjEventScript.h"

CFireBowlScript::CFireBowlScript()
    : CScript((int)SCRIPT_TYPE::FIREBOWLSCRIPT)
    //, m_pPlayerScript(nullptr)
    , m_bCol(false)
    , m_fAtime(0.f)
    , m_vSpeed(350.f, 300.f)
    , m_fSpeed(350.f)
    , m_fAngle(15.f)
    , m_eState(FIRE_STATE::NONE)
    , m_vPos(0, 0, 400)
    , m_eDir(DIR::DOWN)
    , m_vStartPos(0, 0, 0)
    , m_fAdjSpeed(100.f)
{
    Ptr<CTexture> pTex = CResMgr::GetInst()->FindRes<CTexture>(L"firebowl");
    Ptr<CMaterial> pMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"FireBowlMtrl");
    pMtrl->SetData(SHADER_PARAM::TEX_0, pTex.Get());


}

CFireBowlScript::~CFireBowlScript()
{
}

void CFireBowlScript::awake()
{
    //스크립트
    //CGameObject* PlayerObject = CSceneMgr::GetInst()->FindObjectByName(L"Player");
    //m_pPlayerScript = dynamic_cast<CPlayerScript*>(PlayerObject->GetScript(L"CPlayerScript"));
}

void CFireBowlScript::update()
{
    CheckState();
    Move();
}

void CFireBowlScript::CheckState()
{
    //if (m_eState == FIRE_STATE::COL)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;

        CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();
        PLAYER_STATE _curstate = pPS->GetPlayerState();
        PLAYER_ITEM _playeritem = pPS->GetPlayerItem();

        // 충돌상태이고 플레이어가 Item상태일때 , 머리 위로
        if (m_eState == FIRE_STATE::COL && _curstate == PLAYER_STATE::ITEM && _playeritem == PLAYER_ITEM::FIREBOWL)   m_eState = FIRE_STATE::HEAD;

        // 머리 위에 있었는데, 플레이어가 놓았을 때
        else if (m_eState == FIRE_STATE::HEAD && _curstate == PLAYER_STATE::THROW)
        {
            // 머리에서 던질때 위치, 방향 상태 저장
            m_fSpeed = 350.f;
            m_vSpeed = Vec2(350.f, 300.f);
            m_fAdjSpeed = 100.f;
            m_eDir = pPS->GetPlayerAnimDir();
            m_vPos = pPS->Transform()->GetLocalPos();
            m_vPos.z = 399.f; //플레이어 앞으로 화로
            m_vStartPos = m_vPos;
            m_eState = FIRE_STATE::SLIDE;
        }
    }
}
void CFireBowlScript::Move()
{
    //if (m_pPlayerScript != nullptr)
    {
        CGameObject* pPlayer = CSceneMgr::GetInst()->FindPlayer(0);
        if (pPlayer == nullptr)
            return;

        CPlayerScript* pPS = (CPlayerScript*)pPlayer->GetScript();

        Vec3 _vPlayerpos = pPS->Transform()->GetLocalPos();
        Vec3 _vPos = Transform()->GetLocalPos();

        if (m_eState == FIRE_STATE::HEAD)
        {
            _vPos.x = _vPlayerpos.x;
            _vPos.y = _vPlayerpos.y + 30;
            _vPos.z = 399.f;
            Transform()->SetLocalPos(_vPos);
        }
        else if (m_eState == FIRE_STATE::SLIDE)
        {

            switch (m_eDir)
            {
            case DIR::RIGHT:
                m_vPos.x -= m_vSpeed.x * cosf(m_fAngle) * fDT;
                m_vPos.y += m_vSpeed.y * sinf(m_fAngle) * fDT;
                break;

            case DIR::LEFT:
                m_vPos.x += m_vSpeed.x * cosf(m_fAngle) * fDT;
                m_vPos.y += m_vSpeed.y * sinf(m_fAngle) * fDT;
                break;

            case DIR::DOWN:
                m_vPos.y -= m_fSpeed * fDT;
                break;

            case DIR::UP:
                m_vPos.y += m_fSpeed * fDT;
                break;
            }

            if (m_eDir == DIR::RIGHT || m_eDir == DIR::LEFT)
            {
                //마찰력
                if (m_vSpeed.x > 0)
                {
                    m_vSpeed.x -= 130 * fDT;   //0.05
                }
                else if (m_vSpeed.x < 0)
                {
                    m_vSpeed.x += 130 * fDT;
                }
                //중력
                m_vSpeed.y -= 800 * fDT;

                if ((UINT)m_vPos.y <= (UINT)m_vStartPos.y)
                {
                    m_vSpeed.y = m_fAdjSpeed;
                    m_fAdjSpeed -= 10;
                    if (m_fAdjSpeed < 0.f) m_fAdjSpeed = 0.f;
                }
            }
            else //위아래 방향으로 던졌을 때
            {
                //마찰력
                if (m_fSpeed > 0)
                {
                    m_fSpeed -= 250 * fDT;
                }
                else if (m_fSpeed < 0)
                {
                    m_fSpeed += 250 * fDT;
                }
            }
            Transform()->SetLocalPos(m_vPos);

            //다 미끄러진 후 원래 상태로
            m_fAtime += fDT;
            if (m_fAtime > 3.f)
            {
                m_eState = FIRE_STATE::NONE;
                m_fAtime = 0.f;
            }


        }
    }
}


void CFireBowlScript::OnCollisionEnter(CGameObject* _pOther)
{
    //부딪힌 오브젝트 이름 받아옴
    if (nullptr != _pOther->GetScript(L"CPlayerScript"))
    {
        m_eState = FIRE_STATE::COL;
    }

}

void CFireBowlScript::OnCollisionExit(CGameObject* _pOther)
{
    //부딪힌 오브젝트 이름 받아옴
    if (nullptr != _pOther->GetScript(L"CPlayerScript") && (m_eState == FIRE_STATE::COL))
    {
        m_eState = FIRE_STATE::NONE;
    }
    //if (m_eState == FIRE_STATE::COL) m_eState = FIRE_STATE::NONE;
}

void CFireBowlScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CFireBowlScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}