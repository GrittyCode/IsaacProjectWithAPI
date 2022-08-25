#include "stdafx.h"
#include "Item.h"



//item type에 따라 플레이어에게 주는 객체가 달라진다.
INT CItem::CheckCollisionState()
{
	if (m_collide->GetFlag() & (UINT)COLLISION_FLAG::PLAYER)
	{
		CPlayer* m_player = dynamic_cast<CPlayer*>(m_collide->GetTargetObjForType(OBJECT_TYPE::PLAYER));

		if (m_player != NULL)
		{
			m_player->PickItem()
		}
	}

	return 0;
}
