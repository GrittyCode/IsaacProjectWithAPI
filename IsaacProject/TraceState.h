#pragma once

class CTraceState :
    public CState
{
public:
    CTraceState();
    ~CTraceState();

    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Update() override;
};

