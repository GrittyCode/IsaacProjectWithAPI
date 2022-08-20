#include "stdafx.h"
#include "Player.h"

CPlayer::CPlayer(ObjectInfo objinfo, MoverInfo moverInfo)
	: CMover(objinfo,moverInfo),
	  m_PlayerInfo(PlayerInfo())
{
}

CPlayer::~CPlayer()
{
	CObject::Release();
}

void CPlayer::Init()
{
	CObject::Init();
	GetTransform()->SetPosition(Vector2(m_ObjInfo.vecWorldPos.x, m_ObjInfo.vecWorldPos.y));

	m_collide = new CBoxCollider2D(this, m_Transform->GetSizeX() * 0.4f, m_Transform->GetSizeY() - 20.0f);
	AddComponent(m_collide);


	//MOVER INFO ADD
	m_MoverInfo.vecAttackDiretion = Vector2(0, 0);
	m_MoverInfo.vecMoveDiretion = Vector2(0, 0);
	m_MoverInfo.fSpeed = 300.0f;
	m_MoverInfo.eAniAttackState = ANISTATE::IDLE;
	m_MoverInfo.eAniMoveState = ANISTATE::IDLE;
	
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

	//이동
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(0, 0), false));//IDLE
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(352,32),true));//UPMOVE
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(0, 32), false));//DOWNMOVE
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(352, 64), true));//LEFTMOVE
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(0, 64), false));//RIGHTMOVE

	//공격방향
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(128, 0), false));//UPATTACK
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(0, 0), false));//DOWNATTACK
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(288, 0), true));//LEFTATTACK
	m_MoverInfo.vecActAniState.push_back(ActAniInfo(Vector2(64, 0), false));//RIGHTATTACK
}

void CPlayer::Update()
{
	m_PlayerInfo.fFrameStay += DELTA;
	Move();
	Attack();
}

void CPlayer::FixedUpdate()
{
	CObject::FixedUpdate();
}

void CPlayer::Render(HDC hdc)
{
	if (m_PlayerInfo.ePlayerState == PLAYER_STATE::IDLE)
	{
		Draw(0, m_MoverInfo.vecActAniState[(UINT)ANISTATE::DOWNMOVE], 0, 0, 0, 0);
		AttackRender(hdc);
	}
	else if (m_PlayerInfo.ePlayerState == PLAYER_STATE::MOVE)
	{
		MoveRender(hdc);
		AttackRender(hdc);
	}
	else if (m_PlayerInfo.ePlayerState == PLAYER_STATE::HUNT)
	{

	}
	else if (m_PlayerInfo.ePlayerState == PLAYER_STATE::DEAD)
	{

	}

	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::DEBUG)
	{
		wchar_t chState[128];
		wchar_t chCurFrame[4];

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
}

INT CPlayer::CheckCollisionState()
{
	m_collide->OffCollisionFlag();

	return 0;
}


void CPlayer::MoveRender(HDC hdc)
{
	Vector2 PlayerPos = GetTransform()->GetPosition();
	ActAniInfo MoveAniInfo = m_MoverInfo.vecActAniState[(UINT)m_MoverInfo.eAniMoveState];

	//몸체
	if (MoveAniInfo.bFilp == true)
	{
		ReverseDraw(m_PlayerInfo.iCurFrame, MoveAniInfo,0,0,0,0);
	}
	else
	{
		Draw(m_PlayerInfo.iCurFrame, MoveAniInfo,0,0,0,0);
	}
}

void CPlayer::AttackRender(HDC hdc)
{
	Vector2 PlayerPos = GetTransform()->GetPosition();
	ANISTATE eTemp = m_MoverInfo.eAniAttackState;
	ActAniInfo AttackAniInfo = m_MoverInfo.vecActAniState[(UINT)m_MoverInfo.eAniAttackState];
	m_MoverInfo.eAniAttackState = ANISTATE::DOWNATTACK;

	//얼굴
	if (m_PlayerInfo.bAttackON && m_PlayerInfo.bAttack)//공격조건 달성시
	{
		if (AttackAniInfo.bFilp == true)
		{
			ReverseDraw(0, AttackAniInfo, 0, -20, -32, 0);
		}
		else
		{
			Draw(0, AttackAniInfo, 0, -20, +32, 0);
		}
		m_PlayerInfo.bAttack = false;
	}
	else//공격하지안하고 바라보기만
	{
		if (m_PlayerInfo.fCurDelay != 0 && m_PlayerInfo.fCurDelay < 0.1f)
		{
			m_MoverInfo.eAniAttackState = eTemp;
			if (AttackAniInfo.bFilp == true)
			{
				ReverseDraw(0, AttackAniInfo, 0, -20, -32, 0);
			}
			else
			{
				Draw(0, AttackAniInfo, 0, -20, +32, 0);
	
			}
		}
		else
		{
			if (AttackAniInfo.bFilp == true)
			{
				ReverseDraw(0, AttackAniInfo, 0, -20, 0, 0);
			}
			else
			{
				Draw(0, AttackAniInfo, 0, -20, 0, 0);
			}
		}
	}
	m_PlayerInfo.bAttackON = false;
}


