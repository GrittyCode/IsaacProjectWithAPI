#pragma once
class CObjectMgr
{
	SINGLETON(CObjectMgr)

public:
	BOOL SetObjectFromFile(ObjectInfo info);
	BOOL AddObject(CObject* object);
	BOOL AddTile(CTile* tile);
	void Init();
	void Update();
	void FixedUpdate();
	void LateUpdate();
	void Render(HDC hdc);
	void Release();

	//METHOD
	void CreateRandomItem();



	//SET
	void ConnectScene(map<OBJECT_TYPE, list<CObject*>>* temp);
	void SetPlayer(CPlayer* player);
	void ErasePlayer();
	//GET
	map<OBJECT_TYPE, list<CObject*>>* GetMapObjectList()  { return m_MapObjectList; };
	vector<CTile*>* GetMapTileVector() { return &m_vecTile; };
	CPlayer* GetPlayer() { return m_player; };





private:
	map<OBJECT_TYPE, list<CObject*>>* m_MapObjectList = nullptr;
	map<OBJECT_TYPE, list<CObject*>>::iterator m_Objiter;
	CPlayer* m_player = nullptr;
	//TOOL
	vector<CTile*> m_vecTile;
};

