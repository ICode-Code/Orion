#ifndef OE1_CORE_SYSTEM_H_
#define OE1_CORE_SYSTEM_H_

#include "SceneInterface.h"
#include "../Core/Scene/SceneManager.h"
#include "../Core/Component/IComponent.h"

namespace OE1Core
{


	/// <summary>
	/// It's where you manage the creation, modification, and deletion of entities,
	/// components, and other scene-related data.
	//  The CoreSystem has a direct relationship with the scene data.
	/// </summary>
	class CoreSystem : public SceneInterface
	{
	public:
		CoreSystem();
		~CoreSystem();

		void UpdateScene() override;
		Scene* GetScene() override;
		Entity GetEntityByID(uint32_t _id) override;
		entt::registry& GetSceneRegistry() override;

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

#endif // !OE1_CORE_SYSTEM_H_
