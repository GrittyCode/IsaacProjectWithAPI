#include "stdafx.h"
#include "Item.h"


CItem::CItem(ObjectInfo obj, ITEM_TYPE type):
	CObject(obj),
	m_Itemtype(type)
{
	
}

CItem::~CItem()
{
}

void CItem::Init()
{
	CObject::Init();

	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX()), (m_Transform->GetSizeY()));

	AddComponent(m_collide);
}
