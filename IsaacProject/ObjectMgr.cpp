#include "stdafx.h"
#include "ObjectMgr.h"

CObjectMgr* CObjectMgr::m_pInstance = nullptr;

void CObjectMgr::Init()
{
	//MAP 리스트 메모리 등록
	for (size_t i = 0; (OBJECT_TYPE)i < OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		list<CObject*> temp;
		m_MapObjectList.insert({ (OBJECT_TYPE)i, temp });
	}
}

void CObjectMgr::Update()
{
	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::TOOL)
	{
		for (auto tile : m_vecTile)
		{
			tile->Update();
		}
	}

	for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_Objiter = m_MapObjectList.find((OBJECT_TYPE)i);

		if (m_Objiter != m_MapObjectList.end())
		{
			for (CObject* obj : (*m_Objiter).second)
			{
				if (!obj->IsDead())
				{
				obj->Update();
				}
			}
		}
	}
}

void CObjectMgr::FixedUpdate()
{
	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::TOOL)
	{
		for (auto tile : m_vecTile)
		{
			tile->FixedUpdate();
		}
	}

	for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_Objiter = m_MapObjectList.find((OBJECT_TYPE)i);

		if (m_Objiter != m_MapObjectList.end())
		{
			for (CObject* obj : (*m_Objiter).second)
			{
				obj->FixedUpdate();
			}
		}
	}
}

void CObjectMgr::Render(HDC hdc)
{
	for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_Objiter = m_MapObjectList.find((OBJECT_TYPE)i);

		if (m_Objiter != m_MapObjectList.end())
		{
			auto iter = m_Objiter->second.begin();


			for (; iter != (*m_Objiter).second.end();)
			{
				if (!(*iter)->IsDead())
				{
					(*iter)->Render(hdc);
					++iter;
				}
				else
				{
					iter = m_Objiter->second.erase(iter);
				}
			}
		}
	}


	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::TOOL)
	{
		for (auto tile : m_vecTile)
		{
			tile->Render(hdc);
		}
	}
}


void CObjectMgr::Release()
{
	for (auto tile : m_vecTile)
	{
		tile->Release();
		delete tile;
	}

	m_vecTile.clear();

	if (!m_MapObjectList.empty())
	{
		for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
		{
			m_Objiter = m_MapObjectList.find((OBJECT_TYPE)i);

			auto list_iter = (*m_Objiter).second.begin();

			for (UINT i = 0; i < m_Objiter->second.size(); ++i)
			{
				if ((*list_iter) != nullptr)
				{
					(*list_iter)->Release();
					delete *list_iter;
					*list_iter = nullptr;
				}
		}

			m_Objiter->second.clear();
		}

		m_MapObjectList.clear();
	}
}

BOOL CObjectMgr::AddTile(CTile* tile)
{
	tile->Init();
	m_vecTile.push_back(tile);
	return TRUE;
}

BOOL CObjectMgr::AddObject(CObject* object)
{
	m_Objiter = m_MapObjectList.find(object->GetObjType());

	if (m_Objiter != m_MapObjectList.end() && object != nullptr)
	{	
		if (object->GetObjType() == OBJECT_TYPE::PLAYER)
		{
			m_player = dynamic_cast<CPlayer*>(object);
		}
		object->Init();
		(*m_Objiter).second.push_back(object);
		return TRUE;
	}

	if (object != nullptr)
		delete object;
	return FALSE;
}



BOOL CObjectMgr::SetObjectFromFile(ObjectInfo info)
{
	m_Objiter = m_MapObjectList.find(info.type);


	if (m_Objiter != m_MapObjectList.end())
	{
		switch (info.type)
		{
		case OBJECT_TYPE::BACKGROUND:
			CreateObject(new CBackground(info));
			break;
		case OBJECT_TYPE::OBSTACLE:
			CreateObject(new CObstacle(info));
			break;
		case OBJECT_TYPE::DOOR:
			break;
		case OBJECT_TYPE::ITEM:
			break;
		case OBJECT_TYPE::PLAYER:
			CreateObject(new CPlayer(info, MoverInfo()));
			break;
		case OBJECT_TYPE::PLAYER_TEAR:
			break;
		case OBJECT_TYPE::ENEMY:
			CreateObject(new CObstacle(info));
			break;
		case OBJECT_TYPE::BOSS:
			break;
		}

		return TRUE;
	}
	return FALSE;
}