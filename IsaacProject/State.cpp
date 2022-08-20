#include "stdafx.h"
#include "State.h"

CState::CState(AI_STATE type)
	:m_type(type),
	 m_pAI(nullptr)
{
}

CState::~CState()
{
}
