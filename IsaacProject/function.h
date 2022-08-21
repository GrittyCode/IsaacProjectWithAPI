#pragma once

class CObject;
class CAnimation;

Vector2 VectorSum(Vector2 movevec, Vector2 attackvec, float playerspeed, float tearsspeed);
Vector2 IndexToPosition(POINT pt);
Vector2 MapIndexToPosition(POINT pt);

POINT PostionToIndex(Vector2 pos);
POINT MapPostionToIndex(Vector2 pos);

BOOL Save(HDC hdc, HBITMAP hBitmap, const wchar_t* name, uint16_t BitsPerPixel = 24);

float DistanceMeasure(Vector2 sourse, Vector2 taget);

void CreateObject(CObject* pObj);
void DeleteObject(CObject* pObj);

void CreateEffect(CAnimation* pObj);
void DeleteEffect(CAnimation* pObj);