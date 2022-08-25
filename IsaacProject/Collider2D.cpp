#include "stdafx.h"
#include "Collider2D.h"

void CCollider2D::Init()
{
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_mapTarget.insert({ (OBJECT_TYPE)i, nullptr});
	}
}

void CCollider2D::CollisionCheck()
{
	m_Owner->CheckCollisionState();
}

void CCollider2D::OffCollisionFlag()
{
	m_Flag &= ~((int)COLLISION_FLAG::OBSTACLE | (int)COLLISION_FLAG::ENEMY |
				(int)COLLISION_FLAG::PLAYER_TEAR | (int)COLLISION_FLAG::BOMB |
			    (int)COLLISION_FLAG::DOOR | (int)COLLISION_FLAG::ITEM |
				(int)COLLISION_FLAG::PLAYER);
}

void CCollider2D::PushTargetCollision(CCollider2D* collide)
{
	auto iter = m_mapTarget.find(collide->GetOwnerType());

	if (iter != m_mapTarget.end())
	{
		(*iter).second = collide;
	}
}

CCollider2D* CCollider2D::GetTarget(OBJECT_TYPE type)
{
	auto iter = m_mapTarget.find(type);
	
	if (iter != m_mapTarget.end())
	{
		return(*iter).second;
	}
	return nullptr;
}

CObject* CCollider2D::GetTargetObjForType(OBJECT_TYPE type)
{
	auto iter = m_mapTarget.find(type);

	if (iter != m_mapTarget.end())
	{
		return (*iter).second->GetOwnerObj();
	}

	return nullptr;
}

OBJECT_TYPE CCollider2D::GetOwnerType()
{
	return m_Owner->GetObjType();
}




