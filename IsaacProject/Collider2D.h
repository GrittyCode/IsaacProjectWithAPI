#pragma once

class CObject;

class CCollider2D : public CComponent
{
public:
	//생성 소멸자
	CCollider2D() {};
	virtual ~CCollider2D() {};

	virtual void Init();
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() override {}
	//SET
	void SetOffsetX(float x) { m_vecOffset.x = x; };
	void SetOffsetY(float y) { m_vecOffset.y = y; };
	void SetSizeX(float x)	 { m_vecSize.x = x; };
	void SetSizeY(float y)   { m_vecSize.y = y; };
	void SetCollisonFlag(int state) { m_Flag |= state; };
	void CollisionCheck();
	void OffCollisionFlag();
	void PushTargetCollision(CCollider2D* colide);
	//GET
	CCollider2D* GetTarget(OBJECT_TYPE type);
	CObject* GetOwnerObj() { return m_Owner; };
	OBJECT_TYPE GetOwnerType();
	COMPONENT_TYPE GetColliderType() { return m_type; };
	const INT16 GetFlag() const { return m_Flag; }
	const Vector2 GetOffset() const { return m_vecOffset; }
	Vector2 GetCollisionSize() const { return Vector2((m_vecSize.x + m_vecOffset.x),(m_vecSize.y + m_vecOffset.y)); }

protected:
	map<OBJECT_TYPE, CCollider2D*> m_mapTarget;
	CObject* m_Owner = nullptr;	  //나를 갖고있는 오브젝트의 위치를 받기위한 포인터
	Vector2 m_vecSize;
	Vector2 m_vecOffset;
	//collsion flag에 따른 상태값이 바뀐다.
	INT16 m_Flag = 0;

};