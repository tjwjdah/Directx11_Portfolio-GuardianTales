#pragma once

struct VTX
{
	Vec3 vPos;
	Vec4 vColor;	
	Vec2 vUV;
};

struct tParticle
{
	Vec3	vWorldPos;
	Vec3	vWorldDir;

	float	m_fCurTime;
	float	m_fMaxLife;
	float   m_fSpeed;

	int		iAlive;

private:
	int     iPadding[2];
};

struct tParticleShared
{
	int iAliveCount;
	int iPadding[3];
};

struct tTile
{
	Vec2	vLeftTop;
	Vec2	vStep;
public:
	tTile() {
		vLeftTop = Vec2(0.0f, 0.0f);
		vStep = Vec2(0.2f, 0.2f);
	}
};
struct tTileShared
{
	int		iTileXSize;
	int		iTileYSize;
private:
	int		iPadding[2];
};

struct tDamageFont
{
	Vec2	vLeftTop;
	Vec2	vStep;
public:
	tDamageFont() {
		vLeftTop = Vec2(0.0f, 0.0f);
		vStep = Vec2(0.2f, 0.5f);
	}
};
struct tDamageFontShared
{
	int		iTileXSize;
	int		iTileYSize;
private:
	int		iPadding[2];
};


struct tLightColor
{
	Vec4 vDiff; // Diffuse (난반사광 세기)	
	Vec4 vAmb;  // Ambient (환경광)
};

struct tLight2DInfo
{
	tLightColor color;  // 광원 색상

	Vec4		vDir;   // 광원의 방향
	Vec4		vWorldPos; // 광원의 위치

	LIGHT_TYPE  eType;	// 광원 타입		
	float		fRange; // 광원의 범위
	float		fAngle; // 광원 각도
	
	int			iPadding;
};

struct tAnim2D
{
	Vec2	vLeftTop;
	Vec2	vStep;
	int		iAnimUse[4];
};

struct CDIR
{
	bool b_UP;
	bool b_DOWN;
	bool b_RIGHT;
	bool b_LEFT;
};





// ==============
// 상수버퍼 구조체
// ==============
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;
	Matrix	matProj;
	Matrix	matWV;
	Matrix  matWVP;
};

struct tMtrlInfo
{
	Vec4 vDiff;
	Vec4 vSpec;
	Vec4 vEmis;

	int		arrInt[4];
	float	arrFloat[4];
	Vec2	arrVec2[4];
	Vec4	arrVec4[4];
	Matrix	arrMat[4];

	int     arrTexCheck[12];
};

struct tGlobalValue
{
	Vec2 vResolution;
	Vec2 vNoiseResolution;
	float fDeltaTime;
	float fAcctime;

	UINT iLight2DCount;
	UINT iLight3DCount;
};
