#include "stdafx.h"
#include "EventMgr.h"

CEventMgr* CEventMgr::m_pInstance = nullptr;

void CEventMgr::Init()
{

}

void CEventMgr::Update()
{
	// 이전 프레임에서 등록해둔 Dead Object 들을 삭제한다.
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
		//Object를 Dead상태로 변경
		//삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		break;
	}
}
