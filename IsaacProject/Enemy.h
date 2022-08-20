#pragma once
#include "Object.h"

struct EnemyInfo
{
	INT iHp;
	INT iDmg;
	INT iRange;
	float fSpeed;
	float fAttakSpeed;
};


class CEnemy : public CMover
{
public:
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(HDC hdc) ;
	virtual void Release();
	virtual void Move();
	virtual INT CheckCollisionState();
};

