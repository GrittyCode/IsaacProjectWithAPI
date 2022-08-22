#include "stdafx.h"
#include "Enemy.h"

CEnemy::CEnemy(ObjectInfo objInfo, EnemyInfo enemyinfo)
	:CObject(objInfo),
	 m_Eenmyinfo(enemyinfo)
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
}

void CEnemy::Update()
{
	m_pAI->Update();
}

void CEnemy::FixedUpdate()
{
	CheckCollisionState();
}

void CEnemy::Render(HDC hdc)
{
}

void CEnemy::Release()
{
}

void CEnemy::Move()
{
}

INT CEnemy::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER_TEAR)
	{
		m_pAI->ChangeState(AI_STATE::HUNT);
	}

	m_collide->OffCollisionFlag();
	return 0;
}

void CEnemy::SetHp(int demage)
{
	m_Eenmyinfo.iHp -= demage;
}
