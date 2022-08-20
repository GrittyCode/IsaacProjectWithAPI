#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include "ToolScene.h"


INT_PTR CALLBACK ToolDlg(HWND g_hToolDlg, UINT message, WPARAM wParam, LPARAM lParam);

CToolScene::CToolScene()
	:m_rcTool(RECT())
{
}

CToolScene::~CToolScene()
{
}

void CToolScene::Init()
{
	//Tool의 window크기 설정
	RECT rc = { 0,0,1000,1000 };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, true);//실제 크기 반환
	SetWindowPos(g_hWnd, nullptr, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0);//설정한 크기로 해줌

	//Tool 다이어그램 만들기
	g_ToolDig = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_TOOL), g_hWnd, ToolDlg);

	GetClientRect(g_ToolDig, &m_rcTool);
	AdjustWindowRect(&m_rcTool, WS_OVERLAPPEDWINDOW, true);

	ShowWindow(g_ToolDig, SW_SHOW);

	CSceneMgr::GetInstance()->CreateStageFromTool();
}

void CToolScene::Update()
{
	RECT rcWindow;
	POINT CursorPos;
	Vector2 pTemp;
	TileInfo TileTemp;
	int iMainStartIndex;
	int iMapX;
	int iMapY;

	GetCursorPos(&CursorPos);
	ScreenToClient(g_hWnd, &CursorPos);

	GetWindowRect(g_hWnd, &rcWindow);
	MoveWindow(g_ToolDig, rcWindow.right, rcWindow.top, m_rcTool.right - m_rcTool.left, m_rcTool.bottom - m_rcTool.top, true);

	//눌린 상태라면 대입시작
	if (CKeyMgr::GetInstance()->GetKeyState((UINT)KEY::LBUTTON) != KEY_STATE::TAP)
	{
		return;
	}
		
	//윈도우 범위 이내에 없을시 return
	GetClientRect(g_hWnd,&rcWindow);

	if ((rcWindow.left > CursorPos.x || rcWindow.right < CursorPos.x) ||
		(rcWindow.top > CursorPos.y || rcWindow.bottom < CursorPos.y))
	{
		return;
	}
	//필요한 값들 셋팅

	if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::MAP)
	{
		TileInfo CurInfo = CToolDlg::GetInstance()->GetTileTemp();

		pTemp = PostionToIndex(Vector2(CursorPos.x, CursorPos.y));
		iMainStartIndex = (INT)(pTemp.x + (pTemp.y * 18.f));

		pTemp = MapPostionToIndex(CurInfo.v_Size);
		iMapX = (INT)pTemp.x;
		iMapY = (INT)pTemp.y;

		INT tempX = (INT)CurInfo.v_StartPos.x;
		CurInfo.v_Size.x = TILE_SIZE;
		CurInfo.v_Size.y = TILE_SIZE;

		vector<CTile*>* tile = CObjectMgr::GetInstance()->GetMapTileVector();

		for (size_t i = 0; i < iMapY; ++i)
		{
			for (size_t j = 0; j < iMapX; ++j)
			{
				//인덱스				
				tile->at(iMainStartIndex + (j + (i * ROW)))->SetTileInfo(CurInfo);
				tile->at(iMainStartIndex + (j + (i * ROW)))->Init();

				CurInfo.v_StartPos.x += TILE_SIZE;
				CurInfo.v_EndPos.x += TILE_SIZE;
			}
			CurInfo.v_StartPos.y += TILE_SIZE;
			CurInfo.v_EndPos.y += TILE_SIZE;
			CurInfo.v_StartPos.x = (FLOAT)tempX;
		}
	}
	else if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::OBJECT)
	{
		ObjectInfo CurInfo = CToolDlg::GetInstance()->GetObjInfo();
		CursorPos.x -= (CursorPos.x % 26);
		CursorPos.y -= (CursorPos.y % 26);
		CurInfo.vecWorldPos = CursorPos;
		CObjectMgr::GetInstance()->SetObjectFromFile(CurInfo);
	}
}

void CToolScene::FixedUpdate()
{
}

