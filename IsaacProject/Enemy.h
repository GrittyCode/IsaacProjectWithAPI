#pragma once
#include "Object.h"

struct EnemyInfo
{
	EnemyInfo(INT _ihp,FLOAT _fdmg,INT _irange, FLOAT _fspeed, FLOAT _fattakSpeed, ENEMY_TYPE _type)
		:iHp(_ihp),
		fDmg(_fdmg),
		iRange(_irange),
		fSpeed(_fspeed),
		fAttakSpeed(_fattakSpeed),
		type(_type)
	{
	}

	INT iHp;
	FLOAT fDmg;
	INT iRange;
	FLOAT fSpeed;
	FLOAT fAttakSpeed;
	ENEMY_TYPE type;
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

	int GetHp() { return m_Eenmyinfo.iHp; };

	void SetHp(int demage);

	EnemyInfo GetEnemyInfo() { return m_Eenmyinfo; };

protected:
	AI* m_pAI = nullptr;
	EnemyInfo m_Eenmyinfo;
};

