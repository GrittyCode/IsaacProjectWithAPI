#include "stdafx.h"
#include "ToolDlg.h"

CToolDlg* CToolDlg::m_pInstance = nullptr;

void CToolDlg::Init()
{
	//변수들 초기화
	m_iButton = 1;
	m_rcCurCopyScale = { 0,0,0,0};
	m_iTileMOde = (UINT)TILE_MODE::MAP;
	m_iIndexX = 0;
	m_iIndexY = 0;
	m_bFlipX = false;
	m_bFlipY = false;
	m_bPress = false;
	m_stTemp = TileInfo();
}

void CToolDlg::Update()
{
}

void CToolDlg::Draw(HDC hdc)
{
	if (m_iTileMOde == (UINT)TILE_MODE::MAP)
	{
		MapDraw(hdc);
	}
	else if (m_iTileMOde == (UINT)TILE_MODE::OBJECT)
	{
		ObjectDraw(hdc);
	}
	else
	{
		EnemyDraw(hdc);
	}
}

void CToolDlg::MapDraw(HDC hdc)
{
	ImageAttributes imgAttr;

	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBuffer = CreateBitmap(576, 384, 1, 32, NULL);

	SelectObject(hMemDC, hBuffer);

	Image* image = nullptr;
	Graphics g(hMemDC);

	if (m_iButton == 1)
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/01_basement.png");
	}
	else if (m_iButton == 2)
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/02_cellar.png");
	}
	else
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/0e_diceroom.png");
	}

	//브러쉬 설정
	HBRUSH hOldBrush;
	hOldBrush = (HBRUSH)SelectObject(hMemDC,GetStockObject(NULL_BRUSH));

	//펜설정
	HPEN hOldPen;
	HPEN CurPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	hOldPen = (HPEN)SelectObject(hMemDC, CurPen);

	if (m_bFlipX)
	{
		image->RotateFlip(Rotate180FlipY);
	}

	if (m_bFlipY)
	{
		image->RotateFlip(Rotate180FlipX);
	}

	g.DrawImage(image, Rect(0, 0, 576, 384),
		0, 0, 468, 312, UnitPixel, &imgAttr);


	Rectangle(hMemDC, m_rcCurCopyScale.left, m_rcCurCopyScale.top, m_rcCurCopyScale.right, m_rcCurCopyScale.bottom);
	
	
	StretchBlt(hdc, 0, 0, 576, 384, hMemDC, 0, 0, 576, 384, SRCCOPY);
	DeleteObject((HPEN)SelectObject(hMemDC, hOldPen));
	
	SelectObject(hMemDC, hOldBrush);

	SelectObject(hMemDC, hOldPen);
	DeleteObject(CurPen);

	DeleteObject(hBuffer);
	DeleteDC(hMemDC);

	g.ReleaseHDC(hdc);
	delete image;
}

void CToolDlg::ObjectDraw(HDC hdc)
{
	ImageAttributes imgAttr;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBuffer = CreateBitmap(384, 256, 1, 32, NULL);

	//384,256
	SelectObject(hMemDC, hBuffer);

	Image* image = nullptr;
	Graphics g(hMemDC);

	if (m_iButton == 1)
	{
		//돌 이미지
		image = Image::FromFile(L"../Resources/Sprites/Object/Object_Wall.png");
	}
	else if (m_iButton == 2)
	{
		//문 이미지
		image = Image::FromFile(L"../Resources/Sprites/Object/Object_door.png");
	}
	else
	{
		//똥이미지
		image = Image::FromFile(L"../Resources/Sprites/Object/Object_firewoodpoop.png");
	}

	//브러쉬 설정
	HBRUSH hOldBrush;
	hOldBrush = (HBRUSH)SelectObject(hMemDC, GetStockObject(NULL_BRUSH));

	//펜설정
	HPEN hOldPen;
	HPEN CurPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	hOldPen = (HPEN)SelectObject(hMemDC, CurPen);

	g.DrawImage(image, Rect(0, 0, 384, 256),
		0, 0, 384, 256, UnitPixel, &imgAttr);

	Rectangle(hMemDC, m_rcCurCopyScale.left, m_rcCurCopyScale.top, m_rcCurCopyScale.right, m_rcCurCopyScale.bottom);


	StretchBlt(hdc, 0, 0, 576, 384, hMemDC, 0, 0, 576, 384, SRCCOPY);

	DeleteObject(hOldBrush);

	SelectObject(hMemDC, hOldPen);
	DeleteObject(CurPen);

	DeleteObject(hBuffer);
	DeleteDC(hMemDC);
	ReleaseDC(g_ToolDig, hdc);
	g.ReleaseHDC(hdc);
	delete image;
}

