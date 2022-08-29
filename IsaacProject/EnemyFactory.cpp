#include "stdafx.h"
#include "EnemyFactory.h"

void CEnemyFactory::CreateEnemyForType(ENEMY_TYPE type, Vector2 vecPos)
{
	switch (type)
	{
	case ENEMY_TYPE::FLY:
		CreateObject(new CFly(
			ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
			Vector2(0, 0),
			Vector2(32, 32),
			Vector2(32, 32),
			vecPos,
			Vector2(1, 1),
			OBJECT_TYPE::ENEMY, OBJECT_STATE::IDLE), 
			EnemyInfo(4, 0.5f, 0, 50.f, 0.f, ENEMY_TYPE::FLY)));
		break;
	case ENEMY_TYPE::ATTACKFLY:
		break;
	case ENEMY_TYPE::FATEISAAC:
		break;
	case ENEMY_TYPE::FLYBOSS:
		break;
	}
}

