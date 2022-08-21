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

	void ChangeScene(wstring scenePath);
	void ChangeMode(GAME_MODE mode);
	void CreateStageFromTool();
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
	//���ڹ����� ���踦 ����
	INT m_iMiniMap[8][9];
	//������� ���� Ȯ���Ͽ� �����ϰ� ������ ��, 4���⿡ �����ϰ� ����
	vector<POINT> m_createdMap;
	map<wstring,CScene*> m_MapScene;
	CScene* m_currentScene = nullptr;
};