void CToolDlg::EnemyDraw(HDC hdc)
{
	ImageAttributes imgAttr;
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBuffer = CreateBitmap(576, 384, 1, 32, NULL);

	SelectObject(hMemDC, hBuffer);

	Image* image = nullptr;
	Graphics g(hMemDC);

	if (m_iButton == 1)
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/01_basement.png");
	}
	else if (m_iButton == 2)
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/02_cellar.png");
	}
	else
	{
		image = Image::FromFile(L"../Resources/Sprites/Map/0e_diceroom.png");
	}

	//브러쉬 설정
	HBRUSH hOldBrush;
	hOldBrush = (HBRUSH)SelectObject(hMemDC, GetStockObject(NULL_BRUSH));

	//펜설정
	HPEN hOldPen;
	HPEN CurPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));

	hOldPen = (HPEN)SelectObject(hMemDC, CurPen);

	g.DrawImage(image, Rect(0, 0, 576, 384),
		0, 0, 468, 312, UnitPixel, &imgAttr);

	Rectangle(hMemDC, m_rcCurCopyScale.left, m_rcCurCopyScale.top, m_rcCurCopyScale.right, m_rcCurCopyScale.bottom);

	StretchBlt(hdc, 0, 0, 576, 384, hMemDC, 0, 0, 576, 384, SRCCOPY);

	DeleteObject(hOldBrush);

	SelectObject(hMemDC, hOldPen);
	DeleteObject(CurPen);

	DeleteObject(hBuffer);
	DeleteDC(hMemDC);
}

int CToolDlg::GetTileMode()
{
	return m_iTileMOde;
}

bool CToolDlg::GetPress()
{
	return m_bPress;
}

bool CToolDlg::GetFilpX()
{
	return false;
}

bool CToolDlg::GetFilpY()
{
	return false;
}

TileInfo CToolDlg::GetTileTemp()
{
	return m_stTemp;
}

ObjectInfo CToolDlg::GetObjInfo()
{
	return m_stObj;
}

void CToolDlg::SetTileMode(int mode)
{
	m_iTileMOde = mode;
}

void CToolDlg::SetButton(int button)
{
	m_iButton = button;
}

void CToolDlg::SetIndexX(int x)
{
	m_iIndexX = x;
}

void CToolDlg::SetIndexY(int y)
{
	m_iIndexY = y;
}

void CToolDlg::SetFilpX()
{
	m_bFlipX = !m_bFlipX;
}

void CToolDlg::SetFilpY()
{
	m_bFlipY = !m_bFlipY;
}

void CToolDlg::SetPress(bool press)
{
	m_bPress = press;
}

void CToolDlg::SetStartScale(POINT rc)
{
	rc.x /= TOOL_TILE_SIZE;

	rc.y /= TOOL_TILE_SIZE;

	m_rcCurCopyScale = { (rc.x * TOOL_TILE_SIZE),(rc.y * TOOL_TILE_SIZE),(rc.x * TOOL_TILE_SIZE) + TOOL_TILE_SIZE,(rc.y * TOOL_TILE_SIZE) 
		+ TOOL_TILE_SIZE };
}

void CToolDlg::SetCurScale(POINT rc)
{
	rc.x /= TOOL_TILE_SIZE;

	rc.y /= TOOL_TILE_SIZE;

	m_rcCurCopyScale.right = ((rc.x + 1) * TOOL_TILE_SIZE);
	m_rcCurCopyScale.bottom = ((rc.y + 1) * TOOL_TILE_SIZE);

}

