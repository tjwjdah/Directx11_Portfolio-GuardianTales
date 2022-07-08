#pragma once
#include <Engine\CScript.h>


enum class PLAYER_ITEM
{
    BOMB,
    FIREBOWL,
    NONE
};


class CPrefab;
class CObjState;
class CPlayerScript :
    public CScript
{
private:
    bool                m_bIsOnCol;              //충돌 중?


    PLAYER_STATE        m_eCurState;            //플레이어의 현재 상태
    PLAYER_STATE        m_ePrevState;           //이전 상태

    DIR                 m_eCurDir;              //현재 방향
    DIR                 m_ePreDir;              //이전 방향
    DIR                 m_AnimDir;
    DIR                 m_PreAinmDir;

    Vec2                 m_eCrashDir;
    float               m_tCrashTime;


    CDIR                m_eColliderDir;

    float               m_fPlayerSpeed;         //플레이어 스피드
    float               m_fAtime;               //누적시간
    float               m_fMaxtime;

    //JUMP State
    Vec3                m_vStartPos;
    Vec2                m_vJumpSpeed;
    float               m_fJumpSpeed;
    float               m_fAngle;



    PLAYER_ITEM         m_eItem;


    Character           m_Character;


    CObjState*           m_State;
    
    Ptr<CPrefab>             m_Attack1;  //평타
    Ptr<CPrefab>            m_Attack2;  //평타2
    Ptr<CPrefab>            m_Attack3;  //평타3
    Ptr<CPrefab>            m_Attack4;  //평타4

    Ptr<CPrefab>            m_Skill1;  //스킬
    Ptr<CPrefab>            m_Skill2;  //특수 스킬

    Ptr<CPrefab>            m_LinkSkill; //연계기

    int                  m_CurrentCombo;
    int                  m_PreCombo;
    int                  m_MaxCombo;
    bool                 m_IsAttacking;
    bool                 m_CanNextCombo;
    bool                 m_IsComboInputOn;


    int                  m_ISkillNum; //몇번째 스킬 사용할지
    //스킬 재사용 대기시간
    

    float               m_fAtimeslide;

    CGameObject* m_Target; //가장 가까운 몬스터 타겟

    //오토용
  
    int                 m_iPartyNum;
    bool                m_AinmOn;
    float               m_ftime;

    bool              m_Hit;
    float             m_HitTime;
private:

public:
    //GET SET
    PLAYER_STATE GetPlayerState() { return m_eCurState; }
    void SetPlayerState(PLAYER_STATE _state) { m_eCurState = _state; }
    PLAYER_STATE GetPlayerPrevState() { return m_ePrevState; }
    DIR GetPlayerDir() { return m_eCurDir; }
    DIR GetPlayerAnimDir() { return m_AnimDir; }
    void SetPlayerDir(DIR _key) { m_eCurDir = _key; }
    float GetPlayerSpeed() { return m_fPlayerSpeed; }
    void SetPlayerSpeed(float _speed) { m_fPlayerSpeed = _speed; }
    PLAYER_ITEM GetPlayerItem() { return m_eItem; }
    void SetPlayerIsOnCol(bool _col) { m_bIsOnCol = _col; }
    void SetPlayerStartPos(Vec3 _pos) { m_vStartPos = _pos; }
    void SetPlayerJumpSpeed(Vec2 _pos) { m_vJumpSpeed = _pos; m_fJumpSpeed = 500.f; }

    void SetMaxCombo(int _Combo) { m_MaxCombo = _Combo; }

    void SetAttack(CPrefab* _Attack1, CPrefab* _Attack2 = nullptr, CPrefab* _Attack3 = nullptr, CPrefab* _Attack4 = nullptr) {
        m_Attack1 = _Attack1;
        m_Attack2 = _Attack2;
        m_Attack3 = _Attack3;
        m_Attack4 = _Attack4;
    }
    void SetSkill(CPrefab* _Skill, CPrefab* _Skill2 = nullptr)
    {
        m_Skill1 = _Skill;
        m_Skill1 = _Skill2;
    }
    void SetLinkSkill(CPrefab* _LinkSkill)
    {
        m_LinkSkill = _LinkSkill;
    }

    void SetCharacter(Character _Character) { m_Character = _Character; }
    Character GetCharacter() {return  m_Character; }
    void SetTarget(CGameObject* _Obj) { m_Target = _Obj; }
    int GetAuto() { return m_iPartyNum; }
    void SetAuto(int _Num) { m_iPartyNum = _Num; }

    GET_SET(bool, Hit);
    CObjState* GetObjState() { return m_State; }
public:
    virtual void awake();
    virtual void update();

private:

    void CheckState();
    void PlayAnimation();
   
    void PlayerAction();
    void AutoPlayer();

    void EvaAttack();
    void GaramAttack();
    void MarinaAttack();
    void NariAttack();


    void Attacking();
    void AttackStartComboState();
    void AttackEndComboState();
public:
    virtual void OnCollisionEnter(CGameObject* _pOther);
    virtual void OnCollisionExit(CGameObject* _pOther);
    virtual void OnCollision(CGameObject* _pOther);
public:
    CLONE(CPlayerScript);
    virtual void SaveToScene(FILE* _pFile);
    virtual void LoadFromScene(FILE* _pFile);


public:
    CPlayerScript();
    ~CPlayerScript();
};