void CToolScene::Render(HDC hdc)
{

	CObjectMgr::GetInstance()->Render(hdc);
	POINT CursorPos;

	GetCursorPos(&CursorPos);
	ScreenToClient(g_hWnd, &CursorPos);

	ImageAttributes imgAttr;

	Image* image = nullptr;
	Graphics g(hdc);

	if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::MAP)
	{
		TileInfo stTemp = CToolDlg::GetInstance()->GetTileTemp();

		image = Image::FromFile(stTemp.path.c_str());

		if (stTemp.isXFlip)
		{
			image->RotateFlip(Rotate180FlipY);
		}

		if (stTemp.isYFlip)
		{
			image->RotateFlip(Rotate180FlipX);
		}

		/*mat.RotateAt(180, Gdiplus::PointF(CursorPos.x + (image->GetWidth() / 2), CursorPos.y + (image->GetHeight() / 2)));
		g.SetTransform(&mat);*/
		g.DrawImage(image, Rect((int)CursorPos.x, (int)CursorPos.y,
			(int)(stTemp.v_Size.x * Scale), (int)(stTemp.v_Size.y * Scale)),
			(int)stTemp.v_StartPos.x, (int)stTemp.v_StartPos.y, (int)stTemp.v_Size.x, (int)stTemp.v_Size.y, UnitPixel, &imgAttr);
	}
	else if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::OBJECT)
	{
		ObjectInfo stTemp = CToolDlg::GetInstance()->GetObjInfo();

		image = Image::FromFile(stTemp.wpath .c_str());

		g.DrawImage(image, Rect((int)CursorPos.x - stTemp.vecSize.x, (int)CursorPos.y - stTemp.vecSize.y,
			(int)(stTemp.vecSize.x * Scale), (int)(stTemp.vecSize.y * Scale)),
			(int)stTemp.vecStartPos.x, (int)stTemp.vecStartPos.y, (int)stTemp.vecSize.x, (int)stTemp.vecSize.y, UnitPixel, &imgAttr);
	}
	
	g.ReleaseHDC(hdc);
	delete image; 
}

