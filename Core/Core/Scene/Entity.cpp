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
		
		transform.Update();

		UpdateTransformBuffer(transform.QueryWorldTransform());
		
	}
	void Entity::UpdateTransformBuffer()
	{
		Component::TransformComponent& transform = GetComponent<Component::TransformComponent>();
		UpdateTransformBuffer(transform);
	}
	void Entity::UpdateTransformBuffer(glm::mat4& _transform)
	{
		if (HasComponent<Component::MeshComponent>())
			GetComponent<Component::MeshComponent>().Update(_transform);

	/*	if(HasComponent<Component::CameraPackageComponent>())
			GetComponent<Component::CameraPackageComponent>().Update(&GetComponent<Component::TransformComponent>());*/
	}
	bool Entity::IsFunctional()
	{
		return m_Scene != nullptr;
	}
	uint64_t Entity::GetUUID()
	{
		return GetComponent<Component::TagComponent>().m_UID;
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