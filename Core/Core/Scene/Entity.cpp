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
		Component::TransformComponent& transform = GetComponent<Component::TransformComponent>();
		glm::mat4 transfrom_mat = transform.GetWorldTransform();
		if (HasComponent<Component::MeshComponent>())
			GetComponent<Component::MeshComponent>().Update(transfrom_mat);
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