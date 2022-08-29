#include "stdafx.h"
#include "Menu.h"
#include "SoundMgr.h"

CMenu::CMenu()
{
	m_MenuImage = new Image(L"../Resources/Play.png");
	CSoundMgr::GetInstance()->PlayBGM(L"title_screen_intro.ogg",CSoundMgr::CHANNELID::TITLE_BGM);
}

CMenu::~CMenu()
{
	CSoundMgr::GetInstance()->StopSound(CSoundMgr::CHANNELID::TITLE_BGM);
	
	CSoundMgr::GetInstance()->MyPlaySound(L"title_screen_jingle.ogg", CSoundMgr::CHANNELID::INTRO);

}

void CMenu::Update()
{
	while (1)
	{
		CKeyMgr::GetInstance()->Update();

		if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::SPCAE) == KEY_STATE::TAP)
		{
			return;
		}

		CTimeMgr::GetInstance()->UpdateTime();
		Reder();
	}
}

void CMenu::Reder()  
{
	HDC hdc = GetDC(g_hWnd);
	HDC hdc2 = CreateCompatibleDC(hdc);

	HBITMAP hBITMAP;
	HBITMAP hBITMAP2;

	hBITMAP = CreateBitmap(WINDOW_X, WINDOW_Y, 1, 32, NULL);
	hBITMAP2 = CreateCompatibleBitmap(hdc, WINDOW_X, WINDOW_Y);

	SelectObject(hdc, hBITMAP);
	SelectObject(hdc2, hBITMAP2);

	Graphics g(hdc2);

	g.DrawImage(m_MenuImage, Rect(0, 0, 480 * 2, 270 * 2 + 100), 0, 0, 480, 270, UnitPixel);
	g.DrawImage(m_MenuImage, Rect(0, 0, 480*2, 200), 0,  270, 480, 108, UnitPixel);

	//animation
	g.DrawImage(m_MenuImage, Rect(310, 200, 300 , 300), (m_iCurFrame * 160), 380, 160, 160, UnitPixel);

	//fly
	g.DrawImage(m_MenuImage, Rect(650, 400, 250, 150), 350, 380 + (80 * m_iflyCurFrame), 80, 80, UnitPixel);

	m_fCurFlyDelay += DELTA;
	m_fCurDelay += DELTA;

	if (m_fCurFlyDelay > 0.05f)
	{
		++m_iflyCurFrame;
		m_fCurFlyDelay = 0;

		if (m_iflyCurFrame == 2)
		{
			m_iflyCurFrame = 0;
		}
	}

	if (m_fCurDelay > 0.1f)
	{
		++m_iCurFrame;
		m_fCurDelay = 0;

		if (m_iCurFrame == 2)
		{
			m_iCurFrame = 0;
		}
	}

	BitBlt(hdc, 0, 0, WINDOW_X, WINDOW_Y, hdc2, 0,0, SRCCOPY);

	g.ReleaseHDC(hdc2);

	DeleteObject(hBITMAP);
	DeleteObject(hBITMAP2);

	DeleteDC(hdc);
	DeleteDC(hdc2);
}
