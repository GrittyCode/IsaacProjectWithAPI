#pragma once

class CSceneMgr
{
	SINGLETON(CSceneMgr)
public:
	void Init();
	void Update();
	void FixedUpdate();
	void Render(HDC hdc);
	void Release();
	void ChangeScene(wstring scenePath, DIRECTION dir);
	void ChangeMode(GAME_MODE mode);
	void CreateStageFromTool();
	void FadeInOut(float blending);

	map<wstring, CScene*>* const GetMapScene() { return &m_MapScene; }
	/*
	bool CreateStageFromInfo(wstring path,int xIndex, int yIndex);
	void CreateMapFromFile(wstring mapPath);
	BOOL LoadMap(wstring mapPath);
	*/

	BOOL LoadMap(wstring mapPath);
	BOOL SetSceneFromSceneSave(CScene* desScene);

	//Get
	wstring GetCurSceneName();
	CScene* const GetCurScene() const { return m_currentScene; };


private:
	CPlayer* m_Player;
	//격자무늬의 세계를 생성
	INT m_iMiniMap[8][9];
	//만들어진 방을 확인하여 랜덤하게 선택한 후, 4방향에 랜덤하게 생성
	vector<POINT> m_createdMap;
	map<wstring,CScene*> m_MapScene;
	CScene* m_currentScene = nullptr;


	//씬 전환 이미지
	Image* m_pFadeImg;
	BOOL m_bIsChange = true;
	BOOL m_bIsFirst = true;
};

