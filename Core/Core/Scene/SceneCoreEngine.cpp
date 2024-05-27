#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"
#include "../InfiniteVision/IVMasterRenderer.h"
#include "../InfiniteVision/RenderStack/RenderStack.h"
#include "LogUI.h"

namespace OE1Core
{
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
			if (!_suppress_warning)
				LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity((entt::entity)_id, this);
	}

	bool Scene::ShouldUseRenderThreadForAnimationUpdate() { return m_UseActiveThreadForAnimation; };
	void Scene::SetActivePlayerEntity(Entity _entity)
	{

		// make sure this entity is valid to be a player

		bool _has_mesh = _entity.HasComponent<Component::MeshComponent>() || _entity.HasComponent<Component::SkinnedMeshComponent>();

		if (!_has_mesh)
		{
			LogLayer::Pipe("Entity need to have a <RenderableMeshComponent>  to be player!", OELog::CRITICAL);
			return;
		}

		if (!_entity.HasComponent<Component::ThirdPersonCharacterControllerComponent>())
		{
			LogLayer::Pipe("Entity need to have <CharacterControllerComponent> to be player!", OELog::CRITICAL);
			return;
		}

		if (!_entity.GetComponent<Component::ThirdPersonCharacterControllerComponent>().GetCameraComponent())
		{
			LogLayer::Pipe("No attached camera to <CharacterControllerComponent>! No Active Camera!", OELog::CRITICAL);
			return;
		}

		if (!_entity.HasComponent<Component::HumanControlledPlayerComponent>())
			_entity.AddComponent<Component::HumanControlledPlayerComponent>();


		if (m_ActivePlayerEntity)
		{
			if (m_ActivePlayerEntity->GetHandle() != _entity.GetHandle())
			{
				delete m_ActivePlayerEntity;
				m_ActivePlayerEntity = new Entity(_entity.GetHandle(), this);
			}
		}
		else {
			m_ActivePlayerEntity = new Entity(_entity.GetHandle(), this);
		}
	}

	Entity* Scene::GetActivePlayerEntity() { return m_ActivePlayerEntity; }



	// Debug Mesh
	bool Scene::PurgeDebugMesh(uint32_t _package_id)
	{
		if (!HasDebugMesh(_package_id))
			return false;

		delete m_DebugMeshRegistry[_package_id];
		m_DebugMeshRegistry.erase(_package_id);

		return true;
	}
	DebugMesh* Scene::QueryDebugMesh(uint32_t _package_id)
	{
		if (HasDebugMesh(_package_id))
			return m_DebugMeshRegistry[_package_id];

		LOG_ERROR("Requested <DebugMesh> not found!, Package ID: {0}", _package_id);
		return nullptr;
	}
	DebugMesh* Scene::RegisterDebugMesh(IVModel* _model_pkg)
	{
		if (HasDebugMesh(_model_pkg->PackageID))
		{
			LOG_ERROR("Debug Mesh already exist! failed to register Debug Shape: {0}", _model_pkg->Name);
			return nullptr;
		}

		m_DebugMeshRegistry.insert(std::make_pair(_model_pkg->PackageID, new DebugMesh(_model_pkg)));

		return m_DebugMeshRegistry[_model_pkg->PackageID];
	}
	bool Scene::HasDebugMesh(uint32_t _package_id)
	{
		return m_DebugMeshRegistry.find(_package_id) != m_DebugMeshRegistry.end();
	}
	void Scene::OnSelectionFlushOperation(std::vector<Entity>& _entity)
	{
		if (m_UtilizeSpecialDataStructureForFrusumCull)
		{
			for (size_t i = 0; i < _entity.size(); i++)
				m_TurboOctree->Update(_entity[i]);
		}
		else
		{
			// Perform Local cull update
			for (size_t i = 0; i < _entity.size(); i++)
			{
				if (IsParsableIntoOTEntDiscriptor(_entity[i]))
				{
					m_QuickCull->Update(ParseIntoOTEntDiscriptor(_entity[i]));
				}
			}
		}


	}
	void Scene::RegisterLoadedEntity(Entity _entity)
	{
		if (!IsParsableIntoOTEntDiscriptor(_entity))
		{
			LOG_ERROR("Invalid entity to process for culling");
			return;
		}

		DS::OTEntDiscriptor __discriptor = ParseIntoOTEntDiscriptor(_entity);

		if (m_UtilizeSpecialDataStructureForFrusumCull)
			m_TurboOctree->Register(__discriptor);
		else
		{
			m_QuickCull->Register(__discriptor);
		}
	}
	void Scene::PurgeLoadedEntity(Entity _entity)
	{
		if (!IsParsableIntoOTEntDiscriptor(_entity))
		{
			return;
		}

		DS::OTEntDiscriptor __discriptor = ParseIntoOTEntDiscriptor(_entity);
		if (m_UtilizeSpecialDataStructureForFrusumCull)
			m_TurboOctree->Purge(_entity);
		else
		{
			m_QuickCull->Purge(__discriptor);
		}
	}
	bool Scene::IsParsableIntoOTEntDiscriptor(Entity _entity)
	{
		Component::CoreRenderableMeshComponent* _core_mesh_component = nullptr;

		if (_entity.HasComponent<Component::MeshComponent>())
			_core_mesh_component = &_entity.GetComponent<Component::MeshComponent>();

		if (!_core_mesh_component)
			return false;

		return true;
	}
	DS::OTEntDiscriptor Scene::ParseIntoOTEntDiscriptor(Entity _entity)
	{
		if (!IsParsableIntoOTEntDiscriptor(_entity))
			return DS::OTEntDiscriptor();

		DS::OTEntDiscriptor __discriptor;

		Component::CoreRenderableMeshComponent* _core_mesh_component = nullptr;
		_core_mesh_component = &_entity.GetComponent<Component::MeshComponent>();

		Component::TransformComponent& __transform = _entity.GetComponent<Component::TransformComponent>();
		IVModel* _core_model = AssetManager::GetGeometry(_core_mesh_component->GetPackageID());
		StaticMesh* _static_mesh = this->QueryStaticMesh(_core_mesh_component->GetPackageID());

		__discriptor.EntityID = (uint32_t)_entity;
		__discriptor.Bound = _core_model->Bound;

		__discriptor.UpdateBuffer = std::bind(&Component::CoreRenderableMeshComponent::UpdateBuffers, _core_mesh_component);
		__discriptor.UpdateOffset = std::bind(&Component::CoreRenderableMeshComponent::SetOffset, _core_mesh_component, std::placeholders::_1);
		__discriptor.UpdateInstanceCount = std::bind(&StaticMesh::SetVisibleInstanceCount, _static_mesh, std::placeholders::_1);
		__discriptor.Position = __transform.m_Position;
		__discriptor.Scale = __transform.m_Scale;
		__discriptor.PackageID = _core_model->PackageID;
		__discriptor.Valid = true;

		return __discriptor;
	}

	Renderer::IVMasterRenderer* Scene::GetRenderer()
	{
		return m_MyRenderer;
	}
	DS::TurboOT* Scene::GetTurboOT() { return m_TurboOctree; };

	SceneCameraManager* Scene::GetCameraManager() const
	{
		return m_CameraManager;
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

	bool Scene::HasStaticMesh(uint32_t _package_id)
	{
		return (m_StaticMeshRegistry.find(_package_id) != m_StaticMeshRegistry.end());
	}

	bool Scene::HasDynamicMesh(uint32_t _package_id)
	{
		return (m_DynamicMeshRegistry.find(_package_id) != m_DynamicMeshRegistry.end());
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
		if (m_DynamicMeshRegistry.find(_package_id) != m_DynamicMeshRegistry.end())
		{
			m_MyRenderer->PurgeFromRenderStack(m_DynamicMeshRegistry[_package_id]);
			m_DynamicMeshRegistry.erase(_package_id);
			return true;
		}

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
		if (HasDynamicMesh(_model_pkg->PackageID))
		{
			LOG_ERROR("Skinned Mesh already exist! failed to register model package: {0}", _model_pkg->Name);
			return nullptr;
		}

		m_DynamicMeshRegistry.insert(std::make_pair(_model_pkg->PackageID, new DynamicMesh(_model_pkg)));

		m_MyRenderer->PushToRenderStack(m_DynamicMeshRegistry[_model_pkg->PackageID]);

		return m_DynamicMeshRegistry[_model_pkg->PackageID];
	}




///////////////////////////////////////////////////////////////////////// POINT-LIGHT-START /////////////////////////////////////////

	bool Scene::PurgePointLight(uint32_t _entity_id)
	{
		if (m_PointLightRegistry.find(_entity_id) == m_PointLightRegistry.end())
		{
			LOG_ERROR("No Point Light exist! ID:{0}", _entity_id);
			return false;
		}

		m_PointLightRegistry.erase(_entity_id);

		// Update each buffer
		int _idx = 0;
		for (auto iter = m_PointLightRegistry.begin(); iter != m_PointLightRegistry.end(); iter++, _idx++)
		{
			iter->second->SetIndex(_idx);
			iter->second->UpdateBuffer();
		}

		m_LightUtil.PointLightCount--;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);

		return true;
	}
	Component::PointLightComponent* Scene::QueryPointLight(uint32_t _entity_id)
	{
		if (m_PointLightRegistry.find(_entity_id) == m_PointLightRegistry.end())
			return nullptr;

		return m_PointLightRegistry[_entity_id];
	}
	void Scene::RegisterPointLight(uint32_t _entity_id, Component::PointLightComponent* _light)
	{
		if (m_PointLightRegistry.find(_entity_id) != m_PointLightRegistry.end())
		{
			LOG_ERROR("Point Light already exist! ID:{0}", _entity_id);
			return;
		}

		_light->SetIndex(static_cast<int>(m_PointLightRegistry.size()));
		m_PointLightRegistry.insert(std::make_pair(_entity_id, _light));
		_light->UpdateBuffer();

		m_LightUtil.PointLightCount++;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);
	
	}

	///////////////////////////////////////////////////////////////////// POINT_LIGHT_END  ///////////////////////////////////////////


	/////////////////////////////////////////// START DIRECTIONAL LIGHT ///////////////////////////////
	bool Scene::PurgeDirectionalLight(uint32_t _entity_id)
	{
		if (m_DirectionalLightRegistry.find(_entity_id) == m_DirectionalLightRegistry.end())
		{
			LOG_ERROR("No Directional Light exist! ID:{0}", _entity_id);
			return false;
		}

		m_DirectionalLightRegistry.erase(_entity_id);

		// Update each buffer
		int _idx = 0;
		for (auto iter = m_DirectionalLightRegistry.begin(); iter != m_DirectionalLightRegistry.end(); iter++, _idx++)
		{
			iter->second->SetIndex(_idx);
			iter->second->UpdateBuffer();
		}

		m_LightUtil.DirectionalLightCount--;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);

		return true;
	}
	Component::DirectionalLightComponent* Scene::QueryDirectionalLight(uint32_t _entity_id)
	{
		if (m_DirectionalLightRegistry.find(_entity_id) == m_DirectionalLightRegistry.end())
			return nullptr;

		return m_DirectionalLightRegistry[_entity_id];
	}
	void Scene::RegisterDirectionalLight(uint32_t _entity_id, Component::DirectionalLightComponent* _light)
	{
		if (m_DirectionalLightRegistry.find(_entity_id) != m_DirectionalLightRegistry.end())
		{
			LOG_ERROR("Directional Light already exist! ID:{0}", _entity_id);
			return;
		}

		_light->SetIndex(static_cast<int>(m_DirectionalLightRegistry.size()));
		m_DirectionalLightRegistry.insert(std::make_pair(_entity_id, _light));
		_light->UpdateBuffer();

		m_LightUtil.DirectionalLightCount++;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);

	}

	//////////////////////////////////////////// END DIRECTIONAL LIGHT ///////////////////////////////

	////////////////////////////////////////////// START SPOT LIGHT //////////////////////////////////////
	bool Scene::PurgeSpotLight(uint32_t _entity_id)
	{
		if (m_SpotLightRegistry.find(_entity_id) == m_SpotLightRegistry.end())
		{
			LOG_ERROR("No Spot Light exist! ID:{0}", _entity_id);
			return false;
		}

		m_SpotLightRegistry.erase(_entity_id);

		// Update each buffer
		int _idx = 0;
		for (auto iter = m_SpotLightRegistry.begin(); iter != m_SpotLightRegistry.end(); iter++, _idx++)
		{
			iter->second->SetIndex(_idx);
			iter->second->UpdateBuffer();
		}

		m_LightUtil.SpotLightCount--;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);

		return true;
	}
	Component::SpotLightComponent* Scene::QuerySpotLight(uint32_t _entity_id)
	{
		if (m_SpotLightRegistry.find(_entity_id) == m_SpotLightRegistry.end())
			return nullptr;

		return m_SpotLightRegistry[_entity_id];
	}
	void Scene::RegisterSpotlight(uint32_t _entity_id, Component::SpotLightComponent* _light)
	{
		if (m_SpotLightRegistry.find(_entity_id) != m_SpotLightRegistry.end())
		{
			LOG_ERROR("Spot Light already exist! ID:{0}", _entity_id);
			return;
		}

		_light->SetIndex(static_cast<int>(m_SpotLightRegistry.size()));
		m_SpotLightRegistry.insert(std::make_pair(_entity_id, _light));
		_light->UpdateBuffer();

		m_LightUtil.SpotLightCount++;
		Memory::UniformBlockManager::UseBuffer(
			Memory::UniformBufferID::LIGHT_UTILITY)->Update(Memory::s_LightUtilPackageBufferSize, 0, &m_LightUtil);

	}
	///////////////////////////////////////////////// END SPOT LIGHT //////////////////////////////////

	Ray* Scene::GetRay() { return m_SceneRay; }

	void Scene::SwitchContext(BaseWindow* _window)
	{
		m_Window = _window->GetWin();

		/*auto& CameraColl = m_CameraManager->GetCameraList();
		for (auto cam = CameraColl.begin(); cam != CameraColl.end(); cam++)
		{
			if (!cam->second.Camera->IsPowerOn())
				continue;

			if(cam->second.Camera->GetTag() == CAMERA_TASK_TYPE::PLAYER)
				cam->second.Camera->GetCameraController()->SwitchContext(m_Window);
		}*/
	}
	void Scene::ResetScene()
	{
		ResetPhysics();
	}
	void Scene::Update(int _width, int _height)
	{
		m_MasterSceneCamera->Camera->UpdateRenderFrameSize(_width, _height);
	}
}