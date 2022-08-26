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

