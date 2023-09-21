#include "Scene.h"
#include "Entity.h"
#include "../InfiniteVision/IVMasterRenderer.h"
#include "../InfiniteVision/RenderStack/RenderStack.h"

namespace OE1Core
{
	Scene::Scene(SDL_Window* _window)
		: m_Window{_window}, m_CameraPkg{ _window }
	{
		m_Grid = new Grid();
		m_RenderStack = new Renderer::IVRenderStack();
	}
	Scene::~Scene()
	{
		delete m_Grid;
		delete m_RenderStack;
	}


	Entity Scene::CreateEntity()
	{
		Entity my_entity(m_EntityRegistry.create(), this);
		my_entity.AddComponent<Component::InspectorComponent>();
		return my_entity;
	}
	Entity Scene::GetEntity(entt::entity _id)
	{
		if (!m_EntityRegistry.valid(_id))
		{
			LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity(_id, this);
	}
	Entity Scene::GetEntity(uint32_t _id)
	{
		if (!m_EntityRegistry.valid((entt::entity)_id))
		{
			LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity((entt::entity)_id, this);
	}
	void Scene::Update(int _width, int _height)
	{
		m_RendererUpdateCallback(_width, _height);
		m_CameraPkg.GetCamera()->SetResolution(glm::vec2((float)_width, (float)_height));
	}
	void Scene::Update(float dt)
	{
		m_CameraPkg.Update(dt);
	}
	void Scene::ResetPhysics()
	{

	}
	bool Scene::HasStaticMesh(uint32_t _package_id)
	{
		return (m_StaticMeshRegistry.find(_package_id) != m_StaticMeshRegistry.end());
	}
	StaticMesh* Scene::RegisterStaticMesh(ModelPkg* _model_pkg)
	{
		if (HasStaticMesh(_model_pkg->PackageID))
		{
			LOG_ERROR("Static Mesh already exist! failed to register model package: {0}", _model_pkg->Name);
			return nullptr;
		}

		m_StaticMeshRegistry.insert(std::make_pair(_model_pkg->PackageID, new StaticMesh(_model_pkg)));

		Renderer::IVMasterRenderer::PushToRenderStack(m_StaticMeshRegistry[_model_pkg->PackageID], this);

		return m_StaticMeshRegistry[_model_pkg->PackageID];
	}
	StaticMesh* Scene::QueryStaticMesh(uint32_t _package_id)
	{
		if (!HasStaticMesh(_package_id))
		{
			LOG_ERROR("Failed to query static mesh, registry not found, Package ID: {0}", _package_id);
			return nullptr;
		}

		return m_StaticMeshRegistry[_package_id];
	}
	void Scene::OnEvent(OECore::IEvent& e)
	{
		m_CameraPkg.OnEvent(e);
	}
	void Scene::ResetScene()
	{
		ResetPhysics();
	}


}