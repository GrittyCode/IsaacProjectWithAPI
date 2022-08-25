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
		//Object의 경우 Player 인벤토리 창에 추가
	}


	return TRUE;
}
