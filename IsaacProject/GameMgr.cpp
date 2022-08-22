#include "stdafx.h"
#include "GameMgr.h"
#include "SoundMgr.h"

CGameMgr* CGameMgr::m_pInstance = nullptr;


void CGameMgr::Init()
{
	CSoundMgr::GetInstance()->PlayBGM(L"BGM.ogg");

	RECT rt = { 0,0, WINDOW_X,WINDOW_Y };

	GetCurrentDirectory(256, OriginDirectory);
	GetClientRect(g_hWnd, &rt);
	//클라이언트 크기 936 624 고정
	AdjustWindowRect(&rt, NULL, false);
	SetWindowPos(g_hWnd, nullptr, 0,0,WINDOW_X,WINDOW_Y,FALSE);
	GetWindowRect(g_hWnd, &rt);

	Scale = floorf((rt.right - rt.left) / (TILE_SIZE * 18.f));

	//윈도우 크기 관련 변수 초기화
	m_pWindowsize = { rt.right,rt.bottom };
	m_vResolution = POINT{rt.right, rt.bottom};

	//핸들 관련 변수 초기화
	m_hdc = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(m_hdc);
	m_hBuffer = CreateBitmap(WINDOW_X, WINDOW_Y, 1, 32, NULL);
	SelectObject(m_hMemDC, m_hBuffer);

	//tset.Init();

	//처음시작할 때는 게임 모드로 들어감
	m_mode = GAME_MODE::GAME;

	//매니저 생성(init자동)
	CKeyMgr::GetInstance();
	CTimeMgr::GetInstance();
	CCollisionMgr::GetInstance();
	CSceneMgr::GetInstance();
}

void CGameMgr::Update()
{
	CTimeMgr::GetInstance()->UpdateTime();

	//게임모드 설정
	if (CKeyMgr::GetInstance()->GetKeyState((int)KEY::F1) == KEY_STATE::TAP)
	{
		m_mode = GAME_MODE::GAME;
		CSceneMgr::GetInstance()->ChangeMode(GAME_MODE::GAME);
	}

	if (CKeyMgr::GetInstance()->GetKeyState((int)KEY::F2) == KEY_STATE::TAP)
	{
		m_mode = GAME_MODE::TOOL;
		CSceneMgr::GetInstance()->ChangeMode(GAME_MODE::TOOL);
	}

	if (CKeyMgr::GetInstance()->GetKeyState((int)KEY::F3) == KEY_STATE::TAP)
	{
		m_mode = GAME_MODE::DEBUG;
		CSceneMgr::GetInstance()->ChangeMode(GAME_MODE::DEBUG);
	}

	CKeyMgr::GetInstance()->Update();
	CSceneMgr::GetInstance()->Update();
}

void CGameMgr::FixedUpdate()
{
	m_bWindowSizeChange = false;

	CSceneMgr::GetInstance()->FixedUpdate();
}

void CGameMgr::LateUpdate()
{
}

void CGameMgr::Render()
{
	BitBlt(m_hdc, 0, 0, WINDOW_X, WINDOW_Y, m_hMemDC, 0, 0, SRCCOPY);
	CSceneMgr::GetInstance()->Render(m_hMemDC);

	//tset.Render(m_hMemDC);
	//m_hMemDC, m_hBuffer,L"../Resources/Sprites/Map/test.bmp");
}

void CGameMgr::Release()
{
	CSceneMgr::GetInstance()->Release();
	CSceneMgr::DestroyInst();
	CObjectMgr::DestroyInst();
	CCollisionMgr::DestroyInst();
	CKeyMgr::DestroyInst();
	CTimeMgr::DestroyInst();
	CImageMgr::DestroyInst();
	CCameraMgr::DestroyInst();
	CEffectMgr::DestroyInst();
}
