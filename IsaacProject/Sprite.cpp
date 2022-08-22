#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite(wstring path, INT orderLayer)
{
	m_path = path;
	m_orderLayer = orderLayer;
}

CSprite::~CSprite()
{
	m_sprite->operator delete;
	m_SpriteFileY->~Image();

	m_sprite = nullptr;
	m_SpriteFileY = nullptr;
}

void CSprite::Init()
{
	m_type = COMPONENT_TYPE::SPRITE;
	m_sprite = Image::FromFile(m_path.c_str());
	m_SpriteFileY = Image::FromFile(m_path.c_str());
	m_SpriteFileY->RotateFlip(Rotate180FlipY);
}

void CSprite::Update()
{
}

void CSprite::FixedUpdate()
{
}

void CSprite::Render(HDC hdc)
{
}

void CSprite::Release()
{
}

void CSprite::SetPath(wstring path)
{
	m_path = path;
}
