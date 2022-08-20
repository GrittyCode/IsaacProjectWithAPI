#pragma once

class CObject
{
public:
	CObject();
	CObject(ObjectInfo info);
	virtual ~CObject();
public:
	virtual void Init();
	virtual void Update() = 0;
	virtual void FixedUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual INT CheckCollisionState() =  0;
	bool AddComponent(CComponent* component);

	//Set
	void const SetObjState(OBJECT_STATE state) { m_ObjInfo.state = state; }

	//GET
	OBJECT_TYPE const GetObjType() { return m_ObjInfo.type; }
	OBJECT_STATE const GetObjState() { return  m_ObjInfo.state; }
	CTransform* GetTransform() const { return m_Transform; };
	BOOL const HasComponent(COMPONENT_TYPE type);
	CComponent* const GetComponent(COMPONENT_TYPE type);
	ObjectInfo* GetInfo()  { return &m_ObjInfo; }
	CBoxCollider2D* GetCollide() const { return m_collide; }

	//Render
	void ReverseDraw(int frame, ActAniInfo aniinfo, int offset_x, int offset_y, int Startoffset_x, int Startoffset_y);
	void Draw(int frame, ActAniInfo aniinfo, int offset_x, int offset_y, int Startoffset_x, int Startoffset_y);

protected:
	CTransform* m_Transform = nullptr;
	CSprite* m_sprite = nullptr;
	CBoxCollider2D* m_collide = nullptr;

	unordered_map<COMPONENT_TYPE, CComponent*> m_MapComponent;
	unordered_map<COMPONENT_TYPE, CComponent*>::iterator m_iter;
	//파일 저장 로드를 하기 위한 변수
	ObjectInfo m_ObjInfo;
};

