#pragma once
class UiMgr
{
	//Player와 연동되어 화면에 나와있는 UI 이미지들이 달라지게 된다.
	SINGLETON(UiMgr)
public:
	void Init() {}
	void Update();
	void Render(HDC hdc);

private:
	
};

