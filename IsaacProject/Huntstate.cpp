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
	//GetAI()->GetHost()->GetCollide()->GetTarget(OBJECT_TYPE::PLAYER_TEAR)->GetOwnerObj()
}
