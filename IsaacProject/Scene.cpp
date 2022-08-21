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

