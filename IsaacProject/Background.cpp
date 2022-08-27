#include "stdafx.h"
#include "Background.h"

CBackground::CBackground()
{
	m_ObjInfo = ObjectInfo();
}

CBackground::CBackground(ObjectInfo objInfo)
{
	m_ObjInfo = objInfo;
}

void CBackground::Init()
{
	CObject::Init();
	GetTransform()->SetPosition(Vector2(m_ObjInfo.vecWorldPos.x, m_ObjInfo.vecWorldPos.y));

	m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX() - 10.0f, m_Transform->GetSizeY() - 20.0f);
	AddComponent(m_collide);
}

void CBackground::Update()
{
}

void CBackground::FixedUpdate()
{
}

void CBackground::Render(HDC hdcd)
{
	CImageMgr::GetInstance()->GetGraphics()->
		DrawImage(m_sprite->GetSprite(), 
			float(WINDOW_X - m_sprite->GetSprite()->GetWidth()) / 2.0f, 
			float(WINDOW_Y - m_sprite->GetSprite()->GetHeight()) / 2.0f,
			m_sprite->GetSprite()->GetWidth(), 
			m_sprite->GetSprite()->GetHeight());
}

void CBackground::Release()
{
}
