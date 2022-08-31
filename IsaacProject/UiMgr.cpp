#include "stdafx.h"
#include "UiMgr.h"

CUiMgr* CUiMgr::m_pInstance = nullptr;

void CUiMgr::Init()
{
	m_hudImg = new Image(L"..\\Resources\\Sprites\\UI\\hudpickups.png");
	m_numberImg = new Image(L"..\\Resources\\Sprites\\UI\\Number.png");
	m_keyInfo = Spriteinfo(Vector2(16.f, 0.f), Vector2(16.f, 16.f), Vector2(40.f, 70.f));
	m_coinInfo = Spriteinfo(Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(40.f, 100.f));
	m_bombInfo = Spriteinfo(Vector2(0.f, 16.f), Vector2(16.f, 16.f), Vector2(40.f, 130.f));
	m_numberInfo = Spriteinfo(Vector2(0.f, 0.f), Vector2(16.f, 24.f), Vector2(0.f, 0.f));

}

void CUiMgr::RenderBombState()
{
	//이모티콘
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(m_hudImg,
		Rect(m_bombInfo.uiPos.x, m_bombInfo.uiPos.y, m_bombInfo.sizeVec.x * (Scale), m_bombInfo.sizeVec.y * (Scale)),
		m_bombInfo.startVec.x, m_bombInfo.startVec.y, m_bombInfo.sizeVec.x, m_bombInfo.sizeVec.y,UnitPixel
	);

	//16,24

	//10의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_bombInfo.uiPos.x + (m_bombInfo.sizeVec.x * Scale), m_bombInfo.uiPos.y + 5.0f, 
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
		SelectTenNum(ITEM_TYPE::BOMB), m_numberInfo.startVec.y,
		m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
		UnitPixel
	);

	//1의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_bombInfo.uiPos.x + (m_bombInfo.sizeVec.x * Scale) + m_numberInfo.sizeVec.x - 5.0f, m_bombInfo.uiPos.y + 5.0f,
			 m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
			SelectNum(ITEM_TYPE::BOMB), m_numberInfo.startVec.y,
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
			UnitPixel
	);


}

void CUiMgr::RenderKeyState()
{
	//이모티콘
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(m_hudImg,
		Rect(m_keyInfo.uiPos.x, m_keyInfo.uiPos.y, m_keyInfo.sizeVec.x * (Scale), m_keyInfo.sizeVec.y * (Scale)),
		m_keyInfo.startVec.x, m_keyInfo.startVec.y, m_keyInfo.sizeVec.x, m_keyInfo.sizeVec.y,
		UnitPixel
	);

	//10의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_keyInfo.uiPos.x + (m_keyInfo.sizeVec.x * Scale), m_keyInfo.uiPos.y + 5.0f,
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
		SelectTenNum(ITEM_TYPE::KEY), m_numberInfo.startVec.y,
		m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
		UnitPixel
	);

	//1의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_keyInfo.uiPos.x + (m_keyInfo.sizeVec.x * Scale) + m_keyInfo.sizeVec.x - 5.0f, m_keyInfo.uiPos.y + 5.0f,
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
		SelectNum(ITEM_TYPE::KEY), m_numberInfo.startVec.y,
		m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
		UnitPixel
	);
}

void CUiMgr::RenderCoinState()
{
	//이모티콘
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(m_hudImg,
		Rect(m_coinInfo.uiPos.x, m_coinInfo.uiPos.y, m_coinInfo.sizeVec.x * (Scale), m_coinInfo.sizeVec.y * (Scale)),
		m_coinInfo.startVec.x, m_coinInfo.startVec.y, m_coinInfo.sizeVec.x, m_coinInfo.sizeVec.y,
		UnitPixel
	);

	//10의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_coinInfo.uiPos.x + (m_coinInfo.sizeVec.x * Scale), m_coinInfo.uiPos.y + 5.0f,
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
		SelectTenNum(ITEM_TYPE::COIN), m_numberInfo.startVec.y,
		m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
		UnitPixel
	);

	//1의 자리 수
	CImageMgr::GetInstance()->GetGraphics()->DrawImage
	(
		m_numberImg,
		Rect(m_coinInfo.uiPos.x + (m_coinInfo.sizeVec.x * Scale) + m_coinInfo.sizeVec.x - 5.0f, m_coinInfo.uiPos.y + 5.0f,
			m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y),
		SelectNum(ITEM_TYPE::COIN), m_numberInfo.startVec.y,
		m_numberInfo.sizeVec.x, m_numberInfo.sizeVec.y,
		UnitPixel
	);
}

void CUiMgr::Release()
{
	delete m_hudImg;
	delete m_numberImg;
}

void CUiMgr::Render(HDC hdc)
{
	RenderBombState();
	RenderCoinState();
	RenderKeyState();
}

int CUiMgr::SelectTenNum(ITEM_TYPE type)
{
	auto iter = CObjectMgr::GetInstance()->GetPlayer()->GetInventory()->find(type);
	int num = (*iter).second;

	num /= 10;

	int xPos = (num % 10) * m_numberInfo.sizeVec.x;

	return xPos;
}

int CUiMgr::SelectNum(ITEM_TYPE type)
{
	auto iter = CObjectMgr::GetInstance()->GetPlayer()->GetInventory()->find(type);
	int num = (*iter).second;

	int xPos = (num % 10) * m_numberInfo.sizeVec.x;

	return xPos;
}
