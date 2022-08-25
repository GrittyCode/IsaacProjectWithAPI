#include "stdafx.h"
#include "Player.h"
#include "SoundMgr.h"

CPlayer::CPlayer(ObjectInfo objinfo, MoverInfo moverInfo)
	: CMover(objinfo,moverInfo),
	  m_PlayerInfo(PlayerInfo())
{
}

CPlayer::~CPlayer()
{
}

void CPlayer::Init()
{
	CObject::Init();
	GetTransform()->SetPosition(Vector2(m_ObjInfo.vecWorldPos.x, m_ObjInfo.vecWorldPos.y));

	m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX() * 0.4f, m_Transform->GetSizeY() - 15.0f);
	AddComponent(m_collide);

	//MOVER INFO ADD
	m_MoverInfo.vecAttackDiretion = Vector2(0, 0);
	m_MoverInfo.vecMoveDiretion = Vector2(0, 0);
	m_MoverInfo.fSpeed = 300.0f;
	m_MoverInfo.eAniAttackState = ANI_STATE::IDLE;
	m_MoverInfo.eAniMoveState = ANI_STATE::IDLE;
	
	//PLAYER INFO ADD
	m_PlayerInfo.ePlayerState = PLAYER_STATE::IDLE;
	m_PlayerInfo.iCurFrame = 0;
	m_PlayerInfo.fFrameStay = 0;
	m_PlayerInfo.fAttackSpeed = 3.0f;
	m_PlayerInfo.fAttackDelay = 1.0f / m_PlayerInfo.fAttackSpeed;
	m_PlayerInfo.fCurDelay = 0.0f;
	m_PlayerInfo.bAttack = true;
	m_PlayerInfo.bAttackON = false;
	m_PlayerInfo.fAcceleration = m_MoverInfo.fSpeed / 0.1f;
	m_PlayerInfo.bLeft = true;
	
	//PLAYER ITEM INVENTORY
	for (int i = 0; i < (int)ITEM_TYPE::ITME_TYPE_END; ++i)
	{
		m_mapInventory.insert({ (ITEM_TYPE)i, 0 });
	}


	//Move Animation

	//IDEL
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 0), Vector2(32, 32), false, Vector2(0, -20)), 0, 0, Vector2(32, 32), ANI_STATE::IDLE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)), 0, 0, Vector2(32, 32), ANI_STATE::IDLEBody));

	//MOVE(BODY)
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(352, 32), Vector2(32, 32), true, Vector2(0, 0)), 9, 0.1, Vector2(32, 32), ANI_STATE::UPMOVE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 32), Vector2(32, 32), false, Vector2(0, 0)), 9, 0.1f, Vector2(32, 32), ANI_STATE::DOWNMOVE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(352, 64), Vector2(32, 32), true, Vector2(0, 0)), 9, 0.1f, Vector2(32, 32), ANI_STATE::LEFTMOVE));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 64), Vector2(32, 32), false, Vector2(0, 0)), 9, 0.1f, Vector2(32, 32), ANI_STATE::RIGHTMOVE));

	//ATTACK(PACE)
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(128, 0), Vector2(32, 32), false, Vector2(0, -20)), 2, 0.15f, Vector2(32, 32), ANI_STATE::UPATTACK));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(0, 0), Vector2(32, 32), false, Vector2(0, -20)), 2, 0.15f, Vector2(32, 32), ANI_STATE::DOWNATTACK));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(288, 0), Vector2(32, 32), true, Vector2(0, -20)), 2, 0.15f, Vector2(32, 32), ANI_STATE::LEFTATTACK));
	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(64, 0), Vector2(32, 32), false, Vector2(0, -20)), 2, 0.15f, Vector2(32, 32), ANI_STATE::RIGHTATTACK));

	AddAniState(new CAnimation(SpriteInfoTag(m_ObjInfo.wpath, Vector2(128,192), Vector2(64, 64), false, Vector2(0, -20)), 0, 0, Vector2(64, 64), ANI_STATE::HUNT));
}

