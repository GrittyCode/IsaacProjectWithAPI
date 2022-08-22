#include "stdafx.h"
#include "Door.h"

CDoor::CDoor(ObjectInfo objInfo, DoorInfo doorInfo)
	: CObject(objInfo),
		m_doorInfo(doorInfo)
{
}

CDoor::~CDoor()
{
}


void CDoor::Init()
{
	CObject::Init();
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 50), (m_Transform->GetSizeY() - 38));
	AddComponent(m_collide);

	if (m_doorInfo.dir == DIRECTION::LEFT)
	{
		m_sprite->GetSprite()->RotateFlip(Rotate270FlipY);
	}
	else if (m_doorInfo.dir == DIRECTION::RIGHT)
	{
		m_sprite->GetSprite()->RotateFlip(Rotate270FlipX);
	}
}

void CDoor::Update()
{
}



void CDoor::FixedUpdate()
{
	CObject::FixedUpdate();
}

void CDoor::Render(HDC hdc)
{
	//render
	CImageMgr::GetInstance()->GetGraphics()->DrawImage(
		m_sprite->GetSprite(),
		Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
			(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
			(INT)m_ObjInfo.vecSize.x * 2,
			(INT)m_ObjInfo.vecSize.y * 2),
		(INT)m_ObjInfo.vecStartPos.x, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);


	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HPEN	CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN	hOldPen = (HPEN)SelectObject(hdc, CurPen);
		HBRUSH	hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		
		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}

void CDoor::ChangeSceneFromDoor()
{
	ChageScene(&m_doorInfo.strSceneame, &m_doorInfo.dir);
}

INT CDoor::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{
		m_collide->OffCollisionFlag();
		ChangeSceneFromDoor();
	}
	return TRUE;
}
