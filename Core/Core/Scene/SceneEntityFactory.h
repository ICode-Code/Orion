#ifndef OE1_SCENE_ENTITY_FACTORY_H_
#define OE1_SCENE_ENTITY_FACTORY_H_

#include "Scene.h"
#include "../Component/IComponent.h"
#include "EntityType.h"
#include "../../Core/CoreAnimation/AnimationManager/AnimationManager.h"
#include "../AssetManager/DynamicAssetCreator/DynamicAssetCreator.h"
#include <random>
namespace OE1Core
{
	class SceneEntityFactory
	{
	public:
		SceneEntityFactory(Scene* _scene = nullptr);
		~SceneEntityFactory();

		// IF same anem detected it will add (index)
		static std::string CheckNameCollision(std::string _name);

		static void RegisterActiveScene(Scene* _scene);
		static Scene* GetScene();

		// Entity
		static Entity CreateRichSkinnedMeshEntity(IVModel* _model_package, glm::vec3 _initial_pos = glm::vec3(0.0f));
		static Entity CreateRichMeshEntity(IVModel* _model_pkg, glm::vec3 _initial_pos = glm::vec3(0.0f));
		static Entity CreateDefaultCubeEntity();
		static Entity CreateDefaultPlaneEntity();
		static Entity CreateEmptyEntity(std::string _name);
		static Entity CreateFolderEntity(std::string _name);
		static Entity CreateSceneCamera(std::string _name = "Scene Camera");


		// Component
		static void AddAudioComponent(Entity _entity);
		static void AddMeshColliderComponent(Entity _entity);
		static void AddRigidbodyComponent(Entity _entity);
		static void AddProjectileComponent(Entity _entity);
		static void AddThirdPersonCameraControllerComponent(Entity _entity);
		static void AddThirdPersonCharacterControllerComponent(Entity _entity);
		static void AddBoundingVolumeComponent(Entity _entity, IVModel* _model_package);

		// This dude create Mesh component in simple word will tie the static mesh and mesh component
		static void CreateRichMeshComponent(IVModel* _mesh, uint32_t _offset, Entity& _entity);
		static void CreateRichSkinnedMeshComponent(IVModel* _mesh, uint32_t _offset, Entity& _entity);
		static void CreateAnimationComponent(DynamicMesh* _dynamic_mesh, uint32_t _offset, Entity& _entity);



		// Operation
		// return cloned entity
		static Entity Clone(Entity _src_entity);

		static bool Purge(Entity _entity);


		/// <summary>
		/// This always reurn unique number
		/// </summary>
		/// <returns></returns>
		static uint64_t GetUniqueID();

	protected:
		inline static Scene* m_Scene = nullptr;


	protected:
		static void AddDefaultComponent(Entity& _entity, std::string _name);
		// This function will register new instance and return the offset in buffer
		static uint32_t RegisterInstance(StaticMesh* _mesh, Entity& _entity);
		static uint32_t RegisterInstance(DynamicMesh* _mesh, Entity& _entity);
		

	protected: // Util
		static bool NameExist(std::string _name);

	protected: // Clone Util
		static void CloneMeshComponent(Entity _src, Entity _dest);
		static void CloneTransformComponent(Entity _src, Entity _dest);
		static void CloneTagComponent(Entity _src, Entity _dest);
		static void CloneProjectileComponent(Entity _src, Entity _dest);
		static void CloneAudioComponent(Entity _src, Entity _dest);
		static void CloneAnimationComponent(Entity _src, Entity _dest);
		static void CloneRigidBodyComponent(Entity _src, Entity _dest);
		static void CloneMeshColliderComponent(Entity _src, Entity _dest);
		static void CloneBillboardComponent(Entity _src, Entity _dest);
		static void CloneCameraPackageComponent(Entity& _src, Entity _dest);
		static void CloneBoundingVolume(Entity& _src, Entity _dest);


	public: // Purge Util/ Some component need more that just like remove
		static void RemoveMeshComponent(Entity _entity);
		static void RemoveBillboardComponent(Entity _entity);
		static bool RemoveCameraPackageComponent(Entity _entity);
		static bool RemoveBoundingVolumeComponent(Entity _entity);
	};
}

#endif // !OE1_SCENE_ENTITY_FACTORY_H_