void CPlayer::Update()
{
	Move();
	Attack();
}

void CPlayer::FixedUpdate()
{
	CObject::FixedUpdate();
}

void CPlayer::Render(HDC hdc)
{
	Vector2 PlayerPos = GetTransform()->GetPosition();
	
	ObjectType eType;


	ImageAttributes imageAttributes;

	if (m_PlayerInfo.fFrameStay != 0)
	{
		float alphaPercent = 1;

		if (m_PlayerInfo.fFrameStay > 0.15f && m_PlayerInfo.fFrameStay < 0.3f)
		{
			alphaPercent = 0.f;
		}

		ColorMatrix colorMatrix =
		{
			  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			  0.0f, 0.0f, 0.0f, alphaPercent, 0.0f,
			  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
		};

		imageAttributes.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeDefault);

		if (m_PlayerInfo.fFrameStay > 0.3f)
		{
			m_PlayerInfo.fFrameStay = 0;
		}
	}

	if (m_PlayerInfo.ePlayerState != PLAYER_STATE::HUNT)
	{
		m_mapAniState.find(m_MoverInfo.eAniMoveState)->second->Update(GetTransform()->GetPosition(), &imageAttributes);
		m_mapAniState.find(m_MoverInfo.eAniAttackState)->second->Update(GetTransform()->GetPosition(), &imageAttributes);

	}
	else
	{
		if (m_PlayerInfo.fFrameStay == 0)
		{
			CSoundMgr::GetInstance()->MyPlaySound(L"hurt grunt 2.wav", CSoundMgr::CHANNELID::PLAYER_HURT);
		}

		m_mapAniState.find(m_MoverInfo.eAniAttackState)->second->Update(GetTransform()->GetPosition());
		m_PlayerInfo.fFrameStay += DELTA;

		if (m_PlayerInfo.fFrameStay > 0.2f)
		{
			m_PlayerInfo.ePlayerState = PLAYER_STATE::IDLE;
		}
	}

	//디버그모드
	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		static wchar_t chState[128];
		static wchar_t chCurFrame[4];

		memset(chState, 0, 128);
		memset(chCurFrame, 0, 4);

		//디버깅용 text
		if (m_PlayerInfo.ePlayerState == PLAYER_STATE::IDLE)
		{
			_tcscpy(chState, L"IDLE");
		}
		else if (m_PlayerInfo.ePlayerState == PLAYER_STATE::MOVE)
		{
			_tcscpy(chState, L"MOVE");
		}

		//펜설정
		HBRUSH	hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		HPEN CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(hdc, CurPen);		

		CObject::Render(hdc);

		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}

	//라스트 업데이트에서 해야하는데 흑흑 젠장 ;;; 그럼 그렇게 해 이 쉐리야
	if (m_PlayerInfo.ePlayerState != PLAYER_STATE::HUNT)
	{
		m_MoverInfo.eAniAttackState = ANI_STATE::IDLE;
		m_MoverInfo.eAniMoveState = ANI_STATE::IDLEBody;
		m_PlayerInfo.bAttackON = false;
	}
}


