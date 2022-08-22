#pragma once


struct DoorInfo
{
	DoorInfo(wstring sceneName, Vector2 Pos, DIRECTION adir)
		:strSceneame(sceneName),
		 vecPlayerPos(Pos),
		 dir(adir)
	{

	}
	wstring strSceneame;
	Vector2 vecPlayerPos;
	DIRECTION dir;
};


class CDoor : public CObject
{
public:
	void Init();
	void Update();
	void FixedUpdate();
	void Render(HDC hdc);
public:
	void ChangeSceneFromDoor();
	virtual INT CheckCollisionState() override;
	CDoor(ObjectInfo objInfo, DoorInfo doorInfo);
	~CDoor();

private:
	DoorInfo m_doorInfo;

	bool m_bOpen = false;

	float m_fDoorDelay = 0.2f;
	float m_fCurDelay = 0.0f;

	int m_iFramelimit = 4;
	int m_iCurFrame = 0;
};

