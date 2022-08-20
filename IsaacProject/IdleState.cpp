#include "stdafx.h"
#include "IdleState.h"

class  CPlayer;


CIdleState::CIdleState():
	CState(AI_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::Enter()
{
	GetAI()->GetHost()->SetAniState(ANI_STATE::IDLE);
}

void CIdleState::Exit()
{
	m_fIdleDelay = 0;
}

void CIdleState::Update()
{
	if (m_fIdleDelay < m_fStayDelay)
	{
		m_fIdleDelay += DELTA;
	}

	if (m_fStayDelay < m_fIdleDelay)
	{
		GetAI()->ChangeState(AI_STATE::TRACE);
	}
}
