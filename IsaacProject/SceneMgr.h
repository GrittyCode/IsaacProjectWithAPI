#pragma once

class CSceneMgr
{
	SINGLETONE(CSceneMgr)
public:
	void Init();
	void Update();
	void FixedUpdate();
	void Render(HDC hdc);
	void Release();

	void ChangeScene(INT index);
	void ChangeMode(GAME_MODE mode);
	void CreateStageFromTool();
	
	/*
	bool CreateStageFromInfo(wstring path,int xIndex, int yIndex);
	void CreateMapFromFile(wstring mapPath);
	BOOL LoadMap(wstring mapPath);
	*/

	BOOL LoadMap(wstring mapPath);
	BOOL LoadScene(wstring scenePath);

	//Get
	wstring GetCurSceneName();
	CScene* GetCurScene() { return m_currentScene; };


private:
	//격자무늬의 세계를 생성
	INT m_iMiniMap[8][9];
	//만들어진 방을 확인하여 랜덤하게 선택한 후, 4방향에 랜덤하게 생성
	vector<POINT> m_createdMap;

	map<wstring,CScene*> m_MapScene;
	CScene* m_currentScene = nullptr;
};

