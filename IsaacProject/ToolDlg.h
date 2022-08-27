#pragma once

class CToolDlg
{
	SINGLETON(CToolDlg)
public:
	void Init();
	void Update();
	void Draw(HDC hdc);
	void MapDraw(HDC hdc);
	void ObjectDraw(HDC hdc);
	void EnemyDraw(HDC hdc);

	//GET
	int GetTileMode();
	bool GetPress();
	bool GetFilpX();
	bool GetFilpY();
	TileInfo GetTileTemp();
	ObjectInfo GetObjInfo();

	//SET
	void SetTileMode(int mode);
	void SetButton(int botton);
	void SetIndexX(int x);
	void SetIndexY(int y);
	void SetFilpX();
	void SetFilpY();
	void SetPress(bool press);
	void SetStartScale(POINT rc);
	void SetCurScale(POINT rc);
	void SetTileTemp();
	void SetObjectTemp();
	void SetObjectType(int n) {m_stObj.type = (OBJECT_TYPE)n;}
	BOOL SaveSceneFromTool(wstring sceneName);

	//METHOD
	void BarPosUP();
	void BarPosDown();
private:
	int m_iTileMOde = 0;
	int m_iButton = 0;
	int m_iIndexX = 0;
	int m_iIndexY = 0;
	bool m_bFlipX = 0;
	bool m_bFlipY = 0;
	bool m_bPress = 0;

	RECT m_rcCurCopyScale = {0,0};

	TileInfo m_stTemp;
	ObjectInfo m_stObj;
};