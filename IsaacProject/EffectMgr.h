#pragma once

class CEffectMgr
{
	SINGLETON(CEffectMgr);

public:
	void Init();
	void Update();
	void AddEffecter(CAnimation* ani);
	void DeletEffect(CAnimation* ani);

private:
	list<CAnimation*> m_Effectlist;
	list<CAnimation*>::iterator m_iter;
};

