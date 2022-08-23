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

	if (m_doorInfo.dir == DIRECTION::LEFT || m_doorInfo.dir == DIRECTION::RIGHT)
	{
		m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 30), (m_Transform->GetSizeY() - 50));
	}
	else
	{
		m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 50), (m_Transform->GetSizeY() - 32));
	}

	AddComponent(m_collide);

	if (m_doorInfo.dir == DIRECTION::LEFT)
	{
		m_sprite->GetSprite()->RotateFlip(Rotate270FlipY);
	}
	else if (m_doorInfo.dir == DIRECTION::RIGHT)
	{
		m_sprite->GetSprite()->RotateFlip(Rotate270FlipX);
	}
	else if (m_doorInfo.dir == DIRECTION::DOWN)
	{
		m_sprite->GetSprite()->RotateFlip(Rotate180FlipX);
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
	if (CSceneMgr::GetInstance()->GetCurScene()->GetState() != SCENE_STATE::OPEN)
	{
		CImageMgr::GetInstance()->GetGraphics()->DrawImage(
			m_sprite->GetSprite(),
			Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
				(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
				(INT)m_ObjInfo.vecSize.x * 2,
				(INT)m_ObjInfo.vecSize.y * 2),
			(INT)m_ObjInfo.vecStartPos.x, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);
	}
	else
	{
		if (m_doorInfo.dir == DIRECTION::UP)
		{
			CImageMgr::GetInstance()->GetGraphics()->DrawImage(
				m_sprite->GetSprite(),
				Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
					(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
					(INT)m_ObjInfo.vecSize.x * 2,
					(INT)m_ObjInfo.vecSize.y * 2),
				(INT)64, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);
		}
		else if (m_doorInfo.dir == DIRECTION::DOWN)
		{
			CImageMgr::GetInstance()->GetGraphics()->DrawImage(
				m_sprite->GetSprite(),
				Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
					(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
					(INT)m_ObjInfo.vecSize.x * 2,
					(INT)m_ObjInfo.vecSize.y * 2),
				(INT)64, (INT)m_ObjInfo.vecStartPos.y, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);
		}
		else if (m_doorInfo.dir == DIRECTION::LEFT)
		{
			CImageMgr::GetInstance()->GetGraphics()->DrawImage(
				m_sprite->GetSprite(),
				Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
					(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
					(INT)m_ObjInfo.vecSize.x * 2,
					(INT)m_ObjInfo.vecSize.y * 2),
				(INT)m_ObjInfo.vecStartPos.x, 192, (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);
		}
		else if (m_doorInfo.dir == DIRECTION::RIGHT)
		{

			CImageMgr::GetInstance()->GetGraphics()->DrawImage(
				m_sprite->GetSprite(),
				Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
					(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
					(INT)m_ObjInfo.vecSize.x * 2,
					(INT)m_ObjInfo.vecSize.y * 2),
				(INT)m_ObjInfo.vecStartPos.x, 192 - (64 * m_iCurFrame), (INT)m_ObjInfo.vecSize.x, (INT)m_ObjInfo.vecSize.y, UnitPixel);

			if (m_fCurDelay > m_fDoorDelay)
			{
				++m_iCurFrame;
				m_fCurDelay = 0;
			}

			m_fCurDelay += DELTA;

			if (m_iCurFrame == m_iFramelimit)
			{
				m_iCurFrame = 0;
			}
		}
	}



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
	if (CSceneMgr::GetInstance()->GetCurScene()->GetState() == SCENE_STATE::OPEN)
	{
		if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
		{
			m_collide->OffCollisionFlag();
			ChangeSceneFromDoor();
		}
	}
	return TRUE;
}