void CPlayer::Move()
{
	Vector2 vPastPos = GetTransform()->GetPosition();

	m_MoverInfo.vecMoveDiretion = Vector2(0, 0);

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::TAP
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.x = -1;

		if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::TAP)
		{
			m_PlayerInfo.iCurFrame = 0;
			m_PlayerInfo.fFrameStay = 0;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::A) == KEY_STATE::HOLD)
		{
			if (m_PlayerInfo.fFrameStay > 0.1)
			{
				++m_PlayerInfo.iCurFrame;
				m_PlayerInfo.fFrameStay = 0;
			}
		}

		m_MoverInfo.eAniMoveState = ANISTATE::LEFTMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.x = m_MoverInfo.vecMoveDiretion.x == -1.f ? 0.f : 1.f;
		 
		if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::TAP)
		{
			m_PlayerInfo.iCurFrame = 0;
			m_PlayerInfo.fFrameStay = 0;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::D) == KEY_STATE::HOLD)
		{
			if (m_PlayerInfo.fFrameStay > 0.1)
			{
				++m_PlayerInfo.iCurFrame;
				m_PlayerInfo.fFrameStay = 0;
			}
		}
		m_MoverInfo.eAniMoveState = ANISTATE::RIGHTMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.y = -1;

		if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::TAP)
		{
			m_PlayerInfo.iCurFrame = 0;
			m_PlayerInfo.fFrameStay = 0;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::W) == KEY_STATE::HOLD)
		{
			if (m_PlayerInfo.fFrameStay > 0.1)
			{
				++m_PlayerInfo.iCurFrame;
				m_PlayerInfo.fFrameStay = 0;
			}
		}

		m_MoverInfo.eAniMoveState = ANISTATE::UPMOVE;
	}
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecMoveDiretion.y = m_MoverInfo.vecMoveDiretion.y == -1 ? 0 :  1;

		if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::TAP)
		{
			m_PlayerInfo.iCurFrame = 0;
			m_PlayerInfo.fFrameStay = 0;
		}
		else if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::S) == KEY_STATE::HOLD)
		{
			if (m_PlayerInfo.fFrameStay > 0.1)
			{
				++m_PlayerInfo.iCurFrame;
				m_PlayerInfo.fFrameStay = 0;
			}
		}

		m_MoverInfo.eAniMoveState = ANISTATE::DOWNMOVE;
	}

	//프레임을 벗어나면 초기화
	if (m_PlayerInfo.iCurFrame > 9)
	{ 
		m_PlayerInfo.iCurFrame = 0;
	}
	
	if(m_MoverInfo.vecMoveDiretion.Length() != 0.0f)
		m_MoverInfo.vecMoveDiretion = m_MoverInfo.vecMoveDiretion.Normalize();


	if (m_MoverInfo.vecMoveDiretion.x != 0 || m_MoverInfo.vecMoveDiretion.y != 0)
	{
		m_PlayerInfo.ePlayerState = PLAYER_STATE::MOVE;

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
		m_PlayerInfo.ePlayerState = PLAYER_STATE::IDLE;
		m_PlayerInfo.iCurFrame = 0;
		m_PlayerInfo.fFrameStay = 0;
		m_PlayerInfo.fCurSpeed = 0;
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
		m_MoverInfo.eAniAttackState = ANISTATE::LEFTATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::RIGHT) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::RIGHT) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(1, 0);
		m_MoverInfo.eAniAttackState = ANISTATE::RIGHTATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::UP) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::UP) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(0, -1);
		m_MoverInfo.eAniAttackState = ANISTATE::UPATTACK;
		m_PlayerInfo.bAttackON = true;
	}

	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::DOWN) == KEY_STATE::TAP 
		|| CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::DOWN) == KEY_STATE::HOLD)
	{
		m_MoverInfo.vecAttackDiretion = Vector2(0, 1);
		m_MoverInfo.eAniAttackState = ANISTATE::DOWNATTACK;
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

		CObjectMgr::GetInstance()->
			AddObject(new CTear(m_MoverInfo.vecMoveDiretion,GetTransform()->GetPosition(), 
								 m_MoverInfo.vecAttackDiretion,
								 m_PlayerInfo.fCurSpeed /2, m_PlayerInfo.bLeft));
		m_PlayerInfo.bLeft = !m_PlayerInfo.bLeft;
	}
}