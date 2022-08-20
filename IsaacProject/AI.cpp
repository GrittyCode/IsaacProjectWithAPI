#include "stdafx.h"
#include "AI.h"

AI::AI(CEnemy* host)
	:m_pHost(host)
{
}

AI::~AI()
{
}

void AI::Update()
{
	m_currentState->Update();
}

void AI::AddState(CState* state)
{
	if (state == nullptr)
	{
		return;
	}

	CState* Temp = GetState(state->GetType());

	if (Temp == nullptr)
	{
		state->SetAI(this);

		m_MapState.insert({ state->GetType() ,state });
	}
}

void AI::ChangeState(AI_STATE state)
{
	if (m_currentState != nullptr)
	{
		m_currentState->Exit();
	}

	m_currentState = m_MapState.find(state)->second;

	m_currentState->Enter();
}

CState* AI::GetState(AI_STATE state)
{
	map<AI_STATE, CState*>::iterator Iter = m_MapState.find(state);

	if (Iter == m_MapState.end())
	{
		return nullptr;
	}

	return Iter->second;
}
