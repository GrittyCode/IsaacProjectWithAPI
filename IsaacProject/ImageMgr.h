#pragma once

enum class IMAGE_TYPE
{
	PLAYER,
	BOSS,
	TEAR,
	FLY,
	HUMAN,
	MOSQUITO,
	IMAGE_TYPE_END
};

class CImageMgr
{
	SINGLETONE(CImageMgr)

public:
	void Init();
	Image* GetImage(wstring path);
	Graphics* GetGraphics() { return m_graphics; }
	void Release();
private:
	map<wstring, Image*> m_mapImage;
	map<wstring, Image*>::iterator m_iter;
	Gdiplus::Graphics* m_graphics = nullptr;
};

