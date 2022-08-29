#pragma once
class CBomb : public CObject
{
public:
    CBomb(ObjectInfo obj);
    virtual ~CBomb() {};
public:
    void Init();
    void Update();
    void LateUpdate();
    void Render(HDC hdc);
    void Explode();
    INT CheckCollisionState();

    bool GetExplosion() { return m_bExplosion; };

private:
    float m_fAniDelay;
    float m_fCurDelay;

    int m_iCurFrame;
    int m_iFramelimit;

    bool m_bExplosion = false;
    bool m_bPlayerPush = false;
};

