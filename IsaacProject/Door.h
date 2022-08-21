#pragma once

struct DoorInfo
{
	DoorInfo(wstring sceneName, Vector2 Pos)
		:strSceneame(sceneName),
		 vecPlayerPos(Pos)
	{

	}
	wstring strSceneame;
	Vector2 vecPlayerPos;
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

};

