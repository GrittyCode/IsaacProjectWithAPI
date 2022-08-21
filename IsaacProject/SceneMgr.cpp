#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

void CSceneMgr::Init()
{
	//�÷��̾� �ӽ� ����
	LoadMap(L"test.map");
	m_MapScene.insert({ L"Tool.scene", new CToolScene(L"Tool.scene")});
	
	//ù��° ���� ���� ������ ����
	m_currentScene = (*m_MapScene.find(L"MapTest.scene")).second;

	if (m_currentScene != nullptr)
		m_currentScene->Init();

	m_Player = new CPlayer(
			ObjectInfo(
				L"../Resources/Sprites/character_001_isaac.png",
				Vector2(0, 0),
				Vector2(32, 32),
				Vector2(32, 32),
				Vector2(100, 100),
				Vector2(1, 1), OBJECT_TYPE::PLAYER, OBJECT_STATE::IDLE),
			MoverInfo());
	m_Player->Init();
	CObjectMgr::GetInstance()->SetPlayer(m_Player);

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0,0),
		Vector2(0,0),
		Vector2(30, 630),
		Vector2(60, 0),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(936, 30),
		Vector2(0, 10),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0, 0),
		Vector2(0, 0),
		Vector2(30, 624),
		Vector2(876, 0),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

	CreateObject(new CObstacle(ObjectInfo(L"",
		Vector2(0,0),
		Vector2(0,0),
		Vector2(936, 30),
		Vector2(0, 544),
		Vector2(1, 1), OBJECT_TYPE::OBSTACLE, OBJECT_STATE::IDLE)));

}

void CSceneMgr::Update()
{
	if (m_currentScene != nullptr)
		m_currentScene->Update();
}

void CSceneMgr::FixedUpdate()
{
	if (m_currentScene != nullptr)
		m_currentScene->FixedUpdate();
}

void CSceneMgr::Render(HDC hdc)
{
	if(m_currentScene != nullptr)
		m_currentScene->Render(hdc);
	CEffectMgr::GetInstance()->Update();
}

void CSceneMgr::Release()
{
	if (m_currentScene != nullptr)
		m_currentScene->Release();
}


void CSceneMgr::ChangeScene(wstring scenePath)
{
	auto iter = m_MapScene.find(scenePath);

	if (iter != m_MapScene.end())
	{
		//��ϵǾ��ִ� ������ �ű��.
		m_currentScene = (*iter).second;
		m_currentScene->Init();
	}
}

void CSceneMgr::ChangeMode(GAME_MODE mode)
{
	if (mode == GAME_MODE::GAME)
	{
		ChangeScene(L"start.scene");

		if (g_ToolDig != nullptr)
		{
			DestroyWindow(g_ToolDig);
		}
	}
	else if (mode == GAME_MODE::TOOL)
	{
		ChangeScene(L"Tool.scene");
	}
	else//�������
	{

	}
}

BOOL CSceneMgr::LoadMap(wstring mapPath)
{
	wstring mapDirectory = (L"..//Resources//Map//");

	mapDirectory += mapPath;

	wifstream wifs(mapDirectory, ios::in);

	wchar_t strTemp[255];

	//�� ���� ������
	wifs.getline(strTemp, 255);
	int iSceneCount = _wtoi(strTemp);



	for (int i = 0; i < iSceneCount; ++i)
	{
		wifs.getline(strTemp, 255);
		CScene* Scene = new CScene(strTemp); //�̸� ����
		SetSceneFromSceneSave(Scene);
		m_MapScene.insert({ *Scene->GetName(), Scene});
	}
		
	
	return 0;
}

