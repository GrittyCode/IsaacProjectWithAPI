#include "stdafx.h"
#include "Collider2D.h"

void CCollider2D::SetOffsetX(float x)
{
	m_vecOffset.x = x;
}

void CCollider2D::SetOffsetY(float y)
{
	m_vecOffset.y = y;
}

void CCollider2D::SetSizeX(float x)
{
	m_vecSize.x = x;
}

void CCollider2D::SetSizeY(float y)
{
	m_vecSize.y = y;
} 

void CCollider2D::SetCollisonFlag(int state)
{
	m_Flag |= state;
}

void CCollider2D::OffCollisionFlag()
{
	m_Flag &= ~((int)COLLISION_FLAG::OBSTACLE | (int)COLLISION_FLAG::ENEMY |
				(int)COLLISION_FLAG::TEAR | (int)COLLISION_FLAG::BOMB |
			    (int)COLLISION_FLAG::DOOR | (int)COLLISION_FLAG::ITEM |
				(int)COLLISION_FLAG::PLAYER);
}

void CCollider2D::CollisionCheck()
{
	m_source->CheckCollisionState();
}

void CCollider2D::SetTargetCollision(CCollider2D* collide)
{
	m_targetColide = collide;
}

CCollider2D* CCollider2D::GetTargetCollide()
{
	return m_targetColide;
}

CObject* CCollider2D::GetSourceObj()
{
	return m_source;
}