void CToolDlg::SetTileTemp()
{
	wstring wSrt;

	int StartSclaseX = 0;
	int StartSclaseY = 0;
	int SclaseX = 0;
	int SclaseY = 0;

	if (m_iTileMOde == (UINT)TILE_MODE::MAP)

	if (m_iButton == 1)
	{
		wSrt = L"../Resources/Sprites/Map/01_basement.png";
	}
	else if (m_iButton == 2)
	{
		wSrt = L"../Resources/Sprites/Map/02_cellar.png";
	}
	else
	{
		wSrt = L"../Resources/Sprites/Map/0e_diceroom.png";
	}

	StartSclaseX = (m_rcCurCopyScale.left / TOOL_TILE_SIZE) * 26;
	StartSclaseY = (m_rcCurCopyScale.top / TOOL_TILE_SIZE) * 26;
	SclaseX = (m_rcCurCopyScale.right / TOOL_TILE_SIZE) * 26;
	SclaseY = (m_rcCurCopyScale.bottom / TOOL_TILE_SIZE) * 26;

	m_stTemp = TileInfo(wSrt,
		Vec2(StartSclaseX,StartSclaseY),
		Vec2((SclaseX - StartSclaseX), (SclaseY - StartSclaseY)),
		Vec2((SclaseX - StartSclaseX),(SclaseY - StartSclaseY)),
		SORTING_LAYER::TILE, 
		TILE_TYPE::NONE,
		m_bFlipX,
		m_bFlipY);
}


void CToolDlg::SetObjectTemp()
{
	wstring wSrt;

	int StartSclaseX = 0;
	int StartSclaseY = 0;
	int ScaleX = 0;
	int ScaleY = 0;

	if (m_iTileMOde == (UINT)TILE_MODE::OBJECT)
	{
		
		if (m_iButton == 1)
		{
			//임시
			wSrt = L"../Resources/Sprites/Object/Object_Wall.png";
		}
		else if (m_iButton == 2)
		{
			wSrt = L"../Resources/Sprites/Object/Object_door.png";
		}
		else
		{
			wSrt = L"../Resources/Sprites/Object/Object_firewoodpoop.png";
		}

		StartSclaseX = (m_rcCurCopyScale.left / TOOL_TILE_SIZE) * 32;
		StartSclaseY = (m_rcCurCopyScale.top / TOOL_TILE_SIZE) * 32;
		ScaleX = (m_rcCurCopyScale.right / TOOL_TILE_SIZE) * 32;
		ScaleY = (m_rcCurCopyScale.bottom / TOOL_TILE_SIZE) * 32;

		m_stObj = ObjectInfo(wSrt,
			Vec2(StartSclaseX, StartSclaseY),
			Vec2((ScaleX - StartSclaseX), (ScaleX - StartSclaseX)),
			Vec2((ScaleX - StartSclaseX), (ScaleY - StartSclaseY)),
			Vec2(1.0f, 1.0f),
			Vec2(1.0f,1.0f),
			m_stObj.type,
			OBJECT_STATE::IDLE);
	}
}


BOOL CToolDlg::SaveSceneFromTool(wstring sceneName)
{
	wstring directory = L"..\\Resources\\Scene\\";
	wstring desination = directory + sceneName;

	wofstream ofs(desination, ios::out | ios::trunc);


	auto mapObjList = CObjectMgr::GetInstance()->GetMapObjectList();
	auto mapIter = mapObjList->begin();


	//오브젝트에 존재하는 모든 리스트 저장
	for (int i = 0; i < (int)OBJECT_TYPE::OBJECT_TYPE_END; ++i)
	{
		mapIter = mapObjList->find((OBJECT_TYPE)i);

		//오브젝트 파일 저장
		if (mapIter != mapObjList->end())
		{
			for (CObject* obj : (*mapIter).second)
			{
				//스프라이트 정보값 저장
				ofs << obj->GetInfo()->wpath << ','
					<< obj->GetInfo()->vecStartPos.x << ',' << obj->GetInfo()->vecStartPos.y << ','
					<< obj->GetInfo()->vecEndPos.x << ',' << obj->GetInfo()->vecEndPos.y << ','
					<< obj->GetInfo()->vecSize.x << ',' << obj->GetInfo()->vecSize.y << ',';

				//위치값, 크기값 저장 
				ofs << obj->GetInfo()->vecWorldPos.x << ',' << obj->GetInfo()->vecWorldPos.y << ','
					<< obj->GetInfo()->vecScale.x << ',' << obj->GetInfo()->vecScale.y << ',';

				ofs << (UINT)obj->GetInfo()->type << ',' << (UINT)obj->GetInfo()->state << '\n';
			}
		}
	}
	MessageBox(g_hWnd, L"씬 저장 완료!", L"저장 완료", TRUE);
	ofs.close();
	return (INT_PTR)TRUE;
}

void CToolDlg::BarPosUP()
{
}

void CToolDlg::BarPosDown()
{
}