#include "stdafx.h"
#include "CKey.h"

CKey::CKey(ObjectInfo obj, ITEM_TYPE type):
	CItem(obj,type)
{
}

CKey::~CKey()
{
}

void CKey::Init()
{
}

void CKey::Update()
{
}

void CKey::FixedUpdate()
{
	CheckCollisionState();
}


void CKey::Render(HDC hdc)
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
		//Ææ¼³Á¤
		HPEN hOldPen;
		HPEN CurPen;

		CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		hOldPen = (HPEN)SelectObject(hdc, CurPen);
		hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}

void CKey::Release()
{
	CObject::Release();
}

INT CKey::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{
		CPlayer* player  = dynamic_cast<CPlayer*>(m_collide->GetTargetObjForType(OBJECT_TYPE::PLAYER));

		if (player != NULL)
		{
			//key Inventory »ý¼º
			player->PickUpItem(m_Itemtype);
		}
	}
	return TRUE;
}
