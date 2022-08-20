#pragma once
class CImageMgr
{
	SINGLETONE(CImageMgr)

public:
	void Init() { m_graphics = new Graphics(CGameMgr::GetInstance()->GetMemDC()); }
	Image* GetImage(wstring path);
	Graphics* GetGraphics() { return m_graphics; }
	void Release();
private:
	map<wstring, Image*> m_mapImage;
	map<wstring, Image*>::iterator m_iter;
	Gdiplus::Graphics* m_graphics = nullptr;
};