void CPlayer::Move()
{
	Vector2 vPastPos = GetTransform()->GetPosition();

	m_MoverInfo.vecMoveDiretion = Vector2(0, 0);

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::TAP
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.x = -1.0;
		m_MoverInfo.eAniMoveState = ANI_STATE::LEFTMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.x = m_MoverInfo.vecMoveDiretion.x == -1.0f ? 1.0f : 1.0f;
		m_MoverInfo.eAniMoveState = ANI_STATE::RIGHTMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.y = -1.0;
		m_MoverInfo.eAniMoveState = ANI_STATE::UPMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.y = m_MoverInfo.vecMoveDiretion.y == -1.0f ? 0 :  1.0f;
		m_MoverInfo.eAniMoveState = ANI_STATE::DOWNMOVE;
	}

	if ((CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::TAP)||
		(CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::TAP)||
		(CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::TAP)||
		(CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::TAP))
	{
		m_PlayerInfo.fCurSpeed = 0;
	}
	
	if(m_MoverInfo.vecMoveDiretion.Length() != 0.0f)
		m_MoverInfo.vecMoveDiretion = m_MoverInfo.vecMoveDiretion.Normalize();


	if (m_MoverInfo.vecMoveDiretion.x != 0 || m_MoverInfo.vecMoveDiretion.y != 0)
	{
		//m_PlayerInfo.ePlayerState = PLAYER_STATE::MOVE;

		//가속도
		if (m_PlayerInfo.fCurSpeed < m_MoverInfo.fSpeed)
		{
			m_PlayerInfo.fCurSpeed += m_PlayerInfo.fAcceleration * DELTA;
		}
		else
		{
			m_PlayerInfo.fCurSpeed = m_MoverInfo.fSpeed;
		}
	}
	else
	{
		//m_PlayerInfo.ePlayerState = PLAYER_STATE::IDLE;
	}

	//이동
	if (abs(m_MoverInfo.vecMoveDiretion.x) * abs(m_MoverInfo.vecMoveDiretion.y) != 1)
	{
		GetTransform()->
			SetPosition(
				Vector2(vPastPos.x + (DELTA * m_MoverInfo.vecMoveDiretion.x * m_PlayerInfo.fCurSpeed), 
					    vPastPos.y + (DELTA * m_MoverInfo.vecMoveDiretion.y * m_PlayerInfo.fCurSpeed)));
	}
	else
	{
		GetTransform()->
			SetPosition(Vector2(vPastPos.x + (DELTA * m_MoverInfo.vecMoveDiretion.x * m_PlayerInfo.fCurSpeed),
							    vPastPos.y + (DELTA * m_MoverInfo.vecMoveDiretion.y * m_PlayerInfo.fCurSpeed)));
	}
}

void CPlayer::Attack()
{
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::LEFT) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::LEFT) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(-1, 0);
		m_MoverInfo.eAniAttackState = ANI_STATE::LEFTATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::RIGHT) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::RIGHT) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(1, 0);
		m_MoverInfo.eAniAttackState = ANI_STATE::RIGHTATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::UP) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::UP) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(0, -1);
		m_MoverInfo.eAniAttackState = ANI_STATE::UPATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::DOWN) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::DOWN) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(0, 1);
		m_MoverInfo.eAniAttackState = ANI_STATE::DOWNATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (!m_PlayerInfo.bAttack)
	{
		m_PlayerInfo.fCurDelay += DELTA;

		if (m_PlayerInfo.fCurDelay > m_PlayerInfo.fAttackDelay)
		{
			m_PlayerInfo.fCurDelay = 0;
			m_PlayerInfo.bAttack = true;
		}
	}

	if (m_PlayerInfo.bAttackON && m_PlayerInfo.bAttack)
	{
		CreateObject(
			new CTear(m_MoverInfo.vecMoveDiretion, GetTransform()->GetPosition(),
			m_MoverInfo.vecAttackDiretion, m_PlayerInfo.fCurSpeed / 2, m_PlayerInfo.bLeft));

		m_PlayerInfo.bLeft = !m_PlayerInfo.bLeft;
		m_PlayerInfo.bAttack = false;
	}
}

void CPlayer::PickUpItem(ITEM_TYPE type)
{
	auto iter = m_mapInventory.find(type);
	//개수 늘리기
	(*iter).second++;
}



INT CPlayer::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::ENEMY)
	{
		m_PlayerInfo.ePlayerState = PLAYER_STATE::HUNT;
		m_MoverInfo.eAniAttackState = ANI_STATE::HUNT;
		m_MoverInfo.eAniMoveState = ANI_STATE::HUNT;
	}

	m_collide->OffCollisionFlag();

	return 0;
}