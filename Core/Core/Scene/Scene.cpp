#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"
#include "../InfiniteVision/IVMasterRenderer.h"
#include "../InfiniteVision/RenderStack/RenderStack.h"


namespace OE1Core
{
	Scene::Scene(SDL_Window* _window)
		: m_Window{_window}
	{
		m_CameraManager = new SceneCameraManager(_window);
		m_MasterCamera = m_CameraManager->GetCamera("MasterCamera");
		m_CameraManager->EngagePilotMode("MasterCamera");

		m_MasterCamera->PowerOn();

		m_Grid = new Grid();
		m_MyRenderer = new Renderer::IVMasterRenderer(m_Window, this);
		m_RenderStack = new Renderer::IVRenderStack();
		m_SceneActiveSelection = new ActiveEntity();
		m_RenderMode = RenderMode::LIT;
		m_SceneRay = new Ray(m_MasterCamera);

		// Init Icons
		//m_SceneBillboardIcon.insert(std::make_pair(ViewportIconBillboardType::POINT_LIGHT, new ViewportBillboardIcon(AssetManager::GetInternalTexture("PointLight"))));
		//m_SceneBillboardIcon.insert(std::make_pair(ViewportIconBillboardType::DIRECTIONAL_LIGHT, new ViewportBillboardIcon(AssetManager::GetInternalTexture("Sun"))));
		
	}
	Scene::~Scene()
	{
		delete m_Grid;
		delete m_MyRenderer;
		delete m_RenderStack;
		delete m_SceneActiveSelection;
		delete m_SceneRay;

		for (auto iter : m_StaticMeshRegistry)
			delete iter.second;

		for (auto iter : m_DynamicMeshRegistry)
			delete iter.second;

		for (auto iter : m_SceneBillboardIcon)
			delete iter.second;

		delete m_CameraManager;
	}

	bool Scene::PurgeStaticMesh(uint32_t _package_id)
	{
		if (m_StaticMeshRegistry.find(_package_id) != m_StaticMeshRegistry.end())
		{
			m_MyRenderer->PurgeFromRenderStack(m_StaticMeshRegistry[_package_id]);
			m_StaticMeshRegistry.erase(_package_id);
			return true;
		}

		return false;
	}

	bool  Scene::PurgeDynamicMesh(uint32_t _package_id)
	{
		return false;
	}
	DynamicMesh* Scene::QueryDynamicMesh(uint32_t _package_id)
	{
		if (!HasDynamicMesh(_package_id))
		{
			LOG_ERROR("Failed to query DYNAMIC mesh, registry not found, Package ID: {0}", _package_id);
			return nullptr;
		}

		return m_DynamicMeshRegistry[_package_id];
	}
	DynamicMesh* Scene::RegisterDynamicMesh(IVModel* _model_pkg)
	{
		return nullptr;
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
	Entity Scene::GetEntity(uint32_t _id, bool _suppress_warning)
	{
		if (!m_EntityRegistry.valid((entt::entity)_id))
		{
			if(!_suppress_warning)
				LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity((entt::entity)_id, this);
	}
	void Scene::Update(int _width, int _height)
	{
		m_MyRenderer->Update(_width, _height);
		m_MasterCamera->Update(_width, _height);
		
	}
	void Scene::Update(float dt)
	{
		UpdateAllSceneCameraTransforms(dt);
		HotComponentUpdate();
	}
	void Scene::HotComponentUpdate()
	{
		auto BillboatdCompView = m_EntityRegistry.view<Component::ViewportBillboardComponent>();
		for (auto ent : BillboatdCompView)
		{
			Component::ViewportBillboardComponent& billboard = BillboatdCompView.get<Component::ViewportBillboardComponent>(ent);
			Component::TransformComponent& transform = m_EntityRegistry.get<Component::TransformComponent>(ent);

			// Update the billboard
			billboard.Update(transform, m_MasterCamera->GetCamera()->m_View);
		}
	}
	void Scene::UpdateAllSceneCameraTransforms(float _dt)
	{
		auto& CameraColl = m_CameraManager->GetCameraList();
		for (auto cam = CameraColl.begin(); cam != CameraColl.end(); cam++)
		{
			if (!cam->second.Camera->IsPowerOn())
				continue;

			cam->second.Camera->Update(_dt);
			Memory::UniformBlockManager::UseBuffer(
				Memory::UniformBufferID::SCENE_TRANSFORM)->Update(
					Memory::s_SceneTransformBufferSize, cam->second.Offset * Memory::s_SceneTransformBufferSize, &cam->second.Camera->GetSceneTransform());
		}
	}
	void Scene::ResetPhysics()
	{

	}
	bool Scene::HasStaticMesh(uint32_t _package_id)
	{
		return (m_StaticMeshRegistry.find(_package_id) != m_StaticMeshRegistry.end());
	}
	bool Scene::HasDynamicMesh(uint32_t _package_id)
	{
		return (m_DynamicMeshRegistry.find(_package_id) != m_DynamicMeshRegistry.end());
	}


	ActiveEntity* Scene::GetActiveEntity() { return m_SceneActiveSelection; }
	StaticMesh* Scene::RegisterStaticMesh(IVModel* _model_pkg)
	{
		if (HasStaticMesh(_model_pkg->PackageID))
		{
			LOG_ERROR("Static Mesh already exist! failed to register model package: {0}", _model_pkg->Name);
			return nullptr;
		}

		m_StaticMeshRegistry.insert(std::make_pair(_model_pkg->PackageID, new StaticMesh(_model_pkg)));

		m_MyRenderer->PushToRenderStack(m_StaticMeshRegistry[_model_pkg->PackageID]);

		return m_StaticMeshRegistry[_model_pkg->PackageID];
	}
	ViewportBillboardIcon* Scene::GetBillboardIcon(ViewportIconBillboardType _type)
	{
		if (m_SceneBillboardIcon.find(_type) == m_SceneBillboardIcon.end())
			return nullptr;

		return m_SceneBillboardIcon[_type];
	}
	bool Scene::HasBillboardType(ViewportIconBillboardType _type)
	{
		return m_SceneBillboardIcon.find(_type) != m_SceneBillboardIcon.end();
	}
	void Scene::RegisterBillboardIcon(ViewportIconBillboardType _type, std::string _texture_name)
	{
		if (m_SceneBillboardIcon.find(_type) != m_SceneBillboardIcon.end())
			return; // Already Exist

		m_SceneBillboardIcon.insert(std::make_pair(_type, new ViewportBillboardIcon(AssetManager::GetInternalTexture(_texture_name))));
	}
	bool Scene::PurgeBillboardIcon(ViewportIconBillboardType _type)
	{
		if (!HasBillboardType(_type))
			return false;

		m_SceneBillboardIcon.erase(_type);
		return true;
	}
	RenderMode& Scene::GetRenderMode()
	{
		return m_RenderMode;
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
		auto& CameraColl = m_CameraManager->GetCameraList();
		for (auto cam = CameraColl.begin(); cam != CameraColl.end(); cam++)
		{
			if (cam->second.Camera->IsPowerOn() && cam->second.Camera->IsPilotMode())
				cam->second.Camera->OnEvent(e);
		}
	}
	Ray* Scene::GetRay() { return m_SceneRay; }
	void Scene::ResetScene()
	{
		ResetPhysics();
	}
	SceneCameraManager* Scene::GetCameraManager() const
	{
		return m_CameraManager;
	}
	void Scene::Render()
	{
		m_MyRenderer->MasterPass(m_CameraManager->GetCameraList());
	}
	Renderer::IVMasterRenderer* Scene::GetRenderer()
	{
		return m_MyRenderer;
	}


}