#include "stdafx.h"
#include "Item.h"


CItem::CItem(ObjectInfo obj, ITEM_TYPE type) :
	CObject(obj),
	m_Itemtype(type)
{
	//생성할때 타입이 지정된다.
}

CItem::~CItem()
{
}

void CItem::Render(HDC hdc)
{
	CImageMgr::GetInstance()->GetGraphics()->DrawImage(
		m_sprite->GetSprite(),
		Rect((INT)m_ObjInfo.vecWorldPos.x - (INT)m_ObjInfo.vecSize.x,
			(INT)m_ObjInfo.vecWorldPos.y - (INT)m_ObjInfo.vecSize.y,
			(INT)m_ObjInfo.vecSize.x * 2,(INT)m_ObjInfo.vecSize.y * 2),
		(INT)m_ObjInfo.vecStartPos.x,
		(INT)m_ObjInfo.vecStartPos.y,
		(INT)m_ObjInfo.vecEndPos.x,
		(INT)m_ObjInfo.vecEndPos.y, UnitPixel);

	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HBRUSH hOldBrush;
		//펜설정
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

INT CItem::CheckCollisionState()
{

	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(m_collide->GetTargetObjForType(OBJECT_TYPE::PLAYER));

		if (player != NULL)
		{
			//type에 따른 아이템 지급
			player->PickUpItem(m_Itemtype);
			DeleteObject(this);
		}
	}

	return TRUE;

}

void CItem::Init()
{
	CObject::Init();

	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX()), (m_Transform->GetSizeY()));

	AddComponent(m_collide);
}
