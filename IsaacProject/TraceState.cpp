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
	GetAI()->GetHost()->SetAniState(ANI_STATE::MOVE);
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
		//case EVENT_TYPE::AI_STATE_CHANGE:
		//{
		//	//lParam OBJECT Address
		//	//Object를 Dead상태로 변경
		//	//삭제예정 오브젝트들을 모아둔다.
		//	CObject* pDeadObj = (CObject*)eve.lParam;
		//	pDeadObj->SetDead();
		//	m_vecDead.push_back(pDeadObj);
		//}

	if (Host->GetCollide()->GetFlag() & (UINT)COLLISION_FLAG::PLAYER_TEAR)
	{
		GetAI()->ChangeState(AI_STATE::HUNT);
	}
}
