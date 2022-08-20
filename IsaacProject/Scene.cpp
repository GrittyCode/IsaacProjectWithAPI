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
	Release();
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
	//�÷��̾� �浹ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ENEMY, COLLISION_FLAG::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOSS, COLLISION_FLAG::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::BOMB, COLLISION_FLAG::BOMB);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::DOOR, COLLISION_FLAG::DOOR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::ITEM, COLLISION_FLAG::ITEM);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::PLAYER, OBJECT_TYPE::TEAR, COLLISION_FLAG::TEAR);
	
	//���� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::OBSTACLE, COLLISION_FLAG::OBSTACLE);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::ENEMY, COLLISION_FLAG::ENEMY);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::TEAR, COLLISION_FLAG::TEAR);
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::ENEMY, OBJECT_TYPE::BOMB, COLLISION_FLAG::BOMB);
	

	//���� �浹 ó��



	//�� �浹 ó��
	CCollisionMgr::GetInstance()->CheckCollision(OBJECT_TYPE::OBSTACLE, OBJECT_TYPE::PLAYER, COLLISION_FLAG::PLAYER);

	CObjectMgr::GetInstance()->FixedUpdate();
}

void CScene::Render(HDC hdc)
{
	CObjectMgr::GetInstance()->Render(hdc);
}

void CScene::Release()
{
	CObjectMgr::GetInstance()->Release();
}

