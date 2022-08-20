#pragma once
class CSprite :
    public CComponent
{
public:
	CSprite(wstring path, INT orderLayer);
	virtual ~CSprite();
	virtual void Init() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Render(HDC hdc) override;

	Image* const GetSprite() { return m_sprite; }
	Image* const GetSFilpSprite() { return m_SpriteFileY; }

	void SetPath(wstring path);

private:
	wstring m_path;
	Image* m_sprite;
	Image* m_SpriteFileY;
	INT m_orderLayer;
};

