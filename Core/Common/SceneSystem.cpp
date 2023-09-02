#include "SceneSystem.h"


namespace OE1Core
{
	SceneSystem::SceneSystem()
	{

	}
	SceneSystem::~SceneSystem()
	{

	}
	Scene* SceneSystem::GetScene()
	{
		return SceneManager::GetActiveScene();
	}
	void SceneSystem::UpdateScene()
	{

	}
	Entity SceneSystem::GetEntityByID(uint32_t _id)
	{
		return Entity();
	}

	entt::registry& SceneSystem::GetSceneRegistry()
	{
		return SceneManager::GetActiveScene()->m_EntityRegistry;
	}

	///////////////////////////////////////////////////// ACTION FUNCTION

	Entity SceneSystem::CloneEntity(Entity _entity)
	{
		auto active_scene = SceneManager::GetActiveScene();
		Entity new_entity = active_scene->CreateEntity();


		return new_entity;
	}


	///////////////////////////////////////////////////// ENTITY CREATION FUNCTION

	Entity SceneSystem::CreateEmptyEntity()
	{
		auto active_scene = SceneManager::GetActiveScene();

		Entity new_entity = active_scene->CreateEntity();

		new_entity.AddComponent<Component::TransformComponent>(&new_entity);
		new_entity.AddComponent<Component::TagComponent>();

		return new_entity;
	}
	Entity SceneSystem::CreateCameraEntity()
	{


		return Entity();
	}



	/////////////////////////////////////////////////////	COMPONENT CREATION FUNCTIONS

	void SceneSystem::AddRigidbodyComponent(Entity _entity)
	{

	}
	void SceneSystem::AddMeshColliderComponent(Entity _entity)
	{

	}
	void SceneSystem::AddAudioComponent(Entity _entity)
	{

	}
	void SceneSystem::AddProjectileComponent(Entity _entity)
	{

	}
}