#include "Entity.h"


namespace OE1Core
{
	Entity::Entity(entt::entity _entity, Scene* _scene)
	{
		m_EntityHandle = _entity;
		m_Scene = _scene;
	}
	Entity::~Entity()
	{

	}
	void Entity::Update()
	{

	}
	bool Entity::IsFunctional()
	{
		return m_Scene != nullptr;
	}
	uint64_t Entity::GetUUID()
	{
		return 1;
	}
	Scene* Entity::GetScene()
	{
		return m_Scene;
	}
	entt::entity Entity::GetHandle()
	{
		return m_EntityHandle;
	}
}