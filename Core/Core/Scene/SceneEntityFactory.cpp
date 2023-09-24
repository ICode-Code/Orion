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

	void SceneEntityFactory::RegisterActiveScene(Scene* _scene) { m_Scene = _scene; }
	Scene* SceneEntityFactory::GetScene() { return m_Scene; }

	Entity SceneEntityFactory::CreateRichMeshEntity(ModelPkg* _model_pkg, glm::vec3 _initial_pos)
	{
		Entity my_entity = m_Scene->CreateEntity();
		AddDefaultComponent(my_entity, _model_pkg->Name);
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
		_entity.AddComponent<Component::TagComponent>(_name);
		_entity.GetComponent<Component::InspectorComponent>().SetTagComponent(&_entity.GetComponent<Component::TagComponent>());

		_entity.AddComponent<Component::TransformComponent>();
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
}