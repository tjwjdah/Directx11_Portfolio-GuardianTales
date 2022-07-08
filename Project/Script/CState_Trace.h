#pragma once
#include "CState.h"
class CState_Trace :
    public CState
{
private:
    float m_fTraceRange;

public:
    void SetTraceRange(float _Range) { m_fTraceRange = _Range; }
private:
    virtual void update();
    virtual void awake();
    virtual void Exit();
};

