#include "stdafx.h"
#include "Sound.h"

IMPLEMENT_SINGLETON(CSound)

CSound::CSound()
{
	for (int i = 0; i < 4; ++i)
		m_iSound[i] = 100;
}

CSound::~CSound()
{
}

void CSound::SetSound(int All, int Gun, int Ui, int Bgm)
{
	m_iSound[0] = All;
	m_iSound[1] = Gun;
	m_iSound[2] = Ui;
	m_iSound[3] = Bgm;
}
