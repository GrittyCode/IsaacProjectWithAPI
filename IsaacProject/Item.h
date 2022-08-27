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
	CItem(ObjectInfo obj, ITEM_TYPE type);
	virtual void Init() override;
	virtual ~CItem();
	virtual void Render(HDC hdc) override;
	virtual INT CheckCollisionState();
	ITEM_TYPE GetItemType() { return m_Itemtype; }
protected:
	ITEM_TYPE m_Itemtype;
};

