#pragma once

class CTimeMgr
{
	SINGLETON(CTimeMgr)

public:
	const float& GetDeltaTime() const;

public:
	void Init();
	void UpdateTime();

private:
	LARGE_INTEGER m_OldTime = LARGE_INTEGER();
	LARGE_INTEGER m_CurTime = LARGE_INTEGER();
	LARGE_INTEGER m_CpuTick = LARGE_INTEGER(); // cpu 진동수
	
	BOOL m_bInit = FALSE;

	float m_fDeltaTime = 0.0f; // 수행시간
};