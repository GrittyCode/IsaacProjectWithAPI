#include "stdafx.h"
#include "MapCollider.h"

CMapCollider::CMapCollider()
{
}

CMapCollider::CMapCollider(ObjectInfo objinfo)
{
    m_ObjInfo = objinfo;
}

CMapCollider::~CMapCollider()
{
}

void CMapCollider::Init()
{
    CObject::Init();
    m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX(),m_Transform->GetSizeY());
    AddComponent(m_collide);
}

void CMapCollider::Update()
{
}

void CMapCollider::FixedUpdate()
{
    CObject::FixedUpdate();
}

void CMapCollider::LateUpdate()
{
}

void CMapCollider::Render(HDC hdc)
{
	CImageMgr::GetInstance()->GetGraphics()->DrawImage(
		m_sprite->GetSprite(),
		Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
			(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
			(INT)m_ObjInfo.vecSize.x * 2,
			(INT)m_ObjInfo.vecSize.y * 2),
		(INT)m_ObjInfo.vecStartPos.x, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecEndPos.x, (INT)m_ObjInfo.vecEndPos.y, UnitPixel);

	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HBRUSH hOldBrush;
		//펜설정
		HPEN hOldPen;
		HPEN CurPen;

		CurPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		hOldPen = (HPEN)SelectObject(hdc, CurPen);
		hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}

void CMapCollider::Release()
{
}

INT CMapCollider::CheckCollisionState()
{
    if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
        PushMover(m_collide->GetTarget(OBJECT_TYPE::PLAYER)->GetOwnerObj());

    m_collide->OffCollisionFlag();

    return 0;
}

void CMapCollider::PushMover(CObject* obj)
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
