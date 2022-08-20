#pragma once
class CCameraMgr
{
	SINGLETONE(CCameraMgr)
public:
	void Init() {};
	void Update();
	void FixedUpdate();
	void Render();
};

