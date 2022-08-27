#pragma once
class CGameMgr
{
	SINGLETON(CGameMgr)
public:
	void Init();
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render();
	void SetGameMode(INT key) { m_mode = (GAME_MODE)key; };
	void Release();

	//GET
	GAME_MODE GetGameMode() { return m_mode; }
	BOOL GetWindowChanged() {return m_bWindowSizeChange;}
	HDC GetMemDC() { return m_hMemDC; }
	HBITMAP GetBuffer() { return m_hBuffer; };
private:	

	//HDC HANDLE
	HDC m_hdc = NULL;
	HDC m_hMemDC = NULL;

	//HBITMAP
	HBITMAP m_hBitmap = NULL;
	HBITMAP m_hBuffer = NULL;

	//클라이언트 크기
	POINT m_pWindowsize{0,0};
	Vec2 m_vResolution;

	GAME_MODE m_mode = GAME_MODE::GAME;
	BOOL m_bWindowSizeChange = false;
};

