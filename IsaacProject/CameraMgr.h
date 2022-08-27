#pragma once
class CCameraMgr
{
	SINGLETON(CCameraMgr)
public:
	void Init() {};
	void Update();
	void FixedUpdate();
	void Render();
};

