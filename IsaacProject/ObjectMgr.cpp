#include "stdafx.h"
#include "ObjectMgr.h"

CObjectMgr* CObjectMgr::m_pInstance = nullptr;

void CObjectMgr::Init()
{

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

	CUiMgr::GetInstance()->Render(hdc);


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

void CObjectMgr::CreateRandomItem()
{
	int random = rand() % 100;

	//10퍼센트 확률로 보상이 나오지 않는다.
	if (random < 10)
	{
		return;
	}
	//키 생성 코드
	else if (random < 40)
	{
		CreateObject(new CItem(
				ObjectInfo(L"../Resources/Sprites/item/pickup_03_key.png",
				Vector2(0, 0),Vector2(16, 32),
				Vector2(16, 32),Vector2(WINDOW_X * 0.7f, WINDOW_Y * 0.8f),OBJECT_TYPE::ITEM),
				ITEM_TYPE::KEY));
	}
	//폭탄 생성 코드
	else if (random < 70)
	{
		CreateObject(new CItem(
			ObjectInfo(L"../Resources/Sprites/item/pickup_02_bomb.png",
				Vector2(0, 0), Vector2(32, 32),
				Vector2(32, 32), Vector2(WINDOW_X * 0.7f, WINDOW_Y * 0.8f), OBJECT_TYPE::ITEM),
			ITEM_TYPE::BOMB));
	}
	//코인 생성 코드
	else
	{

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
	//과거 씬에 있던 기존 플레이어를 지우고 현재 씬에 연결을 하고 CollisionMgr에 그 씬의 충돌 정보를 모두 등록해놓는다. 
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