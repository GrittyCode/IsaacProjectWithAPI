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
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 10.0f), (m_Transform->GetSizeY() - 10.0f));
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
		//펜설정
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
		PushMover(m_collide->GetTarget(OBJECT_TYPE::PLAYER)->GetOwnerObj());

	m_collide->OffCollisionFlag();

	return 0;
}

void CObstacle::PushMover(CObject* obj)
{
		RECT intersectRect = {};
		RECT aRect = m_collide->GetAABB();
		RECT bRect = obj->GetCollide()->GetAABB();

		IntersectRect(&intersectRect, &aRect, &bRect);

		//방향 벡터 구하기
		Vector2 vecDir = { m_Transform->GetPosition() - obj->GetTransform()->GetPosition() };
		vecDir.Normalize();

		Vector2 vecRect = { (intersectRect.right - intersectRect.left), (intersectRect.bottom - intersectRect.top) };

		if (abs(vecRect.x) > abs(vecRect.y))
		{
			float yDiff = intersectRect.bottom - intersectRect.top;

			if (vecDir.y > 0)
				obj->GetTransform()->SetPositionY(obj->GetTransform()->GetPositionY() - yDiff);
			else
				obj->GetTransform()->SetPositionY(obj->GetTransform()->GetPositionY() + yDiff);
		}
		else
		{
			float xDiff = intersectRect.right - intersectRect.left;
			//x축 리턴 위 대각선 이동

			if (vecDir.x > 0)
				obj->GetTransform()->SetPositionX(obj->GetTransform()->GetPositionX() - xDiff);
			else
				obj->GetTransform()->SetPositionX(obj->GetTransform()->GetPositionX() + xDiff);
		}
}
