#pragma once

class CMenu
{
public:
	CMenu();
	~CMenu();

public:
	void Update();
	void Reder();

private:
	Image* m_MenuImage = nullptr;

	float m_fCurFlyDelay = 0;
	float m_fflyDelay = 0.1;

	int m_iflyCurFrame = 0;
	int m_iFlyFrame = 2;

	float m_fCurDelay = 0;
	float m_fDelay = 0.5;

	int m_iCurFrame = 0;
	int m_iFrame = 2;
};