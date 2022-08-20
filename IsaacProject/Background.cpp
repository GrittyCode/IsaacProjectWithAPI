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
		DrawImage(m_sprite->GetSprite(), 0,0, 
			m_sprite->GetSprite()->GetWidth(), m_sprite->GetSprite()->GetHeight());
}

void CBackground::Release()
{
	CObject::Release();
}
