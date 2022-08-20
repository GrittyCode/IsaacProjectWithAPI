#include "stdafx.h"
#include "BoxCollider2D.h"

CBoxCollider2D::CBoxCollider2D(CObject* target, float sizeX, float sizeY)
{
	m_source = target;
	m_vecSize.x = sizeX;
	m_vecSize.y = sizeY;
}

CBoxCollider2D::CBoxCollider2D()
{
}

CBoxCollider2D::~CBoxCollider2D()
{
}

const Square CBoxCollider2D::GetAABB() const
{
	return Square( (m_source->GetTransform()->GetPosition() + m_vecOffset), m_vecSize);
}

void CBoxCollider2D::Init()
{
	m_type = COMPONENT_TYPE::BOXCOLLIDE2D;
}

void CBoxCollider2D::Update()
{
}

void CBoxCollider2D::FixedUpdate()
{
}

void CBoxCollider2D::Render(HDC hdc)
{
	Rectangle(hdc, 
		(INT)(m_source->GetTransform()->GetPositionX() - m_vecSize.x + m_vecOffset.x), 
		(INT)(m_source->GetTransform()->GetPositionY() - m_vecSize.y + m_vecOffset.y),
		(INT)(m_source->GetTransform()->GetPositionX() + m_vecSize.x + m_vecOffset.x),
		(INT)(m_source->GetTransform()->GetPositionY() + m_vecSize.y + m_vecOffset.y));

}