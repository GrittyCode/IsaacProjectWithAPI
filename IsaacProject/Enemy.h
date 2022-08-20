#pragma once
#include "Object.h"

struct EnemyInfo
{
	EnemyInfo(INT _ihp,INT _idmg,INT _irange,float _fspeed,float _fattakSpeed)
		:iHp(_ihp),
		iDmg(_idmg),
		iRange(_irange),
		fSpeed(_fspeed),
		fAttakSpeed(_fattakSpeed)
	{
	}

	INT iHp;
	INT iDmg;
	INT iRange;
	float fSpeed;
	float fAttakSpeed;
};


class CEnemy : public CObject
{
public:
	CEnemy(ObjectInfo objInfo, EnemyInfo enemyinfo);
	virtual ~CEnemy();
public:
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(HDC hdc) ;
	virtual void Release();
	virtual void Move();
	virtual INT CheckCollisionState();

	EnemyInfo GetEnemyInfo() { return m_Eenmyinfo; };

protected:
	AI* m_pAI = nullptr;
	EnemyInfo m_Eenmyinfo;
};

