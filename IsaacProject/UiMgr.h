#pragma once
class UiMgr
{
	//Player�� �����Ǿ� ȭ�鿡 �����ִ� UI �̹������� �޶����� �ȴ�.
	SINGLETON(UiMgr)
public:
	void Init() {}
	void Update();
	void Render(HDC hdc);

private:
	
};

