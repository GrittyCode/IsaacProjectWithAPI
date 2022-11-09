#pragma once
class CComponent
{
public:
	CComponent() { m_type = COMPONENT_TYPE::COMPONENT_TYPE_END; };
	virtual ~CComponent() {};
public:
	virtual void Init() = 0;
	virtual void Update() {};
	virtual void FixedUpdate() {};
	virtual void Render(HDC hdc) {};
	virtual void Release() = 0;
	COMPONENT_TYPE GetComponentType() { return m_type; }
protected:
	COMPONENT_TYPE m_type = COMPONENT_TYPE::COMPONENT_TYPE_END;
};