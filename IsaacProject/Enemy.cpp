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
	return 0;
}
