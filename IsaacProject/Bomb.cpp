#include "stdafx.h"
#include "Bomb.h"

CBomb::CBomb(ObjectInfo obj)
	:CObject(obj)
{
	m_fCurDelay = 0;
	m_iCurFrame = 0;

	m_iFramelimit = 16;
	m_fAniDelay = 0.07f;
}

void CBomb::Init()
{
	CObject::Init();
	m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX() - 15, m_Transform->GetSizeY() - 15);
	AddComponent(m_collide);
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
		//시간 지나면서 삭제하고 폭팔이펙트
		DeleteObject(this);
		
		m_sprite->SetPath(L"../Resources/Sprites/Effect/effect_017_bombradius.png");
		m_sprite->Init();

		CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_sprite->GetSprite(),
			Rect((INT)m_ObjInfo.vecWorldPos.x - 20.f,(INT)m_ObjInfo.vecWorldPos.y, 96, 32),
				0, 0, 96, 32,
				UnitPixel);
		m_Transform->SetPosition(Vector2(m_Transform->GetPosition().x, m_Transform->GetPosition().y - 40.0f));

		CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/Effect/effect_explosion.png", Vector2(0, 0), Vector2(96,96), false, Vector2(0, 0)),
			12, 0.05f, Vector2(64, 64), ANI_STATE::DEAD, m_Transform->GetPosition()));

		m_bExplosion = true;
		cout << "시러";
	}
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
		Rect((UINT)(vecTemp.x - 25.f),
			(UINT)(vecTemp.y - 30.f),
			45,
			45),
			m_iCurFrame * 53,
			0,
			53,
			61,
			UnitPixel, &imgAttr);	

	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HBRUSH hOldBrush;
		//펜설정
		HPEN hOldPen;
		HPEN CurPen;

		CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		hOldPen = (HPEN)SelectObject(hdc, CurPen);
		hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}

void CBomb::Explode()
{
	//얘가 터질때 boxcollide를 생성해 충돌 처리를 만들고 
	
}


INT CBomb::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER_TEAR)
	{
		CTear* Temp = dynamic_cast<CTear*>(m_collide->GetTargetObj(OBJECT_TYPE::PLAYER_TEAR));
		m_Transform->SetPosition(m_Transform->GetPosition() + (Temp->GetoAttackDir() * DELTA * Temp->GetSpeed() * 3));
	}
	else if(m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{	
			CPlayer* Temp = dynamic_cast<CPlayer*>(m_collide->GetTargetObj(OBJECT_TYPE::PLAYER));
			m_Transform->SetPosition(m_Transform->GetPosition() + (Temp->GetoMoveDir() * DELTA * Temp->GetSpeed() * 3));
	}

	m_collide->OffCollisionFlag();


    return 0;
}
