#pragma once

#define SINGLE(Type) private:\
Type();\
~Type();\
template<typename T>\
friend class CSingleton;

#define SAFE_RELEASE(p) if(nullptr != p) p->Release();

#define DEVICE CDevice::GetInst()->GetDevice().Get()
#define CONTEXT CDevice::GetInst()->GetContext().Get()

#define KEY_CHECK(key, state) state == CKeyMgr::GetInst()->GetKeyState(key)
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define fDT CTimeMgr::GetInst()->GetfDT()
#define DT CTimeMgr::GetInst()->GetDT()

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;

#define CLONE(TYPE) TYPE* Clone() { return new TYPE(*this); }

#define CLONE_DISABLE(TYPE) TYPE* Clone() { return nullptr; }\
							TYPE(const TYPE & _origin) = delete;\
							const TYPE& operator = (const TYPE & _origin) = delete;

#define MAX_LAYER 32

#define GET( type ,param) type Get##param () {return m_##param;}
#define SET( type ,param) void Set##param (type _in) {m_##param = _in;} 

#define GET_SET(type, param) GET(type,param) \
							 SET(type,param);
const int TileSize_X = 64;
const int TileSize_Y = 64;
typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

enum class CB_TYPE
{
	TRANSFORM,	// b0
	MATERIAL,   // b1
	GLOBAL_VALUE, // b2

	END,
};

enum class BLEND_TYPE
{
	DEFAULT,
	ALPHABLEND,
	ALPHA_ONE,
	END,
};

enum class DS_TYPE
{
	LESS,
	LESS_EQUAL,
	GREATER,
	GREATER_EQUAL,
	NO_TEST,
	LESS_NO_WRITE,
	NO_TEST_NO_WRITE,
	END,
};

enum class PIPELINE_STAGE
{
	PS_VERTEX	= 0x01,
	PS_HULL		= 0x02,
	PS_DOMAIN	= 0x04,
	PS_GEOMETRY = 0x08,
	PS_PIXEL	= 0x10,
	PS_COMPUTE	= 0x20,
	PS_ALL = PS_VERTEX | PS_HULL | PS_DOMAIN | PS_GEOMETRY | PS_PIXEL | PS_COMPUTE,
};

enum class RES_TYPE
{
	PREFAB,
	MATERIAL,
	SHADER,
	MESH,
	TEXTURE,
	SOUND,	
	END,
};

enum class COMPONENT_TYPE
{
	TRANSFORM,	// 위치, 크기, 회전
	MESHRENDER, // 메쉬, 재질, 렌더링

	CAMERA,

	COLLIDER2D,
	COLLIDER3D,

	ANIMATOR2D,
	ANIMATOR3D,

	LIGHT2D,
	LIGHT3D,

	PARTICLE,
		
	END,
	
	SCRIPT,
};


enum class SHADER_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,
	
	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,
	
	MAT_0,
	MAT_1,
	MAT_2,
	MAT_3,

	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,
	TEX_4,
	TEX_5,
	TEX_6,
	TEX_7,
	TEXARR_0,
	TEXARR_1,
	TEXARR_2,
	TEXARR_3,
	TEX_END,
};

enum class PROJ_TYPE
{
	PERSPECTIVE,	// 원근투영
	ORTHOGRAPHIC,	// 직교투영
};

enum class DIR_TYPE
{
	RIGHT,
	UP,
	FRONT,
	END,
};

enum class COLLIDER2D_TYPE
{
	RECT,
	CIRCLE,
};

enum class LIGHT_TYPE
{
	DIR,		// 방향성 광원(태양)
	POINT,		// 점광원
	SPOT,       // 스팟
	END,
};

enum class SHADER_POV
{
	FORWARD,
	PARTICLE,
	POSTEFFECT,
};

enum class SCENE_STATE
{
	PLAY,
	PAUSE,
	STOP,
	END,
};


//플레이어 상태
enum class PLAYER_STATE
{
	IDLE,
	MOVE,
	RUN,
	ATTACK,
	SKILL,
	ITEM,
	ITEMIDLE,
	SLIDE,
	THROW,
	PUSH,
	JUMP,
	LAND,
	CRASH,
	DEAD,
	NONE
};

enum class DIR
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT,
	NONE
};


enum class Character
{
	NARI,
	MARINA,
	GARAM,
	EVA

};


//enum class MON_STATE
//{
//	IDLE,
//	MOVE,
//	ATTACK,
//	SKILL,
//	DEAD,
//	NONE
//};


enum class Monster
{
	SAPA,
	BUG,
	MINO,
	INVADER,
	None
};


enum class Pattern
{
	START,
	LOOP,
	PLAY,
	END,
	NONE
};

enum class MON_STATE
{
	IDLE,
	WALK,
	ATTACK,
	DAMAGED,
	DEAD
};



