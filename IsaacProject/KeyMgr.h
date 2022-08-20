#pragma once

class CKeyMgr
{
	SINGLETONE(CKeyMgr)
public:
	void Init();
	void Update();
	void FixedUpdate();
	void Render();

public:
	KEY_STATE GetKeyState(int key);

private:
	vector<tKeyInfo> m_vecKey;
};