INT_PTR CALLBACK ToolDlg(HWND g_hToolDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
	static TCHAR str[128] = { 0 };
	static TCHAR FilePath[128] = FILE_PATH;

	static wstring OBJECT_TYPE[(int)OBJECT_TYPE::OBJECT_TYPE_END] = 
			{L"BACKGROUND", L"OBSTACLE",
			L"PLAYER_TEAR",L"ENEMY_TEAR", 
		    L"BOMB", L"DOOR", L"ITEM",
			L"ENEMY",L"PLAYER",L"BOSS"};
	static HWND hcomboType = nullptr;

    switch (message)
    {
	case WM_INITDIALOG:
	{
		hcomboType = GetDlgItem(g_hToolDlg, IDC_COMBO_TYPE);

		for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
			SendMessage(hcomboType, CB_INSERTSTRING, -1, (LPARAM)OBJECT_TYPE[i].c_str());
	}
	break;
    case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_COMBO_TYPE:
			switch (HIWORD(wParam))
			{
				case CBN_SELCHANGE:
				{
					TCHAR temp[128] = L"";
					INT i = (INT)SendMessage(hcomboType, CB_GETCURSEL, 0, 0);
					CToolDlg::GetInstance()->SetObjectType(i);

					int j = 0;
				}
				break;
			}
		break;
		case IDC_SCENE_SAVE:
		{
			GetDlgItemText(g_hToolDlg, IDC_NAME_INPUT, (LPWSTR)str, 128);
			CToolDlg::GetInstance()->SaveSceneFromTool(str);
		}
		break;
		case IDC_SAVE_BUTTON:
		{
			GetDlgItemText(g_hToolDlg, IDC_NAME_INPUT, (LPWSTR)str, 128); 
			_tcscat(FilePath,str);
			Save(CGameMgr::GetInstance()->GetMemDC(),
				CGameMgr::GetInstance()->GetBuffer(),
				FilePath);
		}
		break;
		case IDC_LODE_BUTTON:
		{
			TCHAR filter[] = L"Bmp File\0*.bmp\0";
			OPENFILENAME OFN;
			TCHAR filePathName[100] = L"";
			TCHAR lpstrFile[100] = L"";

			memset(&OFN, 0, sizeof(OPENFILENAME));
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = g_hToolDlg;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile;
			OFN.nMaxFile = 100;
			OFN.lpstrInitialDir = L".";

			wchar_t Directory[256] = L"..\\";

			int Cnt = 3;

			if (GetOpenFileName(&OFN) != 0)
			{
				bool bCheck = false;
				bool bOnce = false;
				for (size_t i = 0; i < wcslen(OFN.lpstrFile); ++i)
				{
					if (!bCheck)
					{
						if ((OriginDirectory[i] != OFN.lpstrFile[i]))
							bCheck = true;

						continue;
					}

					if (!bOnce)
					{
						Directory[Cnt++] = OFN.lpstrFile[i - 1];
						bOnce = true;
					}
					Directory[Cnt++] = OFN.lpstrFile[i];
				}
			}

			SetCurrentDirectory(OriginDirectory);

			CreateObject(new CBackground(ObjectInfo(Directory,OBJECT_TYPE::BACKGROUND, OBJECT_STATE::IDLE)));

		}
		break;
		case IDC_RETURN_BUTTON:
		{
			//세로 칸수
			GetDlgItemText(g_hToolDlg, IDC_START_X, str, 128);

			if (_ttoi(str) > 0)
			{
				CToolDlg::GetInstance()->SetIndexX(_ttoi(str));
			}

			memset(str, '\0', 128);

			//가로 칸수
			GetDlgItemText(g_hToolDlg, IDC_START_Y, str, 128);

			if (_ttoi(str) > 0)
			{
				CToolDlg::GetInstance()->SetIndexY(_ttoi(str));
			}
		}
		break;
		case IDC_CHECK_X:
		{
			if (SendMessage(g_hToolDlg, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				CToolDlg::GetInstance()->SetFilpX();
				CToolDlg::GetInstance()->SetTileTemp();
			}
		}
		break;
		case IDC_CHECK_Y:
		{
			if (SendMessage(g_hToolDlg, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
			{
				CToolDlg::GetInstance()->SetFilpY();
				CToolDlg::GetInstance()->SetTileTemp();
			}
		}
		break;
		case IDC_MAP_BUTTON:
		{
			CToolDlg::GetInstance()->SetTileMode((UINT)TILE_MODE::MAP);
		}
		break;
		case IDC_OBJECT_BUTTON:
		{
			CToolDlg::GetInstance()->SetTileMode((UINT)TILE_MODE::OBJECT);
		}
		break;
		case IDC_ENEMY_BUTTON:
		{
			CToolDlg::GetInstance()->SetTileMode((UINT)TILE_MODE::ENEMY);
		}
		break;
		case IDC_BUTTON1:
		{
			CToolDlg::GetInstance()->SetButton(1);
		}
		break;
		case IDC_BUTTON2:
		{
			CToolDlg::GetInstance()->SetButton(2);
		}
		break;
		case IDC_BUTTON3:
		{
			CToolDlg::GetInstance()->SetButton(3);
		}
		break;
		default:
		break;
		}
		InvalidateRect(g_hToolDlg, NULL,true);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(g_hToolDlg,&ps);

		CToolDlg::GetInstance()->Draw(hdc);

		EndPaint(g_hToolDlg, &ps);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT CursorPos;

		GetCursorPos(&CursorPos);
		ScreenToClient(g_hToolDlg,&CursorPos);

		if (CToolDlg::GetInstance()->GetPress() == false)
		{
			CToolDlg::GetInstance()->SetStartScale(CursorPos);
			CToolDlg::GetInstance()->SetPress(true);
			InvalidateRect(g_hToolDlg, NULL, FALSE);
		}
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT CursorPos;

		GetCursorPos(&CursorPos);
		ScreenToClient(g_hToolDlg, &CursorPos);

		if (CToolDlg::GetInstance()->GetPress() == true)
		{
			CToolDlg::GetInstance()->SetCurScale(CursorPos);
			InvalidateRect(g_hToolDlg, NULL, FALSE);
		}
	}
	break;
	case WM_LBUTTONUP:
	{
		if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::MAP)
		{
			CToolDlg::GetInstance()->SetPress(false);
			CToolDlg::GetInstance()->SetTileTemp();
		}
		else if (CToolDlg::GetInstance()->GetTileMode() == (UINT)TILE_MODE::OBJECT)
		{
			CToolDlg::GetInstance()->SetPress(false);
			CToolDlg::GetInstance()->SetObjectTemp();
		}
		InvalidateRect(g_hToolDlg, NULL, FALSE);
	}
	break;
	default:
	break;
    }
    return (INT_PTR)FALSE;
}
