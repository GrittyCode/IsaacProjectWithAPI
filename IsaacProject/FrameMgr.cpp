#include "stdafx.h"
#include "FrameMgr.h"

CFrameMgr::CFrameMgr()
{
	ZeroMemory(&m_OldTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CurTime, sizeof(LARGE_INTEGER));
	ZeroMemory(&m_CpuTick, sizeof(LARGE_INTEGER));
}


CFrameMgr::~CFrameMgr()
{
}

HRESULT CFrameMgr::InitFrameMgr(float fCurFPS)
{
	m_fSPF = 1.f / fCurFPS;

	QueryPerformanceCounter(&m_OldTime);
	QueryPerformanceCounter(&m_CurTime);
	QueryPerformanceFrequency(&m_CpuTick);

	return S_OK;
}

bool CFrameMgr::LimitFrame()
{
	QueryPerformanceCounter(&m_CurTime);

	// 일정 딜레이가 걸렸을 때 초기 상태로 돌림.
	if (m_CurTime.QuadPart - m_OldTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceCounter(&m_OldTime);
		QueryPerformanceCounter(&m_CurTime);
		QueryPerformanceFrequency(&m_CpuTick);
	}

	m_fTimeCount += float(m_CurTime.QuadPart - m_OldTime.QuadPart) / m_CpuTick.QuadPart;
	m_OldTime = m_CurTime;

	if (m_fTimeCount >= m_fSPF)
	{
		m_fTimeCount = 0.f;
		return true;
	}

	return false;
}

void CFrameMgr::RenderFrame()
{
	++m_dwFPS;

	m_fTimeCount2 += CTimeMgr::GetInstance()->GetDeltaTime();

	if (1.f <= m_fTimeCount2)
	{
		//cout << m_dwFPS << endl;
		m_dwFPS = 0;
		m_fTimeCount2 = 0.f;
	}
}
