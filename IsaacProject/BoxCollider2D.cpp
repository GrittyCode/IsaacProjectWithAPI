#include "stdafx.h"
#include "BoxCollider2D.h"


CBoxCollider2D::CBoxCollider2D(CObject* target, float sizeX, float sizeY)
{
	m_Owner = target;
	m_vecSize.x = sizeX;
	m_vecSize.y = sizeY;
}

 RECT CBoxCollider2D::GetAABB()
{
	return RECT{ (LONG)(m_Owner->GetTransform()->GetPositionX() - m_vecSize.x + m_vecOffset.x),
				(LONG)(m_Owner->GetTransform()->GetPositionY() - m_vecSize.y + m_vecOffset.y),
				(LONG)(m_Owner->GetTransform()->GetPositionX() + m_vecSize.x + m_vecOffset.x),
				(LONG)(m_Owner->GetTransform()->GetPositionY() + m_vecSize.y + m_vecOffset.y)};
}

void CBoxCollider2D::Init()
{
	CCollider2D::Init();
	m_type = COMPONENT_TYPE::BOXCOLLIDE2D;
}

void CBoxCollider2D::Render(HDC hdc)
{
	Rectangle(hdc, 
		(INT)(m_Owner->GetTransform()->GetPositionX() - m_vecSize.x + m_vecOffset.x), 
		(INT)(m_Owner->GetTransform()->GetPositionY() - m_vecSize.y + m_vecOffset.y),
		(INT)(m_Owner->GetTransform()->GetPositionX() + m_vecSize.x + m_vecOffset.x),
		(INT)(m_Owner->GetTransform()->GetPositionY() + m_vecSize.y + m_vecOffset.y));

}