#include "stdafx.h"
#include "TraceState.h"

CTraceState::CTraceState()
	:CState(AI_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}

void CTraceState::Update()
{
	CEnemy* Host = GetAI()->GetHost();

	Vector2 PlayerPos = CObjectMgr::GetInstance()->GetPlayer()->GetTransform()->GetPosition();
	Vector2 MoveDirection = PlayerPos - Host->GetTransform()->GetPosition();

	MoveDirection.Normalize();
	
	Host->GetTransform()->SetPosition(Vector2(Host->GetTransform()->GetPosition().x + (MoveDirection.x * DELTA * Host->GetEnemyInfo().fSpeed),
	Host->GetTransform()->GetPosition().y + (MoveDirection.y * DELTA * Host->GetEnemyInfo().fSpeed)));

	/*if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
		PushMover(m_collide->GetTarget(OBJECT_TYPE::PLAYER)->GetOwnerObj());*/


	/*if ()
	{
		GetAI()->ChangeState(AI_STATE::DEAD);
	}*/
}
