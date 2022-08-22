#include "stdafx.h"
#include "EffectMgr.h"

CEffectMgr* CEffectMgr::m_pInstance = nullptr;

void CEffectMgr::Init()
{
}

void CEffectMgr::Update()
{
	m_iter = m_Effectlist.begin();

	for (m_iter; m_iter != m_Effectlist.end(); ++m_iter)
	{
		(*m_iter)->Update();
	}
}

void CEffectMgr::AddEffecter(CAnimation* ani)
{
	if (ani == nullptr)
	{
		return;
	}

	m_Effectlist.push_back(ani);
}

void CEffectMgr::DeletEffect(CAnimation* ani)
{
	if (ani == nullptr)
	{
		return;
	}
	m_iter = m_Effectlist.begin();
	
	for (; (*m_iter) != ani; ++m_iter)

	if (m_iter == m_Effectlist.end()) return;
	
	delete ani;
	ani = nullptr;

	m_iter = m_Effectlist.erase(m_iter);
}
