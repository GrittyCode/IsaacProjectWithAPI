#pragma once

class CItem;

class CKey :
	public CItem
{
public:
	CKey(ObjectInfo obj, ITEM_TYPE type);
	virtual ~CKey();
	void Init();
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
	virtual INT CheckCollisionState() override;
private:

};

