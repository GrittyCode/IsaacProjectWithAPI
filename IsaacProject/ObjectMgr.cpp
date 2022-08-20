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

 	//플레이어 등록하기 위한 꼼수
	AddObject(new CPlayer(
		ObjectInfo(
			L"../Resources/Sprites/character_001_isaac.png",
			Vector2(0, 0),
			Vector2(32, 32),
			Vector2(32, 32),
			Vector2(100, 100),
			Vector2(1, 1), OBJECT_TYPE::PLAYER, OBJECT_STATE::IDLE),
			MoverInfo()));

	AddObject(new CFly(ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(64, 64),
		Vector2(200, 200),
		Vector2(1, 1),
		OBJECT_TYPE::ENEMY,
		OBJECT_STATE::IDLE), EnemyInfo(4, 1, 0, 70.0f, 0)));

	//백그라운드 임시 생성	
	AddObject(new CBackground(ObjectInfo(L"../Resources/BackGround/test.bmp", OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));
	CreateObject(new CBackground(ObjectInfo(L"../Resources/BackGround/test.bmp", OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));

	m_player = dynamic_cast<CPlayer*>(m_MapObjectList.find(OBJECT_TYPE::PLAYER)->second.back());
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
	if (CGameMgr::GetInstance()->GetGameMode() == GAME_MODE::TOOL)
	{
		for (auto tile : m_vecTile)
		{
			tile->Render(hdc);
		}
	}

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
					delete* list_iter;
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
		case OBJECT_TYPE::BOOM_OBSTACLE:
			break;
		case OBJECT_TYPE::TEAR_OBSTACLE:
			break;
		case OBJECT_TYPE::DOOR:
			break;
		case OBJECT_TYPE::ITEM:
			break;
		case OBJECT_TYPE::PLAYER:
			CreateObject(new CPlayer(info, MoverInfo()));
			break;
		case OBJECT_TYPE::TEAR:
			break;
		case OBJECT_TYPE::ENEMY:
			break;
		case OBJECT_TYPE::BOSS:
			break;
		}

		return TRUE;
	}
	return FALSE;
}