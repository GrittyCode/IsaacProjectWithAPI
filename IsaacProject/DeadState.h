#pragma once
class DeadState :
    public CState
{
public:
    DeadState();
    ~DeadState();

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
};

