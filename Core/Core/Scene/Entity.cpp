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


	template<typename T> void Entity::RemoveComponent()
	{
		if (HasComponent<T>())
			m_Scene->m_EntityRegistry.remove<T>(m_EntityHandle);
		else
			LOG_ERROR("Unable to remove component! Component not found!");
	}
	template<typename T> bool Entity::HasComponent()
	{
		return m_Scene->m_EntityRegistry.any_of<T>(m_EntityHandle);
	}
	template<typename T> T& Entity::GetComponent()
	{
		return m_Scene->m_EntityRegistry.get<T>(m_EntityHandle);
	}
	template<typename T> T& Entity::GetComponent_if()
	{
		if (HasComponent<T>())
			return m_Scene->m_EntityRegistry.get<T>(m_EntityHandle);
		else
		{
			LOG_ERROR("Unable to get component: Component do not exist");
			assert(true);
		}
	}
	template<typename T, typename... Args> T& Entity::AddComponent(Args&&... _args)
	{
		if(!HasComponent<T>())
			return m_Scene->m_EntityRegistry.emplace<T>(m_EntityHandle, std::forward<Args>(_args)...);
		LOG_ERROR("Cannot add a component type that already exist");
		assert(1);
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