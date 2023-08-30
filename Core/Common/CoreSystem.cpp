#include "CoreSystem.h"


namespace OE1Core
{
	CoreSystem::CoreSystem()
	{

	}
	CoreSystem::~CoreSystem()
	{

	}
	Scene* CoreSystem::GetScene()
	{
		return SceneManager::GetActiveScene();
	}
	void CoreSystem::UpdateScene()
	{

	}
	Entity CoreSystem::GetEntityByID(uint32_t _id)
	{
		return Entity();
	}

	entt::registry& CoreSystem::GetSceneRegistry()
	{
		return SceneManager::GetActiveScene()->m_EntityRegistry;
	}

	///////////////////////////////////////////////////// ACTION FUNCTION

	Entity CoreSystem::CloneEntity(Entity _entity)
	{
		auto active_scene = SceneManager::GetActiveScene();
		Entity new_entity = active_scene->CreateEntity();


		return new_entity;
	}


	///////////////////////////////////////////////////// ENTITY CREATION FUNCTION

	Entity CoreSystem::CreateEmptyEntity()
	{
		auto active_scene = SceneManager::GetActiveScene();

		Entity new_entity = active_scene->CreateEntity();

		new_entity.AddComponent<Component::TransformComponent>(&new_entity);
		new_entity.AddComponent<Component::TagComponent>();

		return new_entity;
	}
	Entity CoreSystem::CreateCameraEntity()
	{


		return Entity();
	}

	

	/////////////////////////////////////////////////////	COMPONENT CREATION FUNCTIONS

	void CoreSystem::AddRigidbodyComponent(Entity _entity)
	{
		
	}
	void CoreSystem::AddMeshColliderComponent(Entity _entity)
	{

	}
	void CoreSystem::AddAudioComponent(Entity _entity)
	{

	}
	void CoreSystem::AddProjectileComponent(Entity _entity)
	{

	}
}