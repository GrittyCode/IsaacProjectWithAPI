#pragma once
class CSound
{
DECLARE_SINGLETON(CSound)

public:
	CSound();
	~CSound();

public:
	void SetSound(int All, int Gun, int Ui, int Bgm);
	int* GetSound() { return m_iSound; }

private:
	int m_iSound[4];
};

