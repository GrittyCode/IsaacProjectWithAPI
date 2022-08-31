#pragma once
struct Spriteinfo
{
	Spriteinfo(Vector2 _start, Vector2 _size, Vector2 _pos):
		startVec(_start),
		uiPos(_pos),
		sizeVec(_size)
	{

	}

	Spriteinfo()
	{

	}

	Vector2 startVec;
	Vector2 sizeVec;
	Vector2 uiPos;
};

class CUiMgr
{
	//Player 연동되어 화면에 나와있는 UI 이미지들이 달라지게 된다.
	SINGLETON(CUiMgr)
public:
	void Init();
	void Update();
	void RenderBombState();
	void RenderKeyState();
	void RenderCoinState();
	
	void Release();
	void Render(HDC hdc);

	int SelectTenNum(ITEM_TYPE type);
	int SelectNum(ITEM_TYPE type);


private:
	Image* m_hudImg;
	Image* m_numberImg;
	//COIN
	Spriteinfo m_coinInfo;
	//KEY
	Spriteinfo m_keyInfo;
	//BOMB
	Spriteinfo m_bombInfo;
	//Number
	Spriteinfo m_numberInfo;
};

