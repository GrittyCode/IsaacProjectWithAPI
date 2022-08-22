#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

void CSceneMgr::Init()
{
	//씬 전환 이미지 생성
	m_pFadeImg = new Image(L"../Resources/Sprites/fadeinout.png");
	//플레이어 임시 생성
	LoadMap(L"test.map");

	m_MapScene.insert({ L"Tool.scene", new CToolScene(L"Tool.scene")});
	
	//첫번째 씬을 시작 씬으로 지정
	m_currentScene = (*m_MapScene.find(L"start.scene")).second;

	if (m_currentScene != nullptr)
		m_currentScene->Init();

	m_Player = new CPlayer(
			ObjectInfo(
				L"../Resources/Sprites/character_001_isaac.png",
				Vector2(0, 0),
				Vector2(32, 32),
				Vector2(32, 32),
				Vector2(WINDOW_X * 0.5f, WINDOW_Y * 0.5f),
				Vector2(1, 1), OBJECT_TYPE::PLAYER, OBJECT_STATE::IDLE),
			MoverInfo());
	m_Player->Init();
	CObjectMgr::GetInstance()->SetPlayer(m_Player);

	CreateObject(new CFly(ObjectInfo(L"../Resources/Sprites/Enemy/monster_010_fly.png",
		Vector2(0, 0),
		Vector2(32, 32),
		Vector2(32, 32),
		Vector2(300, 300),
		Vector2(1, 1),
		OBJECT_TYPE::ENEMY, OBJECT_STATE::IDLE), EnemyInfo(8, 1, 0, 50.f, 0.f)));

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
	if (m_bIsChange)
	{
		
		static float fadeIn = 0.6f;
		
		if (fadeIn <= 1.0f)
		{
			FadeInOut(fadeIn);
			fadeIn += .05f;
		}

		if (fadeIn >= 1.0f)
		{
			static float fadeOut = 1.0f;
			fadeOut -= .05f;
			FadeInOut(fadeOut);
			
			if (fadeOut <= 0.0f)
			{
				fadeIn = 0.6f;
				fadeOut = 1.0f;
				m_bIsChange = false;
			}
			
		}
	}
	//CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_fadeImg, 0,0, m_fadeImg->GetWidth(), m_fadeImg->GetHeight());
}

void CSceneMgr::Release()
{
	auto iter = m_MapScene.begin();

	for (;iter != m_MapScene.end(); ++iter)
	{
		(*iter).second->Release();
	}
	if (m_currentScene != nullptr)
		m_currentScene->Release();

	delete m_pFadeImg;
	m_pFadeImg = nullptr;
}


void CSceneMgr::ChangeScene(wstring scenePath, DIRECTION dir)
{

	auto iter = m_MapScene.find(scenePath);

	m_bIsChange = true;


	if (iter != m_MapScene.end())
	{
		//등록되어있는 씬으로 옮긴다.
		m_currentScene = (*iter).second;
		m_currentScene->Init();

		//플레이어 이동 
		switch (dir)
		{
		case DIRECTION::UP:
			CObjectMgr::GetInstance()->GetPlayer()->GetTransform()->SetPosition(Vector2(WINDOW_X * 0.5f , (float)WINDOW_Y - PADDING_DOOR));
			break;
		case DIRECTION::DOWN:
			CObjectMgr::GetInstance()->GetPlayer()->GetTransform()->SetPosition(Vector2(WINDOW_X * 0.5f , 0.f + PADDING_DOOR));
			break;
		case DIRECTION::LEFT:
			CObjectMgr::GetInstance()->GetPlayer()->GetTransform()->SetPosition(Vector2((float)WINDOW_X  - PADDING_DOOR, WINDOW_Y * 0.5f));
			break;
		case DIRECTION::RIGHT:
			CObjectMgr::GetInstance()->GetPlayer()->GetTransform()->SetPosition(Vector2(0.f + PADDING_DOOR, WINDOW_Y * 0.5f));
			break;
		case DIRECTION::DIRECTION_END:
			break;
		}
	}

}

void CSceneMgr::ChangeMode(GAME_MODE mode)
{
	if (mode == GAME_MODE::GAME)
	{
		ChangeScene(L"start.scene",DIRECTION::DIRECTION_END);

		if (g_ToolDig != nullptr)
		{
			DestroyWindow(g_ToolDig);
		}
	}
	else if (mode == GAME_MODE::TOOL)
	{
		ChangeScene(L"Tool.scene", DIRECTION::DIRECTION_END);
	}
	else//디버깅모드
	{

	}
}


BOOL CSceneMgr::LoadMap(wstring mapPath)
{
	wstring mapDirectory = (L"..//Resources//Map//");

	mapDirectory += mapPath;

	wifstream wifs(mapDirectory, ios::in);

	wchar_t strTemp[255];

	//씬 개수 얻어오기
	wifs.getline(strTemp, 255);
	int iSceneCount = _wtoi(strTemp);



	for (int i = 0; i < iSceneCount; ++i)
	{
		wifs.getline(strTemp, 255);
		CScene* Scene = new CScene(strTemp); //이름 지정
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

			//파일에 등록된 오브젝트들을 각 씬들에 배치한다.

			desScene->AddObjectToScene(objInfo);
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

void CSceneMgr::FadeInOut(float blending)
{
	const float alphaPercent = blending;

	ColorMatrix colorMatrix = 
	{
		  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		  0.0f, 0.0f, 0.0f, alphaPercent, 0.0f,
		  0.0f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	ImageAttributes imageAttributes;
	imageAttributes.SetColorMatrix(&colorMatrix, ColorMatrixFlagsDefault, ColorAdjustTypeDefault);


	CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_pFadeImg, Rect(0, 0, m_pFadeImg->GetWidth(), m_pFadeImg->GetHeight()),
		0,0,m_pFadeImg->GetWidth(), m_pFadeImg->GetHeight(), UnitPixel, &imageAttributes);
}
