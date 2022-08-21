#pragma once
class CAnimation
{
public:
	CAnimation(SpriteInfo sprite,int framelimit,float framedelay, Vector2 Size, ANI_STATE state);
	CAnimation(SpriteInfo sprite, int framelimit, float framedelay, Vector2 Size, ANI_STATE state, Vector2 worldpos);
	~CAnimation();

public:
	void Update();
	void Update(Vector2 pos);
	void Render();
	void ResetDelay();

	ANI_STATE GetState() { return m_eAniState; };

private:
	int m_iCurFrame;
	int m_iFrameLimit;

	float m_fFrameDelay;
	float m_fCurDelay;

	Vector2 m_vecWorldpos;
	Vector2 m_vecScreenSize;

	SpriteInfo m_tSpriteinfo;

	Image* m_image;
	ANI_STATE m_eAniState;
};

