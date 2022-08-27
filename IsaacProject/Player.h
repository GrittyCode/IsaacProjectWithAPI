#pragma once

struct PlayerInfo
{
	int iCurFrame;
	bool bAttack;
	bool bAttackON;
	bool bLeft;
	bool bHurtBlending;
	PLAYER_STATE ePlayerState;
	float fFrameStay;
	float fCurDelay;
	float fCurSpeed;
	float fAcceleration;
	
	
	//stat
	int iHP;
	float fDmg;
	float fAttackSpeed;
	float fAttackDelay;
};




class CPlayer : public CMover
{
public:
	CPlayer(ObjectInfo objinfo, MoverInfo moverInfo);
	virtual ~CPlayer() override;
public:
	virtual void Init() override;
	virtual void Update() override;
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
	void PickUpItem(ITEM_TYPE);

private:
	PlayerInfo m_PlayerInfo;
	map<ITEM_TYPE, int> m_mapInventory;
};