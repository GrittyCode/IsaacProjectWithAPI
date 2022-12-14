#include "stdafx.h"
#include "Tear.h"
#include "SoundMgr.h"

CTear::CTear(Vector2 movediretiony,Vector2 worldpos, Vector2 attackdirection,float playerspeed, bool m_Left)
{
	m_MoverInfo.fSpeed = 400.0f;
	m_vecFireEye = Vector2(0, 0);
	FireEyeSet(m_Left, attackdirection);
	worldpos.x += m_vecFireEye.x;
	worldpos.y += m_vecFireEye.y - 20;
	m_ObjInfo.vecWorldPos = worldpos;
	m_MoverInfo.vecAttackDiretion = VectorSum(movediretiony, attackdirection,playerspeed, m_MoverInfo.fSpeed);
	m_MoverInfo.vecAttackDiretion.Normalize();
	m_fDistance = 300.0f;

	if ((movediretiony.x == attackdirection.x) && (movediretiony.y == attackdirection.y))
	{
		m_MoverInfo.fSpeed += playerspeed;
		m_fDistance += playerspeed;
	}

	m_bGravity = false;
	m_fCurDeley = 0;
	m_iCurPrame = 0;
	m_bSound = false;
	m_ObjInfo.type = OBJECT_TYPE::PLAYER_TEAR;
}

CTear::~CTear()
{

}

void CTear::Init()
{
	m_ObjInfo.wpath = L"../Resources/Sprites/tears.png";
	m_ObjInfo.vecSize = Vector2(32, 32);
	CObject::Init();

	GetTransform()->SetPosition(Vector2(m_ObjInfo.vecWorldPos.x + (m_MoverInfo.vecAttackDiretion.x * 25), m_ObjInfo.vecWorldPos.y + (m_MoverInfo.vecAttackDiretion.y * 25)));
	m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX() - 22, m_Transform->GetSizeY() - 21);
	AddComponent(m_collide);

	CSoundMgr::GetInstance()->MyPlaySound(L"Tear.wav", CSoundMgr::CHANNELID::TEAR_FIRE);
}

void CTear::Update()
{
		Move();
		//일정거리시 소멸
		if (DistanceMeasure(m_ObjInfo.vecWorldPos, GetTransform()->GetPosition()) > m_fDistance)
		{
			if (!m_bSound)
			{
				//splatter 0
				//Tear_Dead_Time
				CSoundMgr::GetInstance()->MyPlaySound(L"splatter0.wav", CSoundMgr::CHANNELID::TEAR_DEAD);
				m_bSound = true;
			}

			CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/tear.png", Vector2(0, 0), Vector2(64, 64), false, Vector2(0, 0)),
				11,
				0.05f,
				Vector2(32, 32),
				ANI_STATE::DEAD,
				GetTransform()->GetPosition()));

			if (!IsDead())
			{
				DeleteObject(this);
			}
		}

}
void CTear::Render(HDC hdc)
{
	CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_sprite->GetSprite(), Rect((UINT)GetTransform()->GetPositionX() - 32, (UINT)GetTransform()->GetPositionY() - 32, 64, 64),
		160, 0, 32, 32, UnitPixel);

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

void CTear::Move()
{
	Vector2 Bulltepos = GetTransform()->GetPosition();

	if (DistanceMeasure(m_ObjInfo.vecWorldPos, GetTransform()->GetPosition()) < m_fDistance - 50)
	{
		GetTransform()->SetPosition(Vector2(Bulltepos.x + (m_MoverInfo.vecAttackDiretion.x * m_MoverInfo.fSpeed * DELTA), Bulltepos.y + (m_MoverInfo.vecAttackDiretion.y * m_MoverInfo.fSpeed * DELTA)));
	}
	else
	{
		GetTransform()->SetPosition(Vector2(Bulltepos.x + (m_MoverInfo.vecAttackDiretion.x * m_MoverInfo.fSpeed * DELTA), Bulltepos.y + (m_MoverInfo.vecAttackDiretion.y * m_MoverInfo.fSpeed * DELTA) + 2));
	}
}

INT CTear::CheckCollisionState()
{
	if ((m_collide->GetFlag() & (UINT)COLLISION_FLAG::OBSTACLE) || 
		(m_collide->GetFlag() & (UINT)COLLISION_FLAG::ENEMY))
	{
		if (!m_bSound)
		{
			m_bSound = true;
			CSoundMgr::GetInstance()->MyPlaySound(L"Tear_Dead_Time.wav", CSoundMgr::CHANNELID::TEAR_DEAD);
		}

		CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/tear.png", Vector2(0, 0), Vector2(64, 64), false, Vector2(0, 0)),
			11,
			0.05f,
			Vector2(32, 32),
			ANI_STATE::DEAD, GetTransform()->GetPosition()));

		if (!IsDead())
		{
			DeleteObject(this);
		}
	}

	if ((m_collide->GetFlag() & (UINT)COLLISION_FLAG::BOMB))
	{
		if (!m_bSound)
		{
			m_bSound = true;
			CSoundMgr::GetInstance()->MyPlaySound(L"Tear_Dead_Time.wav", CSoundMgr::CHANNELID::TEAR_DEAD);
		}

		CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/tear.png", Vector2(0, 0), Vector2(64, 64), false, Vector2(0, 0)),
			11,
			0.05f,
			Vector2(32, 32),
			ANI_STATE::DEAD, GetTransform()->GetPosition()));

		if (!IsDead())
		{
			DeleteObject(this);
		}
	}

	m_collide->OffCollisionFlag();

    return 0;
}

void CTear::FireEyeSet(bool left, Vector2 attackdirection)
{

	if (attackdirection.x == 1 || attackdirection.x == -1)
	{
		if (left)
		{
			m_vecFireEye.y -= 6.0f;
		}
		else
		{
			m_vecFireEye.y += 6.0f;
		}
	}

	else if (attackdirection.y == 1 || attackdirection.y == -1)
	{
		if (left)
		{
			m_vecFireEye.x -= 6.0f;
		}
		else
		{
			m_vecFireEye.x += 6.0f;
		}
	}
}