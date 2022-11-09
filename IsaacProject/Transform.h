#pragma once
class CTransform : public CComponent
{
public:
	CTransform() { m_vecPos = Vector2(0.0f, 0.0f); m_vecSize = Vector2(0.0f, 0.0f); m_vecRot = Vector2(0.0f, 0.0f); m_vecLook = Vector2(0.0f, 0.0f); };
	CTransform(Vector2 pos, Vector2 size) :m_vecPos(pos), m_vecSize(size) { m_vecRot = Vector2(0.0f, 0.0f); m_vecLook = Vector2(0.0f, 0.0f); };
	CTransform(Vector2 pos, Vector2 rot, Vector2 look) {};
	virtual ~CTransform() {};
	virtual void Release() override {};
public:
	//GET
	Vector2 GetPosition() { return m_vecPos; } const
	float GetPositionX() { return m_vecPos.x; }
	float GetPositionY() { return m_vecPos.y; }
	
	Vector2 GetLookVec() { return m_vecLook; } const
	float GetLookX() { return m_vecLook.x; } const
	float GetLookY() { return m_vecLook.y; } const
	
	float GetSizeX() { return m_vecSize.x; } const
	float GetSizeY() { return m_vecSize.y; } const
	
	Vector2 GetRotation() { return m_vecRot; } const
	float GetRotationX() { return m_vecRot.x; }
	float GetRotationY() { return m_vecRot.y; }
	
	//SET
	void SetPosition(Vector2 pos) { m_vecPos = pos;}
	void SetPositionX(float pos) { m_vecPos.x = pos; }
	void SetPositionY(float pos) { m_vecPos.y = pos; }
	void SetLook(Vector2 look) {  }
	void SetRotation(Vector2 rot) { }
	void SetSizeX(float x) {  m_vecSize.x = x; }
	void SetSizeY(float y) {  m_vecSize.y = y; }
	//추가 예정	
	virtual void Init() override;

private:
	Vector2 m_vecSize;
	Vector2 m_vecPos;
	Vector2 m_vecRot;
	Vector2 m_vecLook;
};
