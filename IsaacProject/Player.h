#pragma once

struct PlayerInfo
{
	int iCurFrame;
	bool bAttack;
	bool bAttackON;
	bool bLeft;
	float fAttackSpeed;
	float fFrameStay;
	float fAttackDelay;
	float fCurDelay;
	float fCurSpeed;
	float fAcceleration;
	PLAYER_STATE ePlayerState;
};

class CPlayer : public CMover
{
public:
	CPlayer(ObjectInfo objinfo, MoverInfo moverInfo);
	virtual ~CPlayer() override;
public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	//Render
	virtual void Render(HDC hdc) override;
	void MoveRender(HDC hdc);
	void AttackRender(HDC hdc);
	//Get
	PLAYER_STATE GetPlayerState() { return m_PlayerInfo.ePlayerState; }

	//Set
	void SetPlayerState(PLAYER_STATE state) { m_PlayerInfo.ePlayerState = state; }

	//act
	virtual INT CheckCollisionState() override;
	virtual void Move() override;
	void Attack();

	//Release
	virtual void Release() override
	{
		CObject::Release();
	}

private:
	PlayerInfo m_PlayerInfo;
};