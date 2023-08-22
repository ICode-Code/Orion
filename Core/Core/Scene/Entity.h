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

		template<typename T> void RemoveComponent();
		template<typename T> bool HasComponent();
		template<typename T> T& GetComponent();
		template<typename T> T& GetComponent_if();
		template<typename T, typename... Args> T& AddComponent(Args&&... _args);

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
