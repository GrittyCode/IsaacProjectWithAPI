#include "stdafx.h"
#include "Huntstate.h"

CHuntstate::CHuntstate()
	:CState(AI_STATE::HUNT)
{

}

CHuntstate::~CHuntstate()
{
}

void CHuntstate::Enter()
{
	GetAI()->GetHost()->SetAniState(ANI_STATE::HUNT);
}

void CHuntstate::Exit()
{

}

void CHuntstate::Update()
{
	GetAI()->GetHost()->SetHp(2);

	if (GetAI()->GetHost()->GetHp() > 0)
	{
		GetAI()->ChangeState(AI_STATE::TRACE);
	}
	else
	{
		GetAI()->ChangeState(AI_STATE::DEAD);
	}
}
