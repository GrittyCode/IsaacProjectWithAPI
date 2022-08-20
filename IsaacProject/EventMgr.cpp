#include "stdafx.h"
#include "EventMgr.h"

CEventMgr* CEventMgr::m_pInstance = nullptr;

void CEventMgr::Init()
{

}

void CEventMgr::Update()
{
	// ���� �����ӿ��� ����ص� Dead Object ���� �����Ѵ�.
	for (UINT i = 0; i < m_vecDead.size(); ++i)
	{
		m_vecDead[i]->Release();
	}
	m_vecDead.clear();


	for (UINT i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();

}

void CEventMgr::Excute(const tEvent& eve)
{
	switch (eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		//lparam : OBJECT Address
		CObject* pObj = (CObject*)eve.lParam;
		CObjectMgr::GetInstance()->AddObject(pObj);
	}
		
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		//lParam OBJECT Address
		//Object�� Dead���·� ����
		//�������� ������Ʈ���� ��Ƶд�.
		CObject* pDeadObj = (CObject*)eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		break;
	}
}
