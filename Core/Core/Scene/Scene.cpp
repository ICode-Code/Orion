#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"
#include "../InfiniteVision/IVMasterRenderer.h"
#include "../InfiniteVision/RenderStack/RenderStack.h"
#include "LogUI.h"


namespace OE1Core
{
	Scene::Scene(SDL_Window* _window)
		: m_Window{ _window }
	{
		m_CameraManager = new SceneCameraManager(_window);
		m_MasterSceneCamera = m_CameraManager->GetMasterCamera();


		m_Grid = new Grid();
		m_MyRenderer = new Renderer::IVMasterRenderer(m_Window, this);
		m_RenderStack = new Renderer::IVRenderStack();

		m_SceneActiveSelection = new ActiveEntity();
		m_SceneActiveSelection->SetOnFlushCallback(
			new std::function<void(std::vector<Entity>&)>(
				std::bind(&Scene::OnSelectionFlushOperation, this, std::placeholders::_1)
			)
		);

		m_RenderMode = RenderMode::LIT;
		m_SceneRay = new Ray(m_MasterSceneCamera->Camera);
		m_TurboOctree = new DS::TurboOT();
		m_QuickCull = new SceneQuickCull();

		m_InputController = new InputController(this);
		m_RenderController = new RenderController(this);
		m_GenesisController = new GenesisController(this);


		// Init Icons
		RegisterBillboardIcon(ViewportIconBillboardType::CAMERA, "Camera");
		RegisterBillboardIcon(ViewportIconBillboardType::POINT_LIGHT, "PointLight");
		RegisterBillboardIcon(ViewportIconBillboardType::DIRECTIONAL_LIGHT, "PointLight");
		RegisterBillboardIcon(ViewportIconBillboardType::SPOT_LIGHT, "PointLight");
		//m_SceneBillboardIcon.insert(std::make_pair(ViewportIconBillboardType::POINT_LIGHT, new ViewportBillboardIcon(AssetManager::GetInternalTexture("PointLight"))));
		//m_SceneBillboardIcon.insert(std::make_pair(ViewportIconBillboardType::DIRECTIONAL_LIGHT, new ViewportBillboardIcon(AssetManager::GetInternalTexture("Sun"))));

	}

	Scene::~Scene()
	{
		delete m_QuickCull;
		delete m_Grid;
		delete m_MyRenderer;
		delete m_RenderStack;
		delete m_SceneActiveSelection;
		delete m_SceneRay;
		delete m_TurboOctree;
		delete m_CameraManager;
		delete m_InputController;
		delete m_RenderController;
		delete m_GenesisController;

		for (auto iter : m_StaticMeshRegistry)
			delete iter.second;

		for (auto iter : m_DebugMeshRegistry)
			delete iter.second;

		for (auto iter : m_DynamicMeshRegistry)
			delete iter.second;

		for (auto iter : m_SceneBillboardIcon)
			delete iter.second;


		if (m_ActivePlayerEntity)
			delete m_ActivePlayerEntity;
	}
	void Scene::InputUpdate(float _dt)
	{
		m_LastDelta = _dt;

		HotComponentUpdate();
		UpdateAnimationComponents();
		UpdateCulledBuffer(m_MasterSceneCamera->Camera);

		m_InputController->QuickInputUpdateControllerComponent(_dt);
		m_InputController->QuickInputUpdateMasterCamera(_dt);

		if (m_UseActiveThreadForAnimation)
			UpdateAnimationTransform();
	}
	void Scene::BufferUpdate(float _dt)
	{
		m_InputController->ControllerComponentBufferUpdate(_dt);
		m_InputController->MasterCameraBufferUpdate(_dt);
	}
	void Scene::InitRender()
	{
		m_RenderController->RenderMasterCameraScene();
		m_RenderController->RenderClientCameraScene();
		m_RenderController->FlushRenderCommand();
	}
	void Scene::HotComponentUpdate()
	{
		auto BillboatdCompView = m_EntityRegistry.view<Component::ViewportBillboardComponent>();
		for (auto ent : BillboatdCompView)
		{
			Component::ViewportBillboardComponent& billboard = BillboatdCompView.get<Component::ViewportBillboardComponent>(ent);
			Component::TransformComponent& transform = m_EntityRegistry.get<Component::TransformComponent>(ent);

			// Update the billboard
			billboard.Update(transform, m_MasterSceneCamera->Camera->m_View);
		}
	}
	
	void Scene::UpdateCulledBuffer()
	{

		if (m_UtilizeSpecialDataStructureForFrusumCull)
		{
			UpdateInistanceGLBuffer(m_TurboOctree->m_CulledBuffer);
		}
		else
		{
			UpdateInistanceGLBuffer(m_QuickCull->GetCulledBuffer(m_CameraManager->GetCameraList()));
		}
	}
	void Scene::UpdateCulledBuffer(Component::CameraComponent* _camera)
	{
		UpdateInistanceGLBuffer(m_QuickCull->GetCulledBuffer(_camera));
	}
	void Scene::ResetPhysics()
	{

	}
	void Scene::OnEvent(OECore::IEvent& e)
	{
		m_InputController->OnEventMasterCamera(e);
		
		if (e.Handled())
			return;

		m_InputController->OnEventControllerComponent(e);
	}
	void Scene::UpdateAnimationComponents()
	{
		auto animation_com_view = m_EntityRegistry.view<Component::AnimationComponent>();
		
		for (auto ent : animation_com_view)
		{
			Component::AnimationComponent& Animation = animation_com_view.get<Component::AnimationComponent>(ent);
	
			// Update the Animation Buffer
			Animation.UpdateBuffer();
		}
	}
	void Scene::UpdateAnimationTransform()
	{
		SkeletonAnimator::UpdateAnimations(m_LastDelta);
	}
	void Scene::UpdateInistanceGLBuffer(std::unordered_map<uint32_t, std::vector<DS::OTEntDiscriptor>>& _buffer)
	{
		int _item_count = 0;
		// update buffer
		for (auto iter = _buffer.begin(); iter != _buffer.end(); iter++)
		{
			size_t _insta_count = iter->second.size();

			for (size_t i = 0; i < _insta_count; i++)
			{
				iter->second[i].UpdateInstanceCount((int)_insta_count);
				iter->second[i].UpdateOffset((int)i * StaticMeshInstancePkgSize);
				iter->second[i].UpdateBuffer();
				_item_count++;
			}
		}
	}
	void Scene::SetProtagonist(Component::ActorComponent* _actor) {  m_Protagonist = _actor; }
	Component::ActorComponent* Scene::GetProtagonist() { return m_Protagonist; }

	Memory::EnvironmentVariablesBuffer& Scene::GetEnvVar() { return m_EnvVarBuffer;}
	void Scene::UpdateEnvVar()
	{
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::ENVIRONMENT_VARIABLES)->Update(Memory::s_EnvironmentVariablesBufferSize, 0, &m_EnvVarBuffer);
	}
	
}