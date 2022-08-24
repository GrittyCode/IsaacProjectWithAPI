#pragma once

class CObject
{
public:
	CObject();
	CObject(ObjectInfo info);
	virtual ~CObject();
public:
	//LIFE CYCLE
	virtual void Init();
	virtual void Update() = 0;
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual INT CheckCollisionState() =  0;


	void AddAniState(CAnimation* anistate);
	BOOL AddComponent(CComponent* component);
	BOOL const HasComponent(COMPONENT_TYPE type);
	BOOL const IsDead() const { return !m_bAllive; }

	//Set
	void const SetObjState(OBJECT_STATE state) { m_ObjInfo.state = state; }
	void  SetName(const wstring& strName) { m_strName = strName; }
	void SetAniState(const ANI_STATE anistate) { m_AniState = anistate; }


	//GET
	OBJECT_TYPE const GetObjType() { return m_ObjInfo.type; }
	OBJECT_STATE const GetObjState() { return  m_ObjInfo.state; }
	CTransform* GetTransform() const { return m_Transform; };
	CComponent* const GetComponent(COMPONENT_TYPE type);
	ObjectInfo* GetInfo()  { return &m_ObjInfo; }
	CBoxCollider2D* GetCollide() const { return m_collide; }
	wstring GetName() const { return m_strName; }

	//Render
	void ReverseDraw(int frame, SpriteInfoTag aniinfo, int offset_x, int offset_y, int Startoffset_x, int Startoffset_y);
	void Draw(int frame, SpriteInfoTag aniinfo, int offset_x, int offset_y, int Startoffset_x, int Startoffset_y);



protected:
	CTransform* m_Transform = nullptr;
	CSprite* m_sprite = nullptr;
	CBoxCollider2D* m_collide = nullptr;

	wstring m_strName;


	ObjectInfo m_ObjInfo;
	ANI_STATE m_AniState;
	map<ANI_STATE, CAnimation*> m_mapAniState;
	map<ANI_STATE, CAnimation*>::iterator m_Aniiter;
	unordered_map<COMPONENT_TYPE, CComponent*> m_MapComponent;
	unordered_map<COMPONENT_TYPE, CComponent*>::iterator m_iter;

private:
	BOOL m_bAllive = TRUE;
	void SetDead() { m_bAllive = FALSE; }
	friend class CEventMgr;
};

