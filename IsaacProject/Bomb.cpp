#include "stdafx.h"
#include "Bomb.h"

CBomb::CBomb(ObjectInfo obj)
{
    m_ObjInfo = obj;
}

void CBomb::Init()
{
	CObject::Init();
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 20.0f), (m_Transform->GetSizeY() - 20.0f));
	AddComponent(m_collide);

	//ai설정 팩토리 과정으로 넘어갈예정

	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)),
		3, 0.03f, Vector2(32, 32), ANI_STATE::IDLE));
}

void CBomb::Update()
{
}

void CBomb::FixedUpdate()
{
}

void CBomb::LateUpdate()
{
}

void CBomb::Render(HDC hdc)
{
}

void CBomb::Release()
{
}

INT CBomb::CheckCollisionState()
{
    return 0;
}
