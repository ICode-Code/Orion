#include "RenderController.h"
#include "../Scene.h"


namespace OE1Core
{
	RenderController::RenderController(Scene* _scene)
	{
		m_Scene = _scene;
	}
	RenderController::~RenderController()
	{

	}

	void RenderController::RenderMasterCameraScene()
	{
		m_Scene->m_MyRenderer->MasterCameraPass(m_Scene->m_MasterSceneCamera->Camera);
	}
	void RenderController::RenderClientCameraScene()
	{
		auto __camera_view = m_Scene->m_EntityRegistry.view<Component::CameraComponent>();
		
		for (auto ent : __camera_view)
		{
			Component::CameraComponent& _camera = __camera_view.get<Component::CameraComponent>(ent);

			if (_camera.GetPowerState() == CameraParameter::CAMERA_POWER_STATE::ON)
				m_Scene->m_MyRenderer->ClientCameraPass(&_camera);
		}
	}
	void RenderController::FlushRenderCommand()
	{
		m_Scene->m_MyRenderer->FlushRenderCommand();
	}
}