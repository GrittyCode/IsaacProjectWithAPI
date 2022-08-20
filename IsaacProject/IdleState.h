#pragma once

class CIdleState :
    public CState
{
public:
    CIdleState();
    ~CIdleState();

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;

private:
    float m_fIdleDelay = 0;
    float m_fStayDelay = 1.0f;
};

