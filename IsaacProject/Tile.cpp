#include "stdafx.h"
#include "Tile.h"



CTile::~CTile()
{
	Release();
}

CTile::CTile(TileInfo tileInfo, TILEPOS tilepos):
	m_Tile(tileInfo),
	m_Pos(tilepos)
{
}


void CTile::Init()
{
	//현재 이미
	delete m_image;
	m_image = Image::FromFile(m_Tile.path.c_str());


	if (m_Tile.isXFlip)
	{
		m_image->RotateFlip(Rotate180FlipY);
	}

	if (m_Tile.isYFlip)
	{
		m_image->RotateFlip(Rotate180FlipX);
	}

}

void CTile::Update()
{
	if (CGameMgr::GetInstance()->GetWindowChanged())
	{
		m_Pos.ChangeWindowScale();
	}
}

void CTile::LateUpdate()
{
}

void CTile::FixedUpdate()
{
}

void CTile::Render(HDC hdc)
{
	if(m_Tile.path != L"")
	{
		CImageMgr::GetInstance()->GetGraphics()->DrawImage(m_image,
			Rect((int)m_Pos.WorldPos.x, (int)m_Pos.WorldPos.y,
			(int)(m_Tile.v_Size.x * Scale), (int)(m_Tile.v_Size.y * Scale)),
			(int)m_Tile.v_StartPos.x, (int)m_Tile.v_StartPos.y, (int)m_Tile.v_Size.x, (int)m_Tile.v_Size.y, UnitPixel);
	}
	else
	{
		//펜설정
		HBRUSH	hOldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
		HPEN CurPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		HPEN hOldPen = (HPEN)SelectObject(hdc, CurPen);

		Rectangle(hdc, (INT)m_Pos.WorldPos.x, (INT)m_Pos.WorldPos.y, 
			(INT)m_Pos.WorldPos.x  + (int)(TILE_SIZE * Scale), (INT)m_Pos.WorldPos.y + (int)(TILE_SIZE * Scale));
		
		DeleteObject(hOldBrush);
		SelectObject(hdc, hOldPen);
		DeleteObject(CurPen);
	}
	
}

void CTile::Release()
{
	for (size_t i = 0; i < (int)COMPONENT_TYPE::COMPONENT_TYPE_END; ++i)
	{
		m_iter = m_MapComponent.find((COMPONENT_TYPE)i);

		//찾는 컴포넌트가 있다면
		if (m_iter != m_MapComponent.end())
		{
			delete (*m_iter).second;
			(*m_iter).second = nullptr;
		}
	}
	delete m_image;
	m_image = nullptr;
}

void CTile::SetTileInfo(TileInfo temp)
{
	if (m_image != nullptr)
	{
		delete m_image;
		m_image = nullptr;
	}

	 m_Tile = temp; 
}


