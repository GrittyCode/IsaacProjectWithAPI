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
	map<wstring,CScene*> m_MapScene;
	CScene* m_currentScene = nullptr;
};

