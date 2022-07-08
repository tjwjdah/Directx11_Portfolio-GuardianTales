#include "pch.h"



#include "CMinotauros.h"
#include "CFSMScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CGameObject.h>
#include <Engine\CScene.h>
#include <Engine\CTransform.h>
#include <Engine\CAnimator2D.h>
#include <Engine\CTimeMgr.h>
#include <Engine\CAnimation2D.h>

void CMinotauros::ATTACKRUSH()
{

    switch (m_Pattern)
    {
    case Pattern::START:
    {
        if (!m_AinmOn)
        {
            if (m_vTargetDir.x > 0)
                m_DIR = DIR::RIGHT;
            else
                m_DIR = DIR::LEFT;
            switch (m_DIR)
            {
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"CHARGEREADY_RIGHT", false);
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"CHARGEREADY_LEFT", false);
                break;
            }
            m_AinmOn = true;
        }

        if (Animator2D()->GetCurAnim()->IsFinish())
        {
            m_Pattern = Pattern::LOOP;
            m_AinmOn = false;
            m_fMaxTime = 0.2f;
            m_fTime = 0;
        }
    }
    break;
    case Pattern::LOOP:
    {
        if (!m_AinmOn)
        {
            Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"mino_stomp");  //*********************
            pSound->Play(1, true); //0을 넣으면 무한반복 ,중복재생 하고싶으면 true (기본값은 false, 중복재생 막아놓음)

            switch (m_DIR)
            {
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"CHARGEREADYLP_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"CHARGEREADYLP_LEFT");
                break;
            }
            m_AinmOn = true;
        }

        m_fTime += fDT;

        if (m_fTime > m_fMaxTime)
        {
            m_Pattern = Pattern::PLAY;
            m_fMaxTime = 1.f;
            m_fTime = 0;
            m_AinmOn = false;
        }
    }
    break;
    case Pattern::PLAY:
    {
        if (!m_AinmOn)
        {
            if (m_vTargetDir.x > 0)
                m_DIR = DIR::RIGHT;
            else
                m_DIR = DIR::LEFT;
            switch (m_DIR)
            {
            case DIR::RIGHT:
                Animator2D()->PlayAnimation(L"CHARGE_RIGHT");
                break;
            case DIR::LEFT:
                Animator2D()->PlayAnimation(L"CHARGE_LEFT");
                break;
            }
            m_AinmOn = true;
            m_vRushSetDir = m_vTargetDir;
        }
        Vec3 vMinoPos = Transform()->GetLocalPos();

        if (m_eColliderDir.b_UP == true)
        {
            if (m_vRushSetDir.y > 0.f)
                m_vRushSetDir.y = 0.f;
        }
        if (m_eColliderDir.b_DOWN == true)
        {
            if (m_vRushSetDir.y < 0.f)
                m_vRushSetDir.y = 0.f;
        }
        if (m_eColliderDir.b_RIGHT == true)
        {
            if (m_vRushSetDir.x > 0.f)
                m_vRushSetDir.x = 0.f;
        }
        if (m_eColliderDir.b_LEFT == true)
        {
            if (m_vRushSetDir.x < 0.f)
                m_vRushSetDir.x = 0.f;
        }
        vMinoPos.x += m_vRushSetDir.x * fDT * m_fSpeed * 2;
        vMinoPos.y += m_vRushSetDir.y * fDT * m_fSpeed * 2;
        Transform()->SetLocalPos(vMinoPos);

        m_fTime += fDT;

        if (m_fTime > m_fMaxTime)
        {
            m_Pattern = Pattern::END;
            m_fMaxTime = 1.f;
            m_fTime = 0;
            m_AinmOn = false;
            m_RushNum++;
        }
    }
    break;
    case Pattern::END:
    {
        if (m_RushNum < 3)
        {
            m_Pattern = Pattern::START;
        }
        else
        {
            m_Pattern = Pattern::START;
            m_State = MinoState::IDLE;
            m_RushNum = 0;
            m_vRushSetDir.x = 0;
            m_vRushSetDir.y = 0;
        }
    }
    break;
    case Pattern::NONE:
    {

    }
    break;

    }
}