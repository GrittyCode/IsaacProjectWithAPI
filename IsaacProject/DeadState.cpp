#include "stdafx.h"
#include "DeadState.h"


DeadState::DeadState()
	:CState(AI_STATE::DEAD)
{
}

DeadState::~DeadState()
{
}

void DeadState::Enter()
{
}

void DeadState::Exit()
{
}

void DeadState::Update()
{
	DeleteObject(GetAI()->GetHost());
}
