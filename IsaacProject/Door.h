#pragma once


struct DoorInfo
{
	wstring strSceneame;
	Vector2 vecPlayerPos;
};


class CDoor
{
public:
	void ChangeSceneFromDoor();
	CDoor();
	~CDoor();
private:
	DoorInfo m_doorInfo;
};

