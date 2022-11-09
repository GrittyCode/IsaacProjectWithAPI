#pragma once
class CBoxCollider2D : public CCollider2D
{
public:
	CBoxCollider2D(CObject* target, float sizeX, float sizeY);
	CBoxCollider2D() {};
	virtual ~CBoxCollider2D() {};
public:
	RECT GetAABB();
	virtual void Init() override;
	virtual void Render(HDC hdc) override;
};