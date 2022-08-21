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

	CreateEffect(new CAnimation(SpriteInfoTag(GetAI()->GetHost()->GetInfo()->wpath, Vector2(0, 64), Vector2(64, 64),false,Vector2(0,0)),
		4,
		0.08f,
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
