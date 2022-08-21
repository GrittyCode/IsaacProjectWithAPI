#include "stdafx.h"
#include "function.h"

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)

POINT PostionToIndex(Vector2 pos)
{
	LONG row = (LONG)(pos.x / (TILE_SIZE * Scale));
	LONG colmn = (LONG)(pos.y / (TILE_SIZE * Scale));
	return POINT{ row,colmn };
}

Vector2 IndexToPosition(POINT pt)
{
	float row = (FLOAT)pt.x / (TILE_SIZE * Scale);
	float colmn = (FLOAT)pt.y / (TILE_SIZE * Scale);
	return Vector2{ row,colmn };
}

POINT MapPostionToIndex(Vector2 pos)
{
	LONG row = (LONG)(pos.x / (TILE_SIZE));
	LONG colmn = (LONG)(pos.y / (TILE_SIZE));
	return POINT{ row,colmn };
}

Vector2 MapIndexToPosition(POINT pt)
{
	float row = (float)pt.x / (TILE_SIZE * Scale);
	float colmn = (float)pt.y / (TILE_SIZE * Scale);
	return Vector2{ row,colmn };
}

BOOL Save(HDC hdc, HBITMAP hBitmap, const wchar_t* name, uint16_t BitsPerPixel)
{

	BITMAP bitmap;
	GetObject(hBitmap, sizeof(bitmap), (LPSTR)&bitmap);

	uint32_t Width = bitmap.bmWidth;
	uint32_t Height = bitmap.bmHeight;

	BITMAPINFO Info;
	BITMAPFILEHEADER Header;
	memset(&Info, 0, sizeof(Info));
	memset(&Header, 0, sizeof(Header));
	Info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	Info.bmiHeader.biWidth = Width;
	Info.bmiHeader.biHeight = Height;
	Info.bmiHeader.biPlanes = 1;
	Info.bmiHeader.biBitCount = BitsPerPixel;
	Info.bmiHeader.biCompression = BI_RGB;
	Info.bmiHeader.biSizeImage = Width * Height * (BitsPerPixel > 24 ? 4 : 3);
	Header.bfType = 0x4D42;
	Header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	char* Pixls = NULL;
	HDC MemDC = CreateCompatibleDC(hdc);
	HBITMAP Section = CreateDIBSection(hdc, &Info, DIB_RGB_COLORS, (void**)&Pixls, 0, 0);
	DeleteObject(SelectObject(MemDC, Section));
	BitBlt(MemDC, 0, 0, Width, Height, hdc, 0, 0, SRCCOPY);
	DeleteDC(MemDC);

	std::fstream hFile(name, std::ios::out | ios::binary);

	if (hFile.is_open())
	{
		hFile.write((char*)&Header, sizeof(Header));
		hFile.write((char*)&Info.bmiHeader, sizeof(Info.bmiHeader));
		hFile.write(Pixls, (((BitsPerPixel * Width + 31) & ~31) / 8) * Height);
		hFile.close();
		DeleteObject(Section);
		return true;
	}
	DeleteObject(Section);
	return false;
}


Vector2 VectorSum(Vector2 movevec,Vector2 attackvec,float playerspeed, float tearsspeed)
{
	Vector2 sumvec;
	
	attackvec = Vector2(tearsspeed * attackvec.x, tearsspeed * attackvec.y);
	movevec = Vector2(playerspeed * movevec.x, playerspeed * movevec.y);

	sumvec.x = attackvec.x + movevec.x;
	sumvec.y = attackvec.y + movevec.y;

	return sumvec;
}

float DistanceMeasure(Vector2 sourse, Vector2 taget)
{
	float tmep = sqrtf(powf(sourse.x - taget.x, 2) + powf(taget.y - sourse.y, 2));
	cout << tmep << endl;

	return tmep;
}

void CreateObject(CObject* pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)pObj;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void DeleteObject(CObject* pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)pObj;

	CEventMgr::GetInstance()->AddEvent(evn);
}

void ChageScene(wstring* sceneName)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)sceneName;

	CEventMgr::GetInstance()->AddEvent(evn);
}

