#pragma once

class CFly : public CEnemy
{
public:
	CFly(ObjectInfo objInfo, EnemyInfo enemyinfo);
	~CFly();

public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
};

