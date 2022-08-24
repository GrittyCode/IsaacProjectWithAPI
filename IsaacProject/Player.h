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
	bool bHurtBlending;
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
	//Get
	PLAYER_STATE GetPlayerState() { return m_PlayerInfo.ePlayerState; }

	//Set
	void SetPlayerState(PLAYER_STATE state) { m_PlayerInfo.ePlayerState = state; }

	//act
	virtual INT CheckCollisionState() override;
	virtual void Move() override;
	void Attack();
private:
	PlayerInfo m_PlayerInfo;
};