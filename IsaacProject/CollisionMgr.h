#pragma once


//UPDATE -> 사용자에게 정보를 입력받아 움직임등을 처리함
//FIXEDUPDATE -> 입력받은 정보로 인해 일어난 일들을 처리함
//LATEUPDATE -> 모든 일이 처리 된 이후에, 카메라 등을 랜더함(현재 RENDER)
class CCollisionMgr
{
	SINGLETONE(CCollisionMgr)
public:
	void Init();
	void CheckCollision(OBJECT_TYPE target, OBJECT_TYPE des);
	void AddCollider(OBJECT_TYPE type, CBoxCollider2D* box);
	void DeleateCollider(CBoxCollider2D* target);
	void ChanageScene(map<OBJECT_TYPE, list<CObject*>>* mapObjList);
private:
	BOOL IsCollision(CBoxCollider2D* target, CBoxCollider2D* des);
	map<OBJECT_TYPE, list<CBoxCollider2D*>> m_mapBoxlist;
	map<OBJECT_TYPE, list<CBoxCollider2D*>>::iterator m_iter;
};

