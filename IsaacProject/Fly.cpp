#include "stdafx.h"
#include "Fly.h"

CFly::CFly(ObjectInfo objInfo, EnemyInfo enemyinfo)
	:CEnemy(objInfo, enemyinfo)
{
}

CFly::~CFly()
{
}

void CFly::Init()
{
	//ai���� ���丮 �������� �Ѿ����
	m_pAI = new AI(this);
	m_pAI->AddState(new CIdleState);
	m_pAI->AddState(new CTraceState);
	m_pAI->AddState(new DeadState);
	m_pAI->ChangeState(AI_STATE::IDLE);

	CObject::Init();
}

void CFly::Update()
{
	m_fCurDelay += DELTA;

	//�ִϸ��̼� ����������
	if (m_fCurDelay > 0.02f)
	{
		++m_iFrame;
		m_fCurDelay = 0;

		if (m_iFrame == 2)
		{
			m_iFrame = 0;
		}
	}

	m_pAI->Update();
}

void CFly::FixedUpdate()
{
}

void CFly::Render(HDC hdc)
{
	CImageMgr::GetInstance()->GetGraphics()->DrawImage(
		m_sprite->GetSprite(),
		Rect((UINT)m_Transform->GetPositionX() - 32, (UINT)m_Transform->GetPositionY() - 32, 64, 64),
		32 + (m_iFrame * 32), 32, 32, 32,
		UnitPixel);
}

void CFly::Release()
{
}

INT CFly::CheckCollisionState()
{
	return 0;
}
