#pragma once

class CObject;

class CCollider2D : public CComponent
{
public:
	//생성 소멸자
	CCollider2D() {};
	virtual ~CCollider2D() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render(HDC hdc) = 0;

	//SET
	void SetOffsetX(float x);
	void SetOffsetY(float y);
	void SetSizeX(float x);
	void SetSizeY(float y);
	void SetCollisonFlag(int state);
	void OffCollisionFlag();
	void CollisionCheck();
	void SetTargetCollision(CCollider2D* colide);
	//GET
	CCollider2D* GetTargetCollide();
	CObject* GetSourceObj();
	COMPONENT_TYPE GetColliderType() { return m_type; };
	const INT8 GetFlag() const { return m_Flag; }
	const Vector2 GetOffset() const { return m_vecOffset; }
	Vector2 GetCollisionSize() const { return Vector2((m_vecSize.x + m_vecOffset.x),(m_vecSize.y + m_vecOffset.y)); }

protected:
	CCollider2D* m_targetColide = nullptr;
	CObject* m_source = nullptr;	  //나를 갖고있는 오브젝트의 위치를 받기위한 포인터
	Vector2 m_vecSize;
	Vector2 m_vecOffset;

	//collsion flag에 따른 상태값이 바뀐다.
	INT8 m_Flag = 0b00000000;

};