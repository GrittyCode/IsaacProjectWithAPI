#include "stdafx.h"
#include "ObjectMgr.h"

CObjectMgr* CObjectMgr::m_pInstance = nullptr;

void CObjectMgr::Init()
{
	if (m_player == nullptr)
	{
		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
			Vector2(0, 32),
			Vector2(32, 32),
			Vector2(32, 32),
			Vector2(200, 200),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE),
			DoorInfo(L"test5.scene", Vector2(800, 500), DIRECTION::LEFT)));
	}
	else
	{

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
		auto objiter = m_MapObjectList->find((OBJECT_TYPE)i);

		if (objiter != m_MapObjectList->end())
		{
			for (CObject* obj : (*objiter).second)
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
		m_Objiter = m_MapObjectList->find((OBJECT_TYPE)i);

		if (m_Objiter != m_MapObjectList->end())
		{
			for (CObject* obj : (*m_Objiter).second)
			{
				obj->FixedUpdate();
			}
		}
	}
}

void CObjectMgr::LateUpdate()
{
}


void CObjectMgr::Render(HDC hdc)
{

	for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		CScene* scene = CSceneMgr::GetInstance()->GetCurScene();
		m_Objiter = m_MapObjectList->find((OBJECT_TYPE)i);

		if (m_Objiter != m_MapObjectList->end())
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

	if (!m_MapObjectList->empty())
	{
		for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
		{
			m_Objiter = m_MapObjectList->find((OBJECT_TYPE)i);

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

		m_MapObjectList->clear();
	}
}



void CObjectMgr::ErasePlayer()
{

	if (m_MapObjectList != nullptr)
	{
		m_Objiter = m_MapObjectList->find(OBJECT_TYPE::PLAYER);

		if (m_Objiter != m_MapObjectList->end())
		{
			(*m_Objiter).second.pop_front(); //PLAYER 빼주기
		}
	}
}

void CObjectMgr::SetPlayer(CPlayer* player)
{
	if (player != nullptr)
	{
		m_player = player;

		m_Objiter = m_MapObjectList->find(OBJECT_TYPE::PLAYER);

		if (m_Objiter != m_MapObjectList->end())
		{
			(*m_Objiter).second.push_back(player); //PLAYER 넣어주기
		}
	}
}

void CObjectMgr::ConnectScene(map<OBJECT_TYPE, list<CObject*>>* temp)
{
	ErasePlayer();
	m_MapObjectList = temp;
	SetPlayer(m_player);
	CCollisionMgr::GetInstance()->ChanageScene(m_MapObjectList);
}


BOOL CObjectMgr::AddObject(CObject* object)
{
	m_Objiter = m_MapObjectList->find(object->GetObjType());

	if (m_Objiter != m_MapObjectList->end() && object != nullptr)
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
	m_Objiter = m_MapObjectList->find(info.type);


	if (m_Objiter != m_MapObjectList->end())
	{
		switch (info.type)
		{
		case OBJECT_TYPE::BACKGROUND:
			CreateObject(new CBackground(info));
			break;
		case OBJECT_TYPE::OBSTACLE:
			CreateObject(new CObstacle(info));
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


BOOL CObjectMgr::AddTile(CTile* tile)
{
	tile->Init();
	m_vecTile.push_back(tile);
	return TRUE;
}