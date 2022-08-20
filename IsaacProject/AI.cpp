#include "stdafx.h"
#include "AI.h"

AI::AI()
	:m_pHost(nullptr),
	 m_currentState(nullptr)
{
}

AI::~AI()
{
}

void AI::Update()
{
	m_currentState->Update();
}
