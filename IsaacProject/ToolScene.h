#pragma once

class CToolScene : public CScene
{
public:
	CToolScene();
	~CToolScene();

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(HDC hdc) override;

private:
	RECT m_rcTool;
};