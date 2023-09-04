#ifndef OE1_SCENE_SYSTEM_H_
#define OE1_SCENE_SYSTEM_H_

#include "../Core/Component/IComponent.h"
#include "Interface/SceneInterface.h"

namespace OE1Core
{
	/// <summary>
	/// It's where you manage the creation, modification, and deletion of entities,
	/// components, and other scene-related data.
	//  The CoreSystem has a direct relationship with the scene data.
	/// </summary>
	class SceneSystem : public SceneInterface
	{
	public:
		SceneSystem();
		~SceneSystem();

		void UpdateScene() override;
		Scene* GetScene() override;
		Entity GetEntityByID(uint32_t _id) override;
		entt::registry& GetSceneRegistry() override;
		virtual Grid* GetSceneGrid() override;

		// Actions
		Entity CloneEntity(Entity _entity);

		// Entity Creation
		Entity CreateEmptyEntity();
		Entity CreateCameraEntity();

		// Component Creation
		void AddRigidbodyComponent(Entity _entity);
		void AddMeshColliderComponent(Entity _entity);
		void AddAudioComponent(Entity _entity);
		void AddProjectileComponent(Entity _entity);
	};
}

#endif // !OE1_SCENE_SYSTEM_H_
