#include "stdafx.h"
#include "SceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

void CSceneMgr::Init()
{
	m_currentScene = new CScene(L"test2.Scene",ROW,COLMN);

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
		m_currentScene = new CToolScene();
		m_currentScene->Init();
	}
	else//�������
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

BOOL CSceneMgr::LoadScene(wstring scenePath)
{
	Release();

#ifdef DEBUG
	wcout << OriginDirectory << endl;
#endif // DEBUG

	

	wstring mapDirectory = (L"..//Resources//Scene//");

	mapDirectory += scenePath;

	wifstream ifs(mapDirectory, ios::in);

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

			//���Ͽ� ��ϵ� ������Ʈ���� ������Ʈ �Ŵ����� �����Ѵ�.
			CObjectMgr::GetInstance()->SetObjectFromFile(objInfo);
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
		return m_currentScene->GetName();
	}

	return L"";
}



//LEGACY CODE

/*
	//Ÿ�ϸ� ���� -> ������, Ÿ�� ����
	if (ifs.is_open())
	{
		for (UINT i = 0; i < (i_tileColmn * i_tileRow); ++i)
		{
				//Ÿ�� ������ ����
				for (int pos = 0; pos < (int)TILE_POS::TILE_POS_END; ++pos)
				{
					//���� ������ �� ����
					tempStr.clear();

					while (true)
					{
						//���� �ϳ� ��������
						ifs.get(tempchar);

						if (tempchar == ',' || tempchar == '\n')
						{
							break;
						}

						//���� ���� �ϳ� ����
						tempStr += tempchar;
					}

					switch (pos)
					{
					case (int)TILE_POS::IDX_ROW:
						tempPos.row = _wtoi(tempStr.c_str());
						break;
					case (int)TILE_POS::IDX_COLMN:
						tempPos.colmn = _wtoi(tempStr.c_str());
						break;
					case (int)TILE_POS::WORLDPOS_X:
						tempPos.WorldPos.x = _wtoi(tempStr.c_str()) * Scale;
						break;
					case (int)TILE_POS::WORLDPOS_Y:
						tempPos.WorldPos.y = _wtoi(tempStr.c_str()) * Scale;
						break;
					case (int)TILE_POS::LOCALPOS_X:
						tempPos.LocalPos.x = _wtoi(tempStr.c_str()) * Scale;
						break;
					case (int)TILE_POS::LOCALPOS_Y:
						tempPos.LocalPos.y = _wtoi(tempStr.c_str()) * Scale;
						break;
					}
				}

				tempStr.clear();

				//Ÿ�� �̹��� ����
				for (int info = 0; info < (int)TILE_INFO::TILE_INFO_END; ++info)
				{
					tempStr.clear();

					while (true)
					{
						//���� �ϳ� ��������
						ifs.get(tempchar);

						if (tempchar == ',' || tempchar == '\n')
						{
							break;
						}

						//���� ���� �ϳ� ����
						tempStr += tempchar;
					}

					switch (info)
					{
					case (int)TILE_INFO::PATH:
						tempInfo.path = tempStr;
						break;
					case (int)TILE_INFO::STARTPOS_X:
						tempInfo.v_StartPos.x = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::STARTPOS_Y:
						tempInfo.v_StartPos.y = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::ENDPOS_X:
						tempInfo.v_EndPos.x = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::ENDPOS_Y:
						tempInfo.v_EndPos.y = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::SIZE_X:
						tempInfo.v_Size.x = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::SIZE_Y:
						tempInfo.v_Size.y = (FLOAT)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::LAYER:
						tempInfo.LAYER = (SORTING_LAYER)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::TYPE:
						tempInfo.TYPE = (TILE_TYPE)_wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::FLIP_X:
						tempInfo.isXFlip = _wtoi(tempStr.c_str());
						break;
					case (int)TILE_INFO::FLIP_Y:
						tempInfo.isYFlip = _wtoi(tempStr.c_str());
						break;
					}
				}


				//Ÿ�� ����
				CObjectMgr::GetInstance()->AddTile(new CTile(tempInfo, tempPos));

		}
	}



*/