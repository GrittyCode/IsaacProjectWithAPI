#include "stdafx.h"
#include "TimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

const float& CTimeMgr::GetDeltaTime() const
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_fDeltaTime;
}

void CTimeMgr::Init()
{
	if (!m_bInit)
	{
		m_bInit = TRUE;
		m_fDeltaTime = 0.f;
	}

	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
	// �ϵ����(���κ���)�� �����ϴ� ���ػ� Ÿ�̸� ��(���� CPU Ŭ����)�� ������ �Լ�. 
	// 1 / 10000��
	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_CurTime);

	// ���� CPU�� �������� ������ �Լ�. 1�ʵ��� �󸶳� �����ϴ���.
	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimeMgr::UpdateTime()
{
	QueryPerformanceCounter(&m_CurTime);

	// ���� �����̰� �ɷ��� �� �ʱ� ���·� ����.
	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
		Init();

	m_fDeltaTime = float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime = m_CurTime;
}
