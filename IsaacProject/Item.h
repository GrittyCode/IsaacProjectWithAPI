#pragma once

enum class ITEM_TYPE
{
	COIN,
	BOMB,
	KEY,
	ITME_TYPE_END
};


class CItem
	: public CObject
{
public:
	CItem(ObjectInfo obj);
	virtual ~CItem();
	virtual void Update() = 0;
	virtual INT CheckCollisionState() = 0;
	ITEM_TYPE GetItemType() { return m_type; }
protected:
	ITEM_TYPE m_type;
};

