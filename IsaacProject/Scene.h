#pragma once
class CScene
{
public:
	CScene();
	CScene(wstring name);
	~CScene();

public:
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
	void AddObjectToScene(ObjectInfo objInfo);
	//Get
	wstring* const GetName() { return &m_Name; }

private:
	wstring m_Name;
	//현재 씬에 존재하고 있는 오브젝트들의 맵 리스트
	map <OBJECT_TYPE, list<CObject*>> m_MapObjectList;
	map <OBJECT_TYPE, list<CObject*>>::iterator m_iter;
};

