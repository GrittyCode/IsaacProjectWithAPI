#pragma once


//UPDATE -> ����ڿ��� ������ �Է¹޾� �����ӵ��� ó����
//FIXEDUPDATE -> �Է¹��� ������ ���� �Ͼ �ϵ��� ó����
//LATEUPDATE -> ��� ���� ó�� �� ���Ŀ�, ī�޶� ���� ������(���� RENDER)
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

