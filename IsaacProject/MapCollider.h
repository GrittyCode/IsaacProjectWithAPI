#pragma once
#include "Object.h"

class CMapCollider :
    public CObject
{
public:
    CMapCollider();
	CMapCollider(ObjectInfo objinfo);
    ~CMapCollider();

public:
	virtual void Init();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
	virtual INT CheckCollisionState();

	void PushMover(CObject* obj);
};

