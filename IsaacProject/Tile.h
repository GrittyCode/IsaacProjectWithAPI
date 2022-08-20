#pragma once
//JUST FOR TOOL 
class CTile : public CObject
{
private:
	TileInfo m_Tile;
	TilePos m_Pos;
	Image* m_image;
public:
	//∞°ªÛ∆—≈‰∏Æ
	void Init();
	void Update();
	void LateUpdate();
	void FixedUpdate();
	void Render(HDC hdc);
	void Release();
	void SetTileInfo(TileInfo temp);
	void SetTilePos(TilePos pos) { m_Pos = pos; }
	
	const TilePos GetTilePos()  const { return m_Pos; }
	const TileInfo GetTileInfo() const { return m_Tile; }
	virtual INT CheckCollisionState() { return ERROR_STATE; };

	TILE_TYPE GetTileType() const { return m_Tile.TYPE; };
	CTile(TileInfo tileInfo, TILEPOS tilepos);
	~CTile();
};


