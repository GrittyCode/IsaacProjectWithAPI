#pragma once

class CFly : public CEnemy
{

public:
	virtual ~CFly() override;
public:
	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Release();
private:
	CFly(ObjectInfo objInfo, EnemyInfo enemyinfo);
	CFly();

	friend class CEnemyFactory;
};

