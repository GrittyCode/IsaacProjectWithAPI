#include "stdafx.h"
#include "Item.h"



//item type�� ���� �÷��̾�� �ִ� ��ü�� �޶�����.
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
