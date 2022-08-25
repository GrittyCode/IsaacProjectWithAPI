#pragma once
class CBomb : public CItem
{
public:
    CBomb(ObjectInfo obj);
    virtual ~CBomb() {};
public:
    void Init();
    void Update();
    void FixedUpdate();
    void LateUpdate();
    void Render(HDC hdc);
    void Release();
    INT CheckCollisionState();

private:
    float m_fAniDelay;
    float m_fCurDelay;

    int m_iCurFrame;
    int m_iFramelimit;
};

