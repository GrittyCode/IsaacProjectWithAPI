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
	Vector2 EnemyPos = GetAI()->GetHost()->GetTransform()->GetPosition();

	CreateEffect(new CAnimation(SpriteInfoTag(L"../Resources/Sprites/Enemy/fly_effect.png", Vector2(0, 0), Vector2(64, 64),false,Vector2(0,0)),
	    11,
		0.05f,
		Vector2(32, 32),
		ANI_STATE::DEAD,EnemyPos));

	DeleteObject(GetAI()->GetHost());
}

void DeadState::Exit()
{
}

void DeadState::Update()
{
}
