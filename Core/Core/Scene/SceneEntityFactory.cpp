#include "SceneEntityFactory.h"
#include "Entity.h"
#include "LogUI.h"


namespace OE1Core
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;

	SceneEntityFactory::SceneEntityFactory(Scene* _scene)
	{
		m_Scene = _scene;
	}
	SceneEntityFactory::~SceneEntityFactory()
	{

	}

	Entity SceneEntityFactory::Clone(Entity _src_entity)
	{
		Entity my_new_entity = m_Scene->CreateEntity();

		CloneTagComponent(_src_entity, my_new_entity);
		CloneTransformComponent(_src_entity, my_new_entity);
		CloneMeshComponent(_src_entity, my_new_entity);
		CloneBillboardComponent(_src_entity, my_new_entity);
		CloneCameraPackageComponent(_src_entity, my_new_entity);
		CloneBoundingVolume(_src_entity, my_new_entity);


		return my_new_entity;
	}
	bool SceneEntityFactory::Purge(Entity _entity)
	{
		if (!m_Scene->m_EntityRegistry.valid(_entity.GetHandle()))
			return false;

		// If the client request to remove camera component need to be carfully handeled
		if (!RemoveCameraPackageComponent(_entity))
			return false;

		Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
		
		if (transform.m_Parent)
			transform.m_Parent->GetComponent<Component::TransformComponent>().RemoveChild(_entity);

		while (!transform.IsLeaf())
			transform.m_Children.front()->GetComponent<Component::TransformComponent>().RemoveParent();

		RemoveBillboardComponent(_entity);
		RemoveMeshComponent(_entity);
		RemoveBoundingVolumeComponent(_entity);
		m_Scene->m_EntityRegistry.destroy(_entity.GetHandle());
		return true;
	}
	void SceneEntityFactory::RegisterActiveScene(Scene* _scene) { m_Scene = _scene; }
	Scene* SceneEntityFactory::GetScene() { return m_Scene; }

	Entity SceneEntityFactory::CreateRichMeshEntity(IVModel* _model_pkg, glm::vec3 _initial_pos)
	{
		Entity my_entity = m_Scene->CreateEntity();
		AddDefaultComponent(my_entity, _model_pkg->Name);

		//AddBoundingVolumeComponent(my_entity, _model_pkg);

		my_entity.GetComponent<Component::TagComponent>().SetType(EntityType::T_STATIC_MESH);
		my_entity.GetComponent<Component::TransformComponent>().m_Position = _initial_pos;

		// Create MeshComponent
		bool scene_has_rich_data = m_Scene->HasStaticMesh(_model_pkg->PackageID);
		StaticMesh* crt_static_mesh = nullptr;
		if (!scene_has_rich_data)
			crt_static_mesh = m_Scene->RegisterStaticMesh(_model_pkg);
		else
			crt_static_mesh = m_Scene->QueryStaticMesh(_model_pkg->PackageID);

		if (crt_static_mesh)
		{
			uint32_t mem_offset = RegisterInstance(crt_static_mesh, my_entity);
			CreateRichMeshComponent(_model_pkg, mem_offset, my_entity);
		}

		m_Scene->GetTurboOT()->Register(my_entity);
		
		return my_entity;
	}
	Entity SceneEntityFactory::CreateRichSkinnedMeshEntity(IVModel* _model_pkg, glm::vec3 _initial_pos)
	{
		Entity my_entity = m_Scene->CreateEntity();
		AddDefaultComponent(my_entity, _model_pkg->Name);

		//AddBoundingVolumeComponent(my_entity, _model_pkg);
		
		my_entity.GetComponent<Component::TagComponent>().SetType(EntityType::T_STATIC_MESH);
		my_entity.GetComponent<Component::TransformComponent>().m_Position = _initial_pos;

		// Create MeshComponent
		bool scene_has_rich_data = m_Scene->HasDynamicMesh(_model_pkg->PackageID);
		DynamicMesh* crt_dynamic_mesh = nullptr;

		if (!scene_has_rich_data)
			crt_dynamic_mesh = m_Scene->RegisterDynamicMesh(_model_pkg);
		else
			crt_dynamic_mesh = m_Scene->QueryDynamicMesh(_model_pkg->PackageID);

		if (crt_dynamic_mesh)
		{
			uint32_t mem_offset = crt_dynamic_mesh->AddInstance(&my_entity);// RegisterInstance(crt_dynamic_mesh, my_entity);
			CreateRichSkinnedMeshComponent(_model_pkg, mem_offset, my_entity);
			CreateAnimationComponent(crt_dynamic_mesh, mem_offset, my_entity);
		}

		m_Scene->GetTurboOT()->Register(my_entity);
		return my_entity;

	}
	Entity SceneEntityFactory::CreateDefaultCubeEntity()
	{
		return Entity();
	}
	Entity SceneEntityFactory::CreateDefaultPlaneEntity()
	{
		return Entity();
	}
	Entity SceneEntityFactory::CreateEmptyEntity(std::string _name)
	{
		return Entity();
	}
	Entity SceneEntityFactory::CreateSceneCamera(std::string _name)
	{
		Entity my_entity = m_Scene->CreateEntity();

		AddDefaultComponent(my_entity, _name);

		my_entity.GetComponent<Component::TagComponent>().SetType(EntityType::T_CAMERA);

		Component::TransformComponent& transform = my_entity.GetComponent<Component::TransformComponent>();
		transform.m_Position = glm::vec3(0.0f, 2.0f, 0.0f);
		transform.Update();

		Component::ViewportBillboardComponent& billboard = my_entity.AddComponent<Component::ViewportBillboardComponent>(m_Scene->GetBillboardIcon(ViewportIconBillboardType::CAMERA), (uint32_t)my_entity, ViewportIconBillboardType::CAMERA);
		billboard.Update(transform, m_Scene->m_MasterCamera->GetCamera()->m_View);


		// Create Component
		Component::TagComponent& tag = my_entity.GetComponent<Component::TagComponent>();
		CameraPackage* camera = m_Scene->GetCameraManager()->RegisterCamera(tag.m_Identifier, CAMERA_TYPE::FREE_LOOK);
		camera->PowerOn();
		camera->SetParentEntityID(my_entity);

		Component::CameraPackageComponent& _camera_pkg =  my_entity.AddComponent<Component::CameraPackageComponent>(camera, tag.m_Identifier);
		Component::FreeLookCameraControllerComponent& controller = my_entity.AddComponent<Component::FreeLookCameraControllerComponent>(m_Scene->GetCameraManager()->GetContextWindow());
		
		
		camera->SetCameraController(&controller);
		controller.SetCameraComponent(camera->GetCamera());

		// Register Inspector
		my_entity.GetComponent<Component::InspectorComponent>().SetCameraPackageComponent(
			&my_entity.GetComponent<Component::CameraPackageComponent>()
		);

		return my_entity;
	}
	Entity SceneEntityFactory::CreateFolderEntity(std::string _name)
	{
		Entity my_entity = m_Scene->CreateEntity();

		AddDefaultComponent(my_entity, _name);
		my_entity.GetComponent<Component::TagComponent>().SetType(EntityType::T_WRAPPER);
		my_entity.GetComponent<Component::TransformComponent>().m_Position = glm::vec3(0.0f);

		return my_entity;
	}






	void SceneEntityFactory::AddAudioComponent(Entity _entity)
	{

	}
	void SceneEntityFactory::AddMeshColliderComponent(Entity _entity)
	{

	}
	void SceneEntityFactory::AddRigidbodyComponent(Entity _entity)
	{

	}
	void SceneEntityFactory::AddProjectileComponent(Entity _entity)
	{

	}
	void SceneEntityFactory::AddThirdPersonCameraControllerComponent(Entity _entity)
	{
		if (_entity.HasComponent<Component::ThirdPersonCameraControllerComponent>())
		{
			LOG_ERROR(LogLayer::Pipe("[COMPONENT REGISTRY FAILED] :: Entity already have <ThirdPersonCameraControllerComponent>", OELog::WARNING));
			return;
		}

		// Query Tranform Component
		Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();

		
		 // Create Camera Controller
		 Component::ThirdPersonCameraControllerComponent& camera_controller = _entity.AddComponent<Component::ThirdPersonCameraControllerComponent>(m_Scene->GetCameraManager()->GetContextWindow(), &transform);

		 // Bind Controller and the Camera
		 /*_camera.GetCameraPackage()->SetCameraController(&camera_controller);
		 camera_controller.SetCameraComponent(_camera.GetCameraPackage()->GetCamera());*/


		 // Register inspector so we can twick it
		_entity.GetComponent<Component::InspectorComponent>().SetThirdPersonCameraControllerComponent(
			&_entity.GetComponent<Component::ThirdPersonCameraControllerComponent>()
		);
	}
	void SceneEntityFactory::AddThirdPersonCharacterControllerComponent(Entity _entity)
	{
		if (_entity.HasComponent<Component::ThirdPersonCharacterControllerComponent>())
		{
			LOG_ERROR(LogLayer::Pipe("[COMPONENT REGISTRY FAILED] :: Entity already have <ThirdPersonCharacterControllerComponent>", OELog::WARNING));
			return;
		}

		if (!_entity.HasComponent<Component::AnimationComponent>())
		{
			LOG_ERROR(LogLayer::Pipe("[COMPONENT REGISTRY FAILED] :: Entity need to have <AnimationComponent> to recieve <ThirdPersonCharacterControllerComponent>", OELog::WARNING));
			return;
		}

		// Query Animation Component
		Component::AnimationComponent& animation = _entity.GetComponent<Component::AnimationComponent>();

		// Query Transform Component
		Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
		

		// Create Component
		_entity.AddComponent<Component::ThirdPersonCharacterControllerComponent>(&transform, nullptr, animation.GetAnimationController());

		// Register Inspector
		_entity.GetComponent<Component::InspectorComponent>().SetThirdPersonCharacterControllerComponent(
			&_entity.GetComponent<Component::ThirdPersonCharacterControllerComponent>()
		);


	}
	void SceneEntityFactory::AddDefaultComponent(Entity& _entity, std::string _name)
	{
		_entity.AddComponent<Component::TagComponent>(CheckNameCollision(_name));
		_entity.GetComponent<Component::InspectorComponent>().SetTagComponent(&_entity.GetComponent<Component::TagComponent>());

		_entity.AddComponent<Component::TransformComponent>(&_entity);
		_entity.GetComponent<Component::InspectorComponent>().SetTransformComponent(&_entity.GetComponent<Component::TransformComponent>());
	}
	void SceneEntityFactory::AddBoundingVolumeComponent(Entity _entity, IVModel* _model_package)
	{
		if (_entity.HasComponent<Component::BoundingVolumeComponent>())
		{
			LOG_ERROR(LogLayer::Pipe("[COMPONENT REGISTRY FAILED] :: Entity already  have <BoundingVolumeComponent>", OELog::WARNING));
			return;
		}
		
		Component::TagComponent& _tag = _entity.GetComponent<Component::TagComponent>();


		// Does we have a shape for this entity already
		IVModel* _debug_shape = AssetManager::GetDebugMesh(_model_package->Name);
		
		// IF we don't generate and get a point to the data
		if (!_debug_shape)
		{
			AssetManager::RegisterDebugMesh(_model_package->Name, DAC::GeometryCreator::GetDebugShapeAABB(_model_package->Bound));
			_debug_shape = AssetManager::GetDebugMesh(_model_package->Name);
		}

		uint32_t __offset = 0;
		// Add to the scene so it can get rendered
		if (m_Scene->HasDebugMesh(_debug_shape->PackageID))
			__offset = m_Scene->QueryDebugMesh(_debug_shape->PackageID)->AddInstance(&_entity);
		else
			__offset = m_Scene->RegisterDebugMesh(_debug_shape)->AddInstance(&_entity);

		std::vector<GLuint> _instance_buffer;
		for (size_t i = 0; i < _debug_shape->SubMeshs.size(); i++)
			_instance_buffer.push_back(_debug_shape->SubMeshs[i].IBO);

		// Create Component so it can get controlled
		_entity.AddComponent<Component::BoundingVolumeComponent>(_debug_shape->PackageID, _instance_buffer, (uint32_t)_entity, (GLintptr)__offset, _model_package->Bound.Min, _model_package->Bound.Max);
		
	}







	//////////////// UTILITY HELPER FUNCTIONS

	uint32_t SceneEntityFactory::RegisterInstance(StaticMesh* _mesh, Entity& _entity)
	{
		return _mesh->AddInstance(&_entity);
	}
	uint32_t SceneEntityFactory::RegisterInstance(DynamicMesh* _mesh, Entity& _entity)
	{
		return _mesh->AddInstance(&_entity);
	}
	void SceneEntityFactory::CreateRichMeshComponent(IVModel* _mesh, uint32_t _offset, Entity& _entity)
	{
		std::vector<GLuint> geometry_buffer;
		std::vector<uint32_t> material_offsets;
		for (size_t i = 0; i < _mesh->SubMeshs.size(); i++)
		{
			geometry_buffer.push_back(_mesh->SubMeshs[i].IBO);
			material_offsets.push_back(_mesh->SubMeshs[i].MaterialID);
		}

		Component::CoreMeshArg _arg;

		_arg.PackageID				= _mesh->PackageID;
		_arg.InstanceID				= (uint32_t)_entity;
		_arg.Offset					= _offset;
		_arg.MaterialAccessIndices	= material_offsets;
		_arg.GeometryBuffer			= geometry_buffer;

		_entity.AddComponent<Component::MeshComponent>(_arg);
		_entity.GetComponent<Component::InspectorComponent>().SetMeshComponent(&_entity.GetComponent<Component::MeshComponent>());
	}
	void SceneEntityFactory::CreateRichSkinnedMeshComponent(IVModel* _mesh, uint32_t _offset, Entity& _entity)
	{
		std::vector<GLuint> geometry_buffer;
		std::vector<uint32_t> material_offsets;
		for (size_t i = 0; i < _mesh->SubMeshs.size(); i++)
		{
			geometry_buffer.push_back(_mesh->SubMeshs[i].IBO);
			material_offsets.push_back(_mesh->SubMeshs[i].MaterialID);
		}

		Component::CoreMeshArg _arg;

		_arg.PackageID				= _mesh->PackageID;
		_arg.InstanceID				= (uint32_t)_entity;
		_arg.Offset					= _offset;
		_arg.MaterialAccessIndices	= material_offsets;
		_arg.GeometryBuffer			= geometry_buffer;


		int __bone_count = (int)GeometryPacket::GeometryAssetPacketBuffer::GetSkinnedIVModelCustomData(_mesh->DataIdx)->BoneInfoMap.size();
		
		_entity.AddComponent<Component::SkinnedMeshComponent>(_arg, _offset, __bone_count);
		_entity.GetComponent<Component::InspectorComponent>().SetSkinnedMeshComponent(&_entity.GetComponent<Component::SkinnedMeshComponent>());
	}
	void SceneEntityFactory::CreateAnimationComponent(DynamicMesh* _dynamic_mesh, uint32_t _offset, Entity& _entity)
	{

		if (!_entity.HasComponent<Component::SkinnedMeshComponent>())
		{
			LOG_ERROR(LogLayer::Pipe("Failed to add animation component, add SkinnedMeshComponent before animation component!", OELog::CRITICAL));
			return;
		}

		
		_entity.AddComponent<Component::AnimationComponent>(
			nullptr, // No Animation by default
			uint32_t(_entity),
			MemoryBufferLocator()).SetSkinnedMeshComponentCallback(std::bind(&Component::SkinnedMeshComponent::SetArmatureBufferIndex, &_entity.GetComponent<Component::SkinnedMeshComponent>(), std::placeholders::_1));
		
		_entity.GetComponent<Component::InspectorComponent>().SetAnimationComponent(&_entity.GetComponent<Component::AnimationComponent>());
	}

	std::string SceneEntityFactory::CheckNameCollision(std::string _name)
	{
		while (NameExist(_name))
		{
			// If the last char is not ) it means this isthe first instance
			if (_name.back() != ')')
				_name += "(1)";
			else
			{
				// If the code reach here it means the name is modefied with (index)
				// so we need to extract this index and increament it
				size_t last_open_index = _name.find_last_of('(');
				size_t last_close_index = _name.find_last_of(')');

				size_t index_digit_count = last_close_index - last_open_index;
				std::string digit = _name.substr(last_open_index + 1, index_digit_count);
				_name.replace(last_open_index + 1, index_digit_count - 1, std::to_string(std::stoi(digit) + 1));
			}
		}

		return _name;
	}
	bool SceneEntityFactory::NameExist(std::string _name)
	{
		bool exist = false;
		m_Scene->m_EntityRegistry.each([&](auto _entt)
			{
				Entity _entity(_entt, m_Scene);

				if (_entity.HasComponent<Component::TagComponent>())
				{
					if(_entity.GetComponent<Component::TagComponent>().m_Identifier == _name)
					{
						exist = true;
						return;
					}
				}
				
			});

		return exist;
	}

	//////////////////////// Clone Util
	void SceneEntityFactory::CloneMeshComponent(Entity _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::MeshComponent>())
			return;

		Component::MeshComponent& mesh = _src.GetComponent<Component::MeshComponent>();

		// Get the static Mesh
		StaticMesh* static_mesh = nullptr;
		static_mesh = m_Scene->QueryStaticMesh(mesh.GetPackageID());
		if (!static_mesh)
		{
			LOG_ERROR("Error Cloning MeshComponent!");
			return;
		}

		
		uint32_t mem_offset = RegisterInstance(static_mesh, _dest);


		_dest.AddComponent<Component::MeshComponent>(mesh, (uint32_t)_dest, mem_offset);
		_dest.GetComponent<Component::InspectorComponent>().SetMeshComponent(&_dest.GetComponent<Component::MeshComponent>());
		//CreateRichMeshComponent(AssetManager::GetGeometry(mesh.GetPackageID()), mem_offset, _dest);

		m_Scene->GetTurboOT()->Register(_dest);

	}
	void SceneEntityFactory::CloneBoundingVolume(Entity& _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::BoundingVolumeComponent>() || _dest.HasComponent<Component::BoundingVolumeComponent>())
			return;

		Component::BoundingVolumeComponent& _bound = _src.GetComponent<Component::BoundingVolumeComponent>();

		uint32_t __offset = m_Scene->QueryDebugMesh(_bound.GetPackageID())->AddInstance(&_dest);

		_dest.AddComponent<Component::BoundingVolumeComponent>(_bound, (uint32_t)_dest, __offset);
	}
	void SceneEntityFactory::CloneTransformComponent(Entity _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::TransformComponent>())
			return;

		_dest.AddComponent<Component::TransformComponent>(&_dest);
		_dest.GetComponent<Component::InspectorComponent>().SetTransformComponent(&_dest.GetComponent<Component::TransformComponent>());

		Component::TransformComponent& src_transform = _src.GetComponent<Component::TransformComponent>();
		Component::TransformComponent& dest_transform = _dest.GetComponent<Component::TransformComponent>();

		dest_transform.Update();

		if (src_transform.m_Parent)
			src_transform.m_Parent->GetComponent<Component::TransformComponent>().AddChild(_dest);

		dest_transform.m_Position		= src_transform.m_Position;
		dest_transform.m_Euler			= src_transform.m_Euler;
		dest_transform.m_RotationFinal	= src_transform.m_RotationFinal;
		dest_transform.m_Quaternion		= src_transform.m_Quaternion;
		dest_transform.m_Scale			= src_transform.m_Scale;
	}
	void SceneEntityFactory::CloneTagComponent(Entity _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::TagComponent>())
			return;

		_dest.AddComponent<Component::TagComponent>(CheckNameCollision(
			_src.GetComponent<Component::TagComponent>().m_Identifier
		));
		_dest.GetComponent<Component::InspectorComponent>().SetTagComponent(&_dest.GetComponent<Component::TagComponent>());
		
		Component::TagComponent& src_tag = _src.GetComponent<Component::TagComponent>();
		Component::TagComponent& dest_tag = _dest.GetComponent<Component::TagComponent>();

		dest_tag.SetType(src_tag.GetType());
	}
	void SceneEntityFactory::CloneProjectileComponent(Entity _src, Entity _dest)
	{

	}
	void SceneEntityFactory::CloneAudioComponent(Entity _src, Entity _dest)
	{

	}
	void SceneEntityFactory::CloneAnimationComponent(Entity _src, Entity _dest)
	{

	}
	void SceneEntityFactory::CloneRigidBodyComponent(Entity _src, Entity _dest)
	{

	}
	void SceneEntityFactory::CloneMeshColliderComponent(Entity _src, Entity _dest)
	{

	}
	void SceneEntityFactory::CloneBillboardComponent(Entity _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::ViewportBillboardComponent>())
			return;

		Component::ViewportBillboardComponent& src_billboard = _src.GetComponent<Component::ViewportBillboardComponent>();
		_dest.AddComponent<Component::ViewportBillboardComponent>(src_billboard, (uint32_t)_dest);
	}
	void SceneEntityFactory::CloneCameraPackageComponent(Entity& _src, Entity _dest)
	{
		if (!_src.HasComponent<Component::CameraPackageComponent>())
			return;

		Component::CameraPackageComponent& _camera_pkg = _src.GetComponent<Component::CameraPackageComponent>();

		// Create Component
		Component::TagComponent& tag = _dest.GetComponent<Component::TagComponent>();
		CameraPackage* camera = m_Scene->GetCameraManager()->RegisterCamera(tag.m_Identifier, _camera_pkg.GetCameraPackage()->GetType());
		camera->PowerOn();
		camera->SetParentEntityID(_dest);
		_dest.AddComponent<Component::CameraPackageComponent>(camera, tag.m_Identifier);

		// Register Inspector
		_dest.GetComponent<Component::InspectorComponent>().SetCameraPackageComponent(
			&_dest.GetComponent<Component::CameraPackageComponent>()
		);

	}



	/////////// PURG

	void SceneEntityFactory::RemoveMeshComponent(Entity _entity)
	{
		if (!_entity.HasComponent<Component::MeshComponent>())
			return;
		Component::MeshComponent& mesh = _entity.GetComponent<Component::MeshComponent>();
		if (!m_Scene->HasStaticMesh(mesh.GetPackageID()))
			return;

		StaticMesh* static_mesh = m_Scene->QueryStaticMesh(mesh.GetPackageID());

		static_mesh->PurgeInstance(_entity, m_Scene);

		// This will remove it from render stack and the static mesh it take care of everything
		if (static_mesh->GetInstanceCount() == 0)
			m_Scene->PurgeStaticMesh(static_mesh->GetPackageID());
	}
	void SceneEntityFactory::RemoveBillboardComponent(Entity _entity)
	{
		if (!_entity.HasComponent<Component::ViewportBillboardComponent>())
			return;

		Component::ViewportBillboardComponent& BillboardComponent = _entity.GetComponent<Component::ViewportBillboardComponent>();
		ViewportBillboardIcon* Sprite = m_Scene->GetBillboardIcon(BillboardComponent.GetType());
		Sprite->PurgeInstance(_entity, m_Scene);
		
		if (Sprite->GetInstanceCount() <= 0)
			m_Scene->PurgeBillboardIcon(BillboardComponent.GetType());
	}
	bool SceneEntityFactory::RemoveCameraPackageComponent(Entity _entity)
	{
		if (!_entity.HasComponent<Component::CameraPackageComponent>())
			return true;

		Component::CameraPackageComponent& _camera = _entity.GetComponent<Component::CameraPackageComponent>();

		if (_camera.GetCameraPackage()->IsPilotMode() || _camera.GetCameraPackage()->IsPowerOn())
		{
			LOG_WARRNING(LogLayer::Pipe("Close viewport before purgeing the camera! PLEASE", OELog::WARNING));
			return false;
		}

		Component::TagComponent& tag = _entity.GetComponent<Component::TagComponent>();
		m_Scene->GetCameraManager()->PurgeCamera(tag.m_Identifier);

		return true;
	}
	bool SceneEntityFactory::RemoveBoundingVolumeComponent(Entity _entity)
	{
		if (!_entity.HasComponent<Component::BoundingVolumeComponent>())
			return false;

		Component::BoundingVolumeComponent& _volume = _entity.GetComponent<Component::BoundingVolumeComponent>();

		if (!m_Scene->HasDebugMesh(_volume.GetPackageID()))
			return false;

		m_Scene->QueryDebugMesh(_volume.GetPackageID())->PurgeInstance((uint32_t)_entity, m_Scene);

		if (m_Scene->QueryDebugMesh(_volume.GetPackageID())->GetInstanceCount() <= 0)
			m_Scene->PurgeDebugMesh(_volume.GetPackageID());

		_entity.RemoveComponent<Component::BoundingVolumeComponent>();
		return true;
	}


	uint64_t SceneEntityFactory::GetUniqueID()
	{
		return s_UniformDistribution(s_Engine);
	}


}