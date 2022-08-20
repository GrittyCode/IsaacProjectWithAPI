#pragma once

struct MoverInfo
{
	float fSpeed = 0;
	Vector2 vecMoveDiretion = Vector2(0,0);
	Vector2 vecAttackDiretion = Vector2(0, 0);
	vector<ActAniInfo> vecActAniState;
	ANISTATE eAniAttackState = ANISTATE::IDLE;
	ANISTATE eAniMoveState = ANISTATE::IDLE;
};


class CMover : public CObject
{
public:
	CMover();
	CMover(ObjectInfo objinfo, MoverInfo moverinfo);
	virtual ~CMover();

public:
	//BASIC FRAME
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Move() = 0;
	virtual INT CheckCollisionState() = 0;

	//GET
	Vector2 GetoMoveDir() const { return m_MoverInfo.vecMoveDiretion; }
	float GetSpeed() const { return m_MoverInfo.fSpeed; }
protected:
	MoverInfo m_MoverInfo = MoverInfo{};
};