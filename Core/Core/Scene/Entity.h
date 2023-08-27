#ifndef OE1_ENTITY_H_
#define OE1_ENTITY_H_

#include "Scene.h"
#include <Log.h>

namespace OE1Core
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity _entity, Scene* _scene);
		~Entity();

		template<typename T> void RemoveComponent()
		{
			if (HasComponent<T>())
				m_Scene->m_EntityRegistry.remove<T>(m_EntityHandle);
			else
				LOG_ERROR("Unable to remove component! Component not found!");
		}
		template<typename T> bool HasComponent()
		{
			return m_Scene->m_EntityRegistry.any_of<T>(m_EntityHandle);
		}
		template<typename T> T& GetComponent()
		{
			return m_Scene->m_EntityRegistry.get<T>(m_EntityHandle);
		}
		template<typename T> T& GetComponent_if()
		{
			if (HasComponent<T>())
				return m_Scene->m_EntityRegistry.get<T>(m_EntityHandle);
			else
			{
				LOG_ERROR("Unable to get component: Component do not exist");
				assert(true);
			}
		}
		template<typename T, typename... Args> T& AddComponent(Args&&... _args)
		{
			if (!HasComponent<T>())
				return m_Scene->m_EntityRegistry.emplace<T>(m_EntityHandle, std::forward<Args>(_args)...);
			LOG_ERROR("Cannot add a component type that already exist");
			assert(1);
		}

		void Update();
		bool IsFunctional();
		uint64_t GetUUID();
		Scene* GetScene();
		entt::entity GetHandle();
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		bool operator==(const Entity& other) const { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
		bool operator!=(const Entity& other) const { return !(*this == other); }


	protected:
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};
}

#endif // !OE1_ENTITY_H_
