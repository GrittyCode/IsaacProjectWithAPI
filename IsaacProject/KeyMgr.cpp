#include "stdafx.h"
#include "KeyMgr.h"

CKeyMgr* CKeyMgr::m_pInstance = nullptr;

int g_arrVK[(int)KEY::LAST] =//����Ű���� ���� 
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
		m_vecKey.push_back(tKeyInfo{ KEY_STATE::NONE, false });//��Ʈ���� �־���
	}
}

void CKeyMgr::Update()
{
	//������ ��Ŀ�� �˾Ƴ���(�ȵ��찡 ȭ��� ǥ��Ǿ� ������)

	HWND hWnd = GetFocus();

	//�ȵ��찡 ��Ŀ���� ���� 
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (UINT)KEY::LAST; ++i)
		{
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{
				if (m_vecKey[i].bPrevPush)
				{
					//�������� ���� �־��� ��
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					//������ �������� �ʾ��� ���
					m_vecKey[i].eState = KEY_STATE::TAP;
				}

				m_vecKey[i].bPrevPush = true;
			}
			//����� Ű�� �ȴ����� �ִ�.
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					//������ ������ �־��� ���
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					//�������� ������ ���� �ʾ��� ���
					m_vecKey[i].eState = KEY_STATE::NONE;
				}

				m_vecKey[i].bPrevPush = false;
			}

		}
	}
	//������ ��Ű����������
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