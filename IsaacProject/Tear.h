#pragma once
class CTear : public CMover
{
public:
	CTear(Vector2 playerdiretiony, Vector2 worldpos, Vector2 attackdirection, float playerspeed,bool m_Left);
	virtual ~CTear() override;

	virtual void Init();
	virtual void Update();
	virtual void Render(HDC hdc);
	virtual void Move();
	virtual INT CheckCollisionState();
	void FireEyeSet(bool left, Vector2 attackdirection);

private:
	float m_fDistance;

	bool m_bGravity;
	bool m_bSound;

	int m_iCurPrame;
	float m_fCurDeley;
	Vector2 m_vecFireEye;
};
