#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
	:m_Name(L"")
{
}

CScene::CScene(wstring name)
{
	m_Name = name;
	
	for (UINT i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		m_MapObjectList.insert({ (OBJECT_TYPE)i, list<CObject*>() });
	}
}

CScene::~CScene()
{
}

void CScene::Init()
{
	//오브젝트 매니저와 연결한다.
	CObjectMgr::GetInstance()->Init();
	CObjectMgr::GetInstance()->ConnectScene(&m_MapObjectList);


	//눈물 벽 충돌
	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(10, 640),
		Vector2(60, 0),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(956, 10),
		Vector2(0, 32),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(10, 640),
		Vector2(876, 0),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(936, 10),
		Vector2(0, 525),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	//플레이어와 벽충돌
	CreateObject(new CMapCollider(ObjectInfo(L"",
		Vector2(0,0),
		Vector2(0, 0),
		Vector2(936, 5),
		Vector2(0, 85),
		Vector2(1, 1), OBJECT_TYPE::MAP_COLLIDER, OBJECT_STATE::IDLE)));

	CreateObject(new CMapCollider(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(5, 640),
		Vector2(95, 0),
		Vector2(1, 1), OBJECT_TYPE::MAP_COLLIDER, OBJECT_STATE::IDLE)));

	CreateObject(new CMapCollider(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(5, 640),
		Vector2(840, 80),
		Vector2(1, 1), OBJECT_TYPE::MAP_COLLIDER, OBJECT_STATE::IDLE)));
}

void CScene::Update()
{
	CObjectMgr::GetInstance()->Update();
}

void CScene::FixedUpdate()
{
	//플레이어 충돌처리
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOSS);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOMB);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DOOR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ITEM);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY_TEAR);
	
	//몬스터 충돌 처리
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::PLAYER_TEAR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::BOMB);
	
	//눈물 충돌 처리
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::ENEMY);

	//벽 충돌 처리
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::OBSTACLE, OBJECT_TYPE::PLAYER);

	//문 충돌 처리
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::DOOR, OBJECT_TYPE::PLAYER);

	//map콜라이더
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::MAP_COLLIDER, OBJECT_TYPE::PLAYER);
	CObjectMgr::GetInstance()->FixedUpdate();
}


void CScene::Render(HDC hdc)
{
	CObjectMgr::GetInstance()->Render(hdc);
}


void CScene::Release()
{
	auto iter = m_MapObjectList.begin();

	for (; iter != m_MapObjectList.end(); ++iter)
	{
		auto listiter = (*iter).second.begin();
		for (;listiter != (*iter).second.end(); ++listiter)
		{
			(*listiter)->Release();
			delete *listiter;
			*listiter = nullptr;
		}
	}

	CObjectMgr::GetInstance()->Release();
	
}

void CScene::AddObjectToScene(ObjectInfo objInfo)
{
	m_iter = m_MapObjectList.find(objInfo.type);

	if (m_iter != m_MapObjectList.end())
	{	
		switch (objInfo.type)
		{
			case OBJECT_TYPE::BACKGROUND:
			{
				CBackground* obj = new CBackground(objInfo);
				obj->Init();
				(*m_iter).second.push_back(obj);
			}
			break;
			case OBJECT_TYPE::OBSTACLE:
			{
				CObstacle* obj = new CObstacle(objInfo);
				obj->Init();
				(*m_iter).second.push_back(obj);
			}
			break;
			case OBJECT_TYPE::ITEM:
			{

			}
			break;
		}
	}
}

