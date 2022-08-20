#pragma once
class CObjectMgr
{
	SINGLETONE(CObjectMgr)
public:
	BOOL SetObjectFromFile(ObjectInfo info);
	BOOL AddObject(CObject* object);
	BOOL AddTile(CTile* tile);
	void Init();
	void Update();
	void FixedUpdate();
	void Render(HDC hdc);
	void Release();


	//GET
	map<OBJECT_TYPE, list<CObject*>>* GetMapObjectList()  { return &m_MapObjectList; };
	vector<CTile*>* GetMapTileVector() { return &m_vecTile; };
	CPlayer* GetPlayer() const { return m_player; };

private:
	map<OBJECT_TYPE, list<CObject*>> m_MapObjectList;
	map<OBJECT_TYPE, list<CObject*>>::iterator m_Objiter;
	CPlayer* m_player = nullptr;

	//TOOL
	vector<CTile*> m_vecTile;
};

