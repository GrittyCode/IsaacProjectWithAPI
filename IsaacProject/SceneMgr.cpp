#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

void CSceneMgr::Init()
{
	//백그라운드 임시 생성	
	CreateObject(new CBackground(ObjectInfo(L"../Resources/BackGround/test.bmp", OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));
	//플레이어 등록하기 위한 꼼수
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


	m_currentScene = new CScene(L"test1.scene",ROW,COLMN);

	if (m_currentScene != nullptr)
		m_currentScene->Init();
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
}

void CSceneMgr::Release()
{
	if (m_currentScene != nullptr)
		m_currentScene->Release();

	delete m_currentScene;
	m_currentScene = nullptr;
}

void CSceneMgr::ChangeScene(INT index)
{
	Release();
}

void CSceneMgr::ChangeMode(GAME_MODE mode)
{
	if (mode == GAME_MODE::GAME)
	{
		Release();
		m_currentScene = new CScene(L"test.Scene", ROW, COLMN);
		m_currentScene->Init();

		if (g_ToolDig != nullptr)
		{
			DestroyWindow(g_ToolDig);
		}
	}
	else if (mode == GAME_MODE::TOOL)
	{
		Release();
		CObjectMgr::GetInstance()->Init();
		m_currentScene = new CToolScene();
		m_currentScene->Init();
	}
	else//디버깅모드
	{

	}
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

BOOL CSceneMgr::LoadMap(wstring mapPath)
{
	INT iGoldenRoomCnt = 1;

	wstring mapDirectory = (L"..//Resources//Map//");

	mapDirectory += mapPath;

	wifstream ifs(mapDirectory, ios::in);
	wstring sceneName;

	int iRoomCount = 0;
	int Startrow = rand() % 5;
	int Startcolmn = rand() % 5;

	m_createdMap.push_back(POINT{Startcolmn, Startrow});
	//상하좌우 생성
	int dir[4][2] = { {0,1}, {0,-1}, {-1,0},{1,0} };

	auto iter = m_createdMap.begin();

	//씬 10개 생성
	while (iRoomCount < 10)
	{
		int select = rand() % m_createdMap.size();
		//선택된 방은 당연히 1로 생성되었다는 것을 표시
		m_iMiniMap[m_createdMap[select].y][m_createdMap[select].x] = 1;
		m_createdMap.erase(iter + select);
		iRoomCount++;
		//현재 선택된 방에서 4방향으로 생성
		//최대 4개 생성이 가능
		int CreateNum = rand() % 4 + 1;
		for (int i = 0; i < CreateNum; ++i)
		{
			int dirRandom = rand() % 4;
		}

	}
	return 0;
}

BOOL CSceneMgr::LoadScene(wstring scenePath)
{
	Release();

#ifdef DEBUG
	wcout << OriginDirectory << endl;
#endif // DEBUG

	wstring mapDirectory = (L"..//Resources//Scene//");

	mapDirectory += scenePath;

	wifstream ifs(mapDirectory, ios::in);

	//오브젝트 정보를 받을 구조체
	ObjectInfo objInfo;

	//문자 버퍼
	wchar_t tempchar;
	//문자열 버퍼
	wstring tempStr;

	if (ifs.is_open())
	{	
		while (true)
		{
			if (ifs.eof()) //파일의 끝이라면 종료
				break;

			tempStr.clear();

			//오브젝트 이미지 정보 저장
			for (UINT info = 0; info < (UINT)OBJECT_INFO::OBJECT_INFO_END; ++info)
			{
				//속성값이 바뀔때까지
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

			//파일에 등록된 오브젝트들을 오브젝트 매니저에 세팅한다.
			CObjectMgr::GetInstance()->SetObjectFromFile(objInfo);
		}
	}
	else //파일로드 실패
	{
		MessageBox(g_hWnd, L"경고!", L"파일 로드 실패", FALSE);
		return (INT_PTR)FALSE;
	}

	return (INT_PTR)TRUE;
}

wstring CSceneMgr::GetCurSceneName()
{
	if (m_currentScene != nullptr)
	{
		return m_currentScene->GetName();
	}

	return L"";
}
