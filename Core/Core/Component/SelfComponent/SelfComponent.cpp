#include "SelfComponent.h"
#include "../Core/Scene/Scene.h"
#include "../Core/Scene/Entity.h"


namespace OE1Core
{
	namespace Component
	{
		SelfComponent::SelfComponent(Entity* _entity, Scene* _scene)
		{
			m_Entity = _entity;
			m_Scene = _scene;
			m_EntityID = (uint32_t)(m_Entity->GetHandle());
		}
		SelfComponent::~SelfComponent()
		{

		}
		Entity* SelfComponent::GetEntity() { return m_Entity; }
		Scene* SelfComponent::GetScene() { return m_Scene; }
		uint32_t SelfComponent::GetEntityID() { return m_EntityID; }
	}
}