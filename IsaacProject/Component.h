#pragma once
class CComponent
{
public:
	CComponent() { m_type = COMPONENT_TYPE::COMPONENT_TYPE_END; };
	virtual ~CComponent() {};
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() {  };
	COMPONENT_TYPE GetComponentType() { return m_type; }
protected:
	COMPONENT_TYPE m_type = COMPONENT_TYPE::COMPONENT_TYPE_END;
};