#include "stdafx.h"
#include "Obstacle.h"

CObstacle::CObstacle()
{
	m_ObjInfo = ObjectInfo();	
}

CObstacle::CObstacle(ObjectInfo objinfo)
{
	m_ObjInfo = objinfo;

}

void CObstacle::Init()
{
	CObject::Init();
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 2.0f), (m_Transform->GetSizeY() - 2.0f));
	AddComponent(m_collide);
}

void CObstacle::Update()
{
}


void CObstacle::FixedUpdate()
{
	CObject::FixedUpdate();
}



void CObstacle::Render(HDC hdc)
{

	CImageMgr::GetInstance()->GetGraphics()->DrawImage(
		m_sprite->GetSprite(),
		Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
			 (INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
			 (INT)m_ObjInfo.vecSize.x * 2,
			 (INT)m_ObjInfo.vecSize.y * 2),
		(INT)m_ObjInfo.vecStartPos.x, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);


	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HBRUSH hOldBrush;
		//Ææ¼³Á¤
		HPEN hOldPen;
		HPEN CurPen;

		if (m_isCollision)
		{
			CurPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hOldPen = (HPEN)SelectObject(hdc, CurPen);
			hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		}
		else
		{
			CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			hOldPen = (HPEN)SelectObject(hdc, CurPen);
			hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		}

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}



void CObstacle::Release()
{
	CObject::Release();
}




INT CObstacle::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
		PushMover(m_collide->GetTargetCollide()->GetSourceObj());
	m_collide->OffCollisionFlag();

	return 0;
}

void CObstacle::PushMover(CObject* obj)
{
		Vector2 vecDir =  m_Transform->GetPosition() - obj->GetTransform()->GetPosition();
		if (abs(vecDir.x) > abs(vecDir.y))
		{
			if (vecDir.x < 0.0f)
				obj->GetTransform()->SetPositionX(GetCollide()->GetAABB().right + (obj->GetCollide()->GetCollisionSize().x));
			else
				obj->GetTransform()->SetPositionX(GetCollide()->GetAABB().left - (obj->GetCollide()->GetCollisionSize().x));
		}
		else
		{
			if (vecDir.y < 0.0f)
				obj->GetTransform()->SetPositionY(GetCollide()->GetAABB().bottom + (obj->GetCollide()->GetCollisionSize().y));
			else
				obj->GetTransform()->SetPositionY(GetCollide()->GetAABB().top - (obj->GetCollide()->GetCollisionSize().y));
		}
}
