#include "stdafx.h"
#include "Object.h"

CObject::CObject():
	m_bAllive(true)
{
	m_Transform = nullptr; 
	m_sprite = nullptr;
}

CObject::CObject(ObjectInfo info)
	:	m_ObjInfo(info),
		m_bAllive(true)
{
	m_Transform = nullptr;
	m_sprite = nullptr;
}

CObject::~CObject()
{

}

void CObject::Init()
{
	//저장된 위치 값에 transfrom 할당
	AddComponent(new CTransform(Vector2(m_ObjInfo.vecWorldPos.x, m_ObjInfo.vecWorldPos.y), Vector2(m_ObjInfo.vecSize.x, m_ObjInfo.vecSize.y)));
	m_Transform = dynamic_cast<CTransform*>(GetComponent(COMPONENT_TYPE::TRANSFORM));

	AddComponent(new CSprite(m_ObjInfo.wpath, 10));
	m_sprite = dynamic_cast<CSprite*>(GetComponent(COMPONENT_TYPE::SPRITE));

}

void CObject::FixedUpdate()
{
	CheckCollisionState();
}

void CObject::Render(HDC hdc)
{
	m_iter = m_MapComponent.begin();

	while (m_iter != m_MapComponent.end())
	{
		(*m_iter).second->Render(hdc);
		m_iter++;
	}
}

void CObject::Release()
{
	for (size_t i = 0; i < (int)COMPONENT_TYPE::COMPONENT_TYPE_END; ++i)
	{
		m_iter = m_MapComponent.find((COMPONENT_TYPE)i);

		//찾는 컴포넌트가 있다면
		if (m_iter != m_MapComponent.end())
		{
			if ((COMPONENT_TYPE)i == COMPONENT_TYPE::BOXCOLLIDE2D)
			{
				CCollisionMgr::GetInstance()->DeleateCollider(dynamic_cast<CBoxCollider2D*>((*m_iter).second));
			}

			(*m_iter).second->Release();
			delete (*m_iter).second;
			(*m_iter).second = nullptr;
		}
	}
	m_MapComponent.clear();
}

BOOL CObject::AddComponent(CComponent* component)
{
	//컴포넌트가 존재하지 않는다면
	if (m_MapComponent.find(component->GetComponentType()) == m_MapComponent.end())
	{
		component->Init();
		m_MapComponent.insert({ component->GetComponentType() , component });

		//충돌체를 준다면
		if (component->GetComponentType() == COMPONENT_TYPE::BOXCOLLIDE2D)
			CCollisionMgr::GetInstance()->AddCollider(m_ObjInfo.type,dynamic_cast<CBoxCollider2D*>(component));		

		return TRUE;
	}

	//이미 컴포넌트가 존재한다면
	delete component;
	return FALSE;
}

BOOL const CObject::HasComponent(COMPONENT_TYPE type)
{
	m_iter = m_MapComponent.find(type);

	if (m_MapComponent.find(type) != m_MapComponent.end())
	{
		return TRUE;
	}

	return FALSE;
}


CComponent* const CObject::GetComponent(COMPONENT_TYPE type)
{
	m_iter = m_MapComponent.find(type);

	if (m_MapComponent.find(type) != m_MapComponent.end())
	{
		return (*m_iter).second;
	}

	return nullptr;
}



