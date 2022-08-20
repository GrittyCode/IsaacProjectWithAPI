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

};

