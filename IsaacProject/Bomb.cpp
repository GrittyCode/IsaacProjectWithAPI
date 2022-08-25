#include "stdafx.h"
#include "Bomb.h"

CBomb::CBomb(ObjectInfo obj)
	:CItem(obj)
{
	CObject::Init();
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 20.0f), (m_Transform->GetSizeY() - 20.0f));
	AddComponent(m_collide);

	m_fCurDelay = 0;
	m_iCurFrame = 0;

	m_iFramelimit = 16;
	m_fAniDelay = 0.5f;
}

void CBomb::Init()
{
}

void CBomb::Update()
{
	m_fCurDelay += DELTA;

	if (m_fCurDelay > m_fAniDelay)
	{
		++m_iCurFrame;
		m_fCurDelay = 0;
	}

	if (m_iCurFrame == m_iFramelimit)
	{
		//½Ã°£ Áö³ª¸é¼­ »èÁ¦ÇÏ°í ÆøÆÈÀÌÆåÆ®
		DeleteObject(this);
		CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/Effect/effect_029_explosion.png", Vector2(0, 0), Vector2(96, 96), false, Vector2(0, 0)),
			5, 5.0f, Vector2(64, 64), ANI_STATE::DEAD));
	}
}

void CBomb::FixedUpdate()
{
}

void CBomb::LateUpdate()
{
}

void CBomb::Render(HDC hdc)
{
	Vector2 vecTemp = GetTransform()->GetPosition();

	ImageAttributes imgAttr;
	imgAttr.SetColorKey(Color(245, 0, 245), Color(255, 10, 255));

	CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_sprite->GetSprite(),
		Rect((UINT)(vecTemp.x - 32),
			(UINT)(vecTemp.y - 32),
			(UINT)(64),
			(UINT)(64)),
			(UINT)(m_iCurFrame * 53),
			(UINT)0,
			(UINT)53,
			(UINT)61,
			UnitPixel, &imgAttr);	
}

void CBomb::Release()
{
}

INT CBomb::CheckCollisionState()
{
    return 0;
}
