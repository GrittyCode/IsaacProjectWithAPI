#include "stdafx.h"
#include "CKey.h"

CKey::CKey(ObjectInfo obj)
	:CObject(obj)
{
	
}

void CKey::Init()
{
}

void CKey::Update()
{
}

void CKey::FixedUpdate()
{
}

void CKey::LateUpdate()
{
}

void CKey::Render(HDC hdc)
{
}

void CKey::Release()
{
}

INT CKey::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{
		//Object�� ��� Player �κ��丮 â�� �߰�
	}


	return TRUE;
}
