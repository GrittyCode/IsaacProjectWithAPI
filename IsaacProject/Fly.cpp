#include "stdafx.h"
#include "Fly.h"

CFly::CFly(ObjectInfo objInfo, EnemyInfo enemyinfo)
	:CEnemy(objInfo, enemyinfo)
{
}

CFly::~CFly()
{
}

void CFly::Init()
{
	//component set
	CObject::Init();
	m_collide = new CBoxCollider2D(this, (m_Transform->GetSizeX() - 20.0f), (m_Transform->GetSizeY() - 20.0f));
	AddComponent(m_collide);

	//ai설정 팩토리 과정으로 넘어갈예정
	m_pAI = new AI(this);
	m_pAI->AddState(new CIdleState);
	m_pAI->AddState(new CTraceState);
	m_pAI->AddState(new DeadState);
	m_pAI->AddState(new CHuntstate);
	m_pAI->ChangeState(AI_STATE::IDLE);

	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)),
		3, 0.03f, Vector2(32, 32), ANI_STATE::IDLE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)),
		3, 0.03f, Vector2(32, 32), ANI_STATE::MOVE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)),
		3, 0.03f, Vector2(32, 32), ANI_STATE::HUNT));
	/*AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0,64), Vector2(64, 64), false, Vector2(0, 0)),
		4, 0.3f, Vector2(32, 32), ANI_STATE::DEAD));*/

	m_AniState = ANI_STATE::IDLE;
	//m_vecAniState.push_back(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 0), Vector2(32, 32), false, Vector2(0, -20)), 0, 0, Vector2(32, 32)));
}

void CFly::Update()
{
	//애니메이션 프레임조정
	m_pAI->Update();
}


void CFly::Render(HDC hdc)
{
	//CImageMgr::GetInstance()->GetGraphics()->DrawImage(
	//	m_sprite->GetSprite(),
	//	Rect((UINT)m_Transform->GetPositionX() - 32, (UINT)m_Transform->GetPositionY() - 32, 64, 64),
	//	32 + (m_iFrame * 32), 32, 32, 32,
	//	UnitPixel);

	m_mapAniState.find(m_AniState)->second->Update(m_Transform->GetPosition());

	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		HBRUSH hOldBrush;
		//펜설정
		HPEN hOldPen;
		HPEN CurPen;

		if (m_collide != nullptr)
		{
			CurPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			hOldPen = (HPEN)SelectObject(hdc, CurPen);
			hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		}
		else
		{
			CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
			hOldPen = (HPEN)SelectObject(hdc, CurPen);
			hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		}

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
}

void CFly::Release()
{
	CObject::Release();
}
