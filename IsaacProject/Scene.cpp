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
	//������Ʈ �Ŵ����� �����Ѵ�.
	CObjectMgr::GetInstance()->Init();
	CObjectMgr::GetInstance()->ConnectScene(&m_MapObjectList);


	if (m_Name == L"Tool.scene")
		return;

	//���� �� �浹
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
		Vector2(0, 530),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	//�÷��̾�� ���浹
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
		Vector2(102, 0),
		Vector2(1, 1), OBJECT_TYPE::MAP_COLLIDER, OBJECT_STATE::IDLE)));

	CreateObject(new CMapCollider(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(5, 640),
		Vector2(833, 80),
		Vector2(1, 1), OBJECT_TYPE::MAP_COLLIDER, OBJECT_STATE::IDLE)));

	if (iMinMap == 0)
	{
		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Object/Door.png",
			Vector2(64, 0),
			Vector2(0, 0),
			Vector2(64, 64),
			Vector2(468, 80),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE),DoorInfo(L"test2.scene", Vector2(800, 500), DIRECTION::UP)));

		CreateObject(new CBackground(ObjectInfo(L"../Resources/BackGround/controls.png",
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(325, 84),
			Vector2(468, 322),
			Vector2(1, 1), OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));
	}

	if (iMinMap == 1)
	{
		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Object/Door.png",
			Vector2(0, 128),
			Vector2(0, 0),
			Vector2(64, 64),
			Vector2((float)80, WINDOW_Y * 0.5f),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE), DoorInfo(L"test2.scene", Vector2(800, 500), DIRECTION::LEFT)));

		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Object/Door.png",
			Vector2(0, 256),
			Vector2(0, 0),
			Vector2(64, 64),
			Vector2((float)872, WINDOW_Y * 0.5f),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE), DoorInfo(L"test2.scene", Vector2(800, 500), DIRECTION::RIGHT)));


		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Object/Door.png",
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(64, 64),
			Vector2(WINDOW_X * 0.5f, (float)80),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE), DoorInfo(L"test2.scene", Vector2(800, 500), DIRECTION::UP)));

		CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Object/Door.png",
			Vector2(0, 0),
			Vector2(0, 0),
			Vector2(64, 64),
			Vector2(WINDOW_X * 0.5f, (float)562),
			Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE), DoorInfo(L"test2.scene", Vector2(800, 500), DIRECTION::DOWN)));

		//�ĸ�����

		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(300, 300));
		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(150, 150));
		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(600, 200));
		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(600, 60));
		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(300, 300));
		CEnemyFactory::CreateEnemyForType(ENEMY_TYPE::FLY, Vector2(500, 100));


		m_state = SCENE_STATE::CLOSE;
	}
}

void CScene::Update()
{
	CObjectMgr::GetInstance()->Update();
}

void CScene::FixedUpdate()
{
	//�÷��̾� �浹ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOSS);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOMB);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DOOR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ITEM);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY_TEAR);
	
	//���� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::PLAYER_TEAR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::BOMB);
	
	//���� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::ENEMY);

	//�� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::OBSTACLE, OBJECT_TYPE::PLAYER);

	//�� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::DOOR, OBJECT_TYPE::PLAYER);

	//map �ݶ��̴�
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::MAP_COLLIDER, OBJECT_TYPE::PLAYER);

	//Item �ݶ��̴�
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ITEM, OBJECT_TYPE::PLAYER);


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

BOOL CScene::AllEnemyDie()
{
	auto iter = m_MapObjectList.find(OBJECT_TYPE::ENEMY);

	if ((*iter).second.empty())
	{
		if (m_state == SCENE_STATE::CLOSE)
		{
			CObjectMgr::GetInstance()->CreateRandomItem();
		}

		return true;
	}

	return false;
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

