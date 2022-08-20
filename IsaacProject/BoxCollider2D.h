#pragma once
class CBoxCollider2D : public CCollider2D
{
public:
	CBoxCollider2D(CObject* target, float sizeX, float sizeY);
	CBoxCollider2D();
	virtual ~CBoxCollider2D();
public:
	const Square GetAABB() const;
	virtual void Init() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(HDC hdc) override;
};