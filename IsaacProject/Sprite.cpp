#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite(wstring path, INT orderLayer)
{
	m_path = path;
	m_orderLayer = orderLayer;
}

CSprite::~CSprite()
{
	delete m_sprite;
	delete m_SpriteFileY;
	m_sprite = nullptr;
	m_SpriteFileY = nullptr;
	CImageMgr::GetInstance()->GetGraphics()->ReleaseHDC(CGameMgr::GetInstance()->GetMemDC());

}

void CSprite::Init()
{
	delete m_sprite;
	delete m_SpriteFileY;
	m_sprite = nullptr;
	m_SpriteFileY = nullptr;
	m_type = COMPONENT_TYPE::SPRITE;
	m_sprite = new Image(m_path.c_str());
	m_SpriteFileY = new Image(m_path.c_str());
	m_SpriteFileY->RotateFlip(Rotate180FlipY);
}


void CSprite::SetPath(wstring path)
{
	m_path = path;
}
