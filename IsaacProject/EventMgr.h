#pragma once


struct tEvent
{
	EVENT_TYPE	eEven;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CEventMgr
{
	SINGLETON(CEventMgr)
public:
	void Init();
	void Update();
public:
	void AddEvent(const tEvent& eve) { m_vecEvent.push_back(eve); }
private:
	void Excute(const tEvent& _eve);
	vector<tEvent> m_vecEvent;
	vector<CAnimation*> m_vecDeadAnimation;
	vector<CObject*> m_vecDead;

};

