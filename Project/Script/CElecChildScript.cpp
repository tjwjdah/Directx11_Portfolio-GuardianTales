#include "pch.h"
#include "CElecChildScript.h"

#include <Engine\CSceneMgr.h>
#include <Engine\CScene.h>
#include <Engine\CResMgr.h>
#include <Engine\CTexture.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine/CEventMgr.h>
#include <Engine/CAnimation2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CCollider2D.h>

#include "CPlayerScript.h"
#include "CObjEventScript.h"
#include "CElecBlockScript.h"
#include "CElecEffectScript.h"

CElecChildScript::CElecChildScript()
    : CScript((int)SCRIPT_TYPE::ELECCHILDSCRIPT)
    , m_bIsCol(false)
    , m_pEffectScript(nullptr)
    , m_pTarScript(nullptr)
    , m_fMinDir(10000.f)
    , m_bAni(false)
    , m_state(estate::none)
    , m_effobj(nullptr)
{
}

CElecChildScript::~CElecChildScript() {}

void CElecChildScript::checkstate()
{
    Vec3 _ParPos = GetObj()->GetParent()->Transform()->GetLocalPos();

    if (m_pEffectScript->GetIsCol() == true) m_state = estate::block;

    if (m_state == estate::block && m_pEffectScript->GetIsCol() == false)
    {
        m_state = estate::none;
        m_fMinDir = 10000.f;
        m_bAni = false;
        m_bAni2 = false;
    }

    if (m_state == estate::block)
    {
        if (!m_bAni2)
        {
            m_effobj->Animator2D()->PlayAnimation(L"NONE", false);
            m_bAni2 = true;
        }
    }

    if (m_pTarScript != nullptr)
    {
        Vec3 _LinkPos = m_pTarScript->Transform()->GetLocalPos();
        float _LinkDir = sqrt(pow((_LinkPos.x - _ParPos.x), 2) + pow((_LinkPos.y - _ParPos.y), 2));
        Vec2 _vLinkDir = Vec2(_LinkPos.x - _ParPos.x, _LinkPos.y - _ParPos.y);  _vLinkDir.Normalize();
        float _Linkangle = atan2f(_vLinkDir.y, _vLinkDir.x);
        float _offset = 40.f;
        m_fMinDir = _LinkDir;

        if (!m_bAni)
        {
            //effect생성
            m_effobj->Animator2D()->PlayAnimation(L"ELECEFFECT", true);
            m_bAni = true;
        }

        m_effobj->Transform()->SetLocalScale(Vec3(_LinkDir + _offset, 64.f, 0.f));
        m_effobj->Transform()->SetLocalPos(Vec3(_ParPos.x + (_LinkPos.x - _ParPos.x) / 2, _ParPos.y + (_LinkPos.y - _ParPos.y) / 2 + 30.f, 400.f));
        m_effobj->Transform()->SetLocalRot(Vec3(0.f, 0.f, _Linkangle));
    }


}

void CElecChildScript::awake() {

    m_effect = CResMgr::GetInst()->FindRes<CPrefab>(L"ElecEffect");
    m_effobj = m_effect->Instantiate();

    tEvent _temp = {};
    _temp.eEvent = EVENT_TYPE::CREATE_OBJECT;
    _temp.lParam = (DWORD_PTR)m_effobj;
    _temp.wParam = 4;
    CEventMgr::GetInst()->AddEvent(_temp);

    m_effobj->Animator2D()->PlayAnimation(L"NONE", false);
    m_pEffectScript = dynamic_cast<CElecEffectScript*>(m_effobj->GetScript(L"CElecEffectScript"));
}

void CElecChildScript::update()
{
    checkstate();

    Vec3 _Pos = GetObj()->GetParent()->Transform()->GetLocalPos(); //내 pos

    //들어온 것 계속 조사
    for (int i = 0; i < m_vecScript.size(); ++i)
    {
        Vec3 _ChildPos = m_vecScript[i]->Transform()->GetLocalPos(); //범위 내 자식 pos
        float _Dir = sqrt(pow((_ChildPos.x - _Pos.x), 2) + pow((_ChildPos.y - _Pos.y), 2));

        if (m_fMinDir > _Dir)
        {
            m_state = estate::link;
            dynamic_cast<CElecBlockScript*>(m_vecScript[i])->SetIsLinked(true);
            m_fMinDir = _Dir;
            m_pTarScript = m_vecScript[i];

        }
        //나머지는 연결 해제
        else if (m_vecScript[i] != m_pTarScript) ///
        {
            dynamic_cast<CElecBlockScript*>(m_vecScript[i])->SetIsLinked(false);
        }
    }

}

void CElecChildScript::OnCollisionEnter(CGameObject* _pOther)
{
    if (_pOther->GetScript(L"CElecBlockScript"))
    {
        m_vecScript.push_back(_pOther->GetScript(L"CElecBlockScript"));
        m_bIsCol = true;
    }
}

void CElecChildScript::OnCollisionExit(CGameObject* _pOther)
{
    if (m_pTarScript)
    {
        if (_pOther->GetScript(L"CElecBlockScript"))
        {
            float _id = _pOther->GetScript(L"CElecBlockScript")->GetID();
            for (int i = 0; i < m_vecScript.size(); ++i)
            {
                if (_id == m_vecScript[i]->GetID())
                {
                    dynamic_cast<CElecBlockScript*>(m_vecScript[i])->SetIsLinked(false);
                    m_vecScript.erase(m_vecScript.begin() + i);

                    if (m_pTarScript->GetID() == _id)
                    {
                        m_effobj->Animator2D()->PlayAnimation(L"NONE", false);
                        m_pTarScript = nullptr;
                        m_state = estate::none;
                        m_fMinDir = 10000.f;
                    }
                }
            }

            if (m_vecScript.size() == 0)
            {
                m_effobj->Animator2D()->PlayAnimation(L"NONE", false);
                m_pTarScript = nullptr;
                m_state = estate::none;
                m_bAni = false;
                m_fMinDir = 10000.f;
                m_bIsCol = false;
            }

        }
    }

}

void CElecChildScript::SaveToScene(FILE* _pFile)
{
    CScript::SaveToScene(_pFile);
}

void CElecChildScript::LoadFromScene(FILE* _pFile)
{
    CScript::LoadFromScene(_pFile);
}