BOOL CSceneMgr::SetSceneFromSceneSave(CScene* desScene)
{

#ifdef DEBUG
	wcout << OriginDirectory << endl;
#endif // DEBUG

	wstring SceneDirectory = (L"..//Resources//Scene//");

	SceneDirectory += *desScene->GetName();

	wifstream ifs(SceneDirectory, ios::in);

	//������Ʈ ������ ���� ����ü
	ObjectInfo objInfo;

	//���� ����
	wchar_t tempchar;
	//���ڿ� ����
	wstring tempStr;

	if (ifs.is_open())
	{	
		while (true)
		{
			if (ifs.eof()) //������ ���̶�� ����
				break;

			tempStr.clear();

			//������Ʈ �̹��� ���� ����
			for (UINT info = 0; info < (UINT)OBJECT_INFO::OBJECT_INFO_END; ++info)
			{
				//�Ӽ����� �ٲ𶧱���
				while (true)
				{
					ifs.get(tempchar);

					if (tempchar == ',' || tempchar == '\n')
						break;

					tempStr += tempchar;
				}

				switch (info)
				{
				case (UINT)OBJECT_INFO::PATH:
					objInfo.wpath = tempStr;
					break;
				case (UINT)OBJECT_INFO::START_X:
					objInfo.vecStartPos.x = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::START_Y:
					objInfo.vecStartPos.y = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::END_X:
					objInfo.vecEndPos.x = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::END_Y:
					objInfo.vecEndPos.y = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::SIZE_X:
					objInfo.vecSize.x = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::SIZE_Y:
					objInfo.vecSize.y = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::POSITION_X:
					objInfo.vecWorldPos.x = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::POSITION_Y:
					objInfo.vecWorldPos.y = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::SCALE_X:
					objInfo.vecScale.x = (float)_wtof(tempStr.c_str());
					break;
				case (UINT)OBJECT_INFO::SCALE_Y:
					objInfo.vecScale.y = (float)_wtof(tempStr.c_str());
				case (UINT)OBJECT_INFO::TYPE:
					objInfo.type = (OBJECT_TYPE)_wtoi(tempStr.c_str());
				case (UINT)OBJECT_INFO::STATE:
					objInfo.state = (OBJECT_STATE)_wtoi(tempStr.c_str());
					break;
				}

				tempStr.clear();
			}

			//���Ͽ� ��ϵ� ������Ʈ���� �� ���鿡 ��ġ�Ѵ�.

			desScene->AddObjectToScene(objInfo);
		}
	}
	else //���Ϸε� ����
	{
		MessageBox(g_hWnd, L"���!", L"���� �ε� ����", FALSE);
		return (INT_PTR)FALSE;
	}

	return (INT_PTR)TRUE;
}

wstring CSceneMgr::GetCurSceneName()
{
	if (m_currentScene != nullptr)
	{
		return *m_currentScene->GetName();
	}
	return L"";
}



void CSceneMgr::CreateStageFromTool()
{
	for (int i = 0; i < COLMN; ++i)
	{
		for (int j = 0; j < ROW; ++j)
		{
			CObjectMgr::GetInstance()->AddTile(new CTile(TileInfo(), TilePos(j, i)));
		}
	}
}





/*
	//��׶��� �ӽ� ����
	CreateObject(new CBackground(ObjectInfo(L"../Resources/BackGround/test.bmp", OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));
	//�÷��̾� ����ϱ� ���� �ļ�
	CreateObject(new CPlayer(
		ObjectInfo(
			L"../Resources/Sprites/character_001_isaac.png",
			Vector2(0, 0),
			Vector2(32, 32),
			Vector2(32, 32),
			Vector2(100, 100),
			Vector2(1, 1), OBJECT_TYPE::PLAYER, OBJECT_STATE::IDLE),
			MoverInfo()));

	CreateObject(new CFly(ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
		Vector2(0, 32),
		Vector2(32, 32),
		Vector2(32, 32),
		Vector2(200, 200),
		Vector2(1, 1), OBJECT_TYPE::ENEMY, OBJECT_STATE::IDLE),
		EnemyInfo(4,1,0,50.0f,0)));


	CreateObject(new CDoor(ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
		Vector2(0, 32),
		Vector2(32, 32),
		Vector2(32, 32),
		Vector2(200, 200),
		Vector2(1, 1), OBJECT_TYPE::DOOR, OBJECT_STATE::IDLE),
		DoorInfo(L"test1.scene", Vector2(500,500))));
	*/