#pragma once

class CHuntstate :
    public CState
{
public:
    CHuntstate();
    ~CHuntstate();

public:
    virtual void Enter();
    virtual void Exit();
    virtual void Update();
};

