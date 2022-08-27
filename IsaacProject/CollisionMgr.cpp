#include "stdafx.h"
#include "CollisionMgr.h"

CCollisionMgr* CCollisionMgr::m_pInstance = nullptr;


void CCollisionMgr::Init()
{

	//맵 리스트 메모리 등록
	for (UINT i = 0; i < (UINT)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_mapBoxlist.insert({ (OBJECT_TYPE)i, list<CBoxCollider2D*>() });
	}

}

void CCollisionMgr::CheckCollision(OBJECT_TYPE sour, OBJECT_TYPE ades)
{
	m_iter = m_mapBoxlist.find(sour);
	
	if (sour != ades)
	{
	
		for (auto target : (*m_iter).second)
		{
			if (!target->GetOwnerObj()->IsDead())
			{
				m_iter = m_mapBoxlist.find(ades);
				for (auto des : (*m_iter).second)
				{
					if (!des->GetOwnerObj()->IsDead())
					{
						if (IsCollision(target, des))
						{
							target->SetCollisonFlag((UINT)pow(2, (UINT)ades - 1));
							target->PushTargetCollision(des);
						}
					}
				}
			}
		}

	}
	else
	{
		for (auto target : (*m_iter).second)
		{
			m_iter = m_mapBoxlist.find(ades);
			if (!target->GetOwnerObj()->IsDead())
			{
				for (auto des : (*m_iter).second)
				{
					if (!des->GetOwnerObj()->IsDead())
					{
						//자기 자신일때는 바로 넘어간다.
						if (target == des)
							continue;

						if (IsCollision(target, des))
							target->SetCollisonFlag((UINT)pow(2, (UINT)ades - 1));

						target->CollisionCheck();
					}
				}
			}
		}
	}
}



void CCollisionMgr::AddCollider(OBJECT_TYPE type, CBoxCollider2D* box)
{
	m_iter = m_mapBoxlist.find(type);
	if (m_iter != m_mapBoxlist.end())
	{
		(*m_iter).second.push_back(box);
	}
}



void CCollisionMgr::DeleteCollider(CBoxCollider2D* target)
{
	m_iter = m_mapBoxlist.find(target->GetOwnerType());

	if (target != nullptr)
	{
		auto listIter = m_iter->second.begin();
		for (; listIter != (*m_iter).second.end();)
		{
			if ((*listIter) == target)
			{
				listIter = (*m_iter).second.erase(listIter);
			}
			else
			{
				++listIter;
			}
		}
	}
}


void CCollisionMgr::ChanageScene(map<OBJECT_TYPE, list<CObject*>>* mapObjList)
{
	m_mapBoxlist.clear();
	Init();

	auto iter = mapObjList->begin();

	for (; iter != mapObjList->end(); ++iter)
	{
		auto listiter = (*iter).second.begin();
		for (; listiter != (*iter).second.end(); ++listiter)
		{
			if ((*listiter)->GetCollide() != nullptr)
			{
				auto boxiter = m_mapBoxlist.find((*listiter)->GetObjType());
				(*boxiter).second.push_back((*listiter)->GetCollide());
			}
		}
	}
}


//사각형 AABB충돌
BOOL CCollisionMgr::IsCollision(CBoxCollider2D* source, CBoxCollider2D* dest)
{

	if (source->GetAABB().left  < dest->GetAABB().right &&
		source->GetAABB().top < dest->GetAABB().bottom)
	{
		if(source->GetAABB().right > dest->GetAABB().left &&
			source->GetAABB().bottom > dest->GetAABB().top)
					return TRUE;
	}

	return FALSE;
}


