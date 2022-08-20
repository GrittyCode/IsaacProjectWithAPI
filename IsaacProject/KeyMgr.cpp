#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

int g_arrVK[(int)KEY::LAST] =//가상키값을 넣음 
{
	VK_LEFT,//LEFT,
	VK_RIGHT,//RIGHT,
	VK_UP,//UP,
	VK_DOWN,//DOWN,
	'W',
	'A',
	'S',
	'D',
	VK_SPACE,//SPCAE,
	VK_RETURN,//ENTER,
	VK_ESCAPE,//ESC,
	VK_LBUTTON,
	VK_F1,
	VK_F2,
	VK_F3,
};


void CKeyMgr::Init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });//라스트까지 넣어줌
	}
}

void CKeyMgr::Update()
{
	//윈도우 포커싱 알아내기(읜도우가 화면상에 표출되어 있을때)

	HWND hWnd = GetFocus();

	//읜도우가 포커싱인 상태 
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (UINT)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					//이전에도 눌려 있었을 시
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//이전에 눌려있지 않았을 경우
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			//현재는 키가 안눌려져 있다.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					//이전에 눌러져 있었을 경우
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//이전에도 눌려져 있지 않았을 경우
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}

		}
	}
	//윈도우 포키싱해제상태
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;

			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;
			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;
			}
		}
	}
}

KEY_STATE CKeyMgr::GetKeyState(int key)
{
	return m_vecKey[key].eState;
}