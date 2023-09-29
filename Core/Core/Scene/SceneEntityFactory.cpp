#include "SceneEntityFactory.h"
#include "Entity.h"


namespace OE1Core
{
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


		return my_new_entity;
	}
	bool SceneEntityFactory::Purge(Entity _entity)
	{
		if (!m_Scene->m_EntityRegistry.valid(_entity.GetHandle()))
			return false;
		Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
		
		if (transform.m_Parent)
			transform.m_Parent->GetComponent<Component::TransformComponent>().RemoveChild(_entity);

		while (!transform.IsLeaf())
			transform.m_Children.front()->GetComponent<Component::TransformComponent>().RemoveParent();


		RemoveMeshComponent(_entity);
		m_Scene->m_EntityRegistry.destroy(_entity.GetHandle());
		return true;
	}
	void SceneEntityFactory::RegisterActiveScene(Scene* _scene) { m_Scene = _scene; }
	Scene* SceneEntityFactory::GetScene() { return m_Scene; }

	Entity SceneEntityFactory::CreateRichMeshEntity(ModelPkg* _model_pkg, glm::vec3 _initial_pos)
	{
		Entity my_entity = m_Scene->CreateEntity();
		AddDefaultComponent(my_entity, _model_pkg->Name);
		my_entity.GetComponent<Component::TagComponent>().SetType(s_TypeRegistry[EntityType::T_STATIC_MESH]);
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






	void SceneEntityFactory::AddAudioComponent(Entity& _entity)
	{

	}
	void SceneEntityFactory::AddMeshColliderComponent(Entity& _entity)
	{

	}
	void SceneEntityFactory::AddRigidbodyComponent(Entity& _entity)
	{

	}
	void SceneEntityFactory::AddProjectileComponent(Entity& _entity)
	{

	}

	void SceneEntityFactory::AddDefaultComponent(Entity& _entity, std::string _name)
	{
		_entity.AddComponent<Component::TagComponent>(CheckNameCollision(_name));
		_entity.GetComponent<Component::InspectorComponent>().SetTagComponent(&_entity.GetComponent<Component::TagComponent>());

		_entity.AddComponent<Component::TransformComponent>(&_entity);
		_entity.GetComponent<Component::InspectorComponent>().SetTransformComponent(&_entity.GetComponent<Component::TransformComponent>());
	}







	//////////////// UTILITY HELPER FUNCTIONS

	uint32_t SceneEntityFactory::RegisterInstance(StaticMesh* _mesh, Entity& _entity)
	{
		return _mesh->AddIntance(&_entity);
	}
	void SceneEntityFactory::CreateRichMeshComponent(ModelPkg* _mesh, uint32_t _offset, Entity& _entity)
	{
		std::vector<GLuint> geometry_buffer;
		std::vector<uint32_t> material_offsets;
		for (size_t i = 0; i < _mesh->MeshList.size(); i++)
		{
			geometry_buffer.push_back(_mesh->MeshList[i].IBO);
			material_offsets.push_back(_mesh->MeshList[i].MaterialID);
		}
		_entity.AddComponent<Component::MeshComponent>(
			_mesh->PackageID,
			(uint32_t)_entity,
			_offset,
			geometry_buffer,
			material_offsets
		);
		_entity.GetComponent<Component::InspectorComponent>().SetMeshComponent(&_entity.GetComponent<Component::MeshComponent>());
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
		CreateRichMeshComponent(AssetManager::GetGeometry(mesh.GetPackageID()), mem_offset, _dest);

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

		dest_tag.SetType(src_tag.m_Type);
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



	/////////// PURG

	void SceneEntityFactory::RemoveMeshComponent(Entity _entity)
	{
		if (!_entity.HasComponent<Component::MeshComponent>())
			return;
		Component::MeshComponent& mesh = _entity.GetComponent<Component::MeshComponent>();
		if (!m_Scene->HasStaticMesh(mesh.GetPackageID()))
			return;

		StaticMesh* static_mesh = m_Scene->QueryStaticMesh(mesh.GetPackageID());

		static_mesh->RemoveInstance(_entity, m_Scene);

		// This will remove it from render stack and the static mesh it take care of everything
		if (static_mesh->GetInstanceCount() == 0)
			m_Scene->PurgeStaticMesh(static_mesh->GetPackageID());
	}
}