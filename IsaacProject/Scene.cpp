#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
	:m_Name(L""),
	m_row(18),
	m_colmn(12)
{
	
}

CScene::CScene(wstring name, UINT row, UINT colmn)
{
	m_Name = name;
	m_row = row;
	m_colmn = colmn;

	CSceneMgr::GetInstance()->LoadScene(m_Name);
}

CScene::~CScene()
{
}

void CScene::Init()
{

}

void CScene::Update()
{
	CObjectMgr::GetInstance()->Update();
}

void CScene::FixedUpdate()
{
	//敲饭捞绢 面倒贸府
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOSS);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOMB);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DOOR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ITEM);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY_TEAR);
	
	//阁胶磐 面倒 贸府
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::PLAYER_TEAR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::BOMB);
	
	//传拱 面倒 贸府
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY_TEAR, OBJECT_TYPE::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER_TEAR, OBJECT_TYPE::ENEMY);

	//寒 面倒 贸府
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::OBSTACLE, OBJECT_TYPE::PLAYER);

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

