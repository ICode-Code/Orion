#include "GenesisController.h"
#include "../Scene.h"
#include "../Entity.h"


namespace OE1Core
{
	GenesisController::GenesisController(Scene* _scene)
	{
		m_Scene = _scene;
	}
	GenesisController::~GenesisController()
	{

	}


	void GenesisController::InputUpdate(float _dt)
	{
		if (!m_Scene->m_Protagonist) return;
		if (!m_Scene->m_Protagonist->GetCamera()) return;
		if (!m_Scene->m_Protagonist->GetActorEntity()) return;


		Component::CameraComponent* _camera = m_Scene->m_Protagonist->GetCamera();
		
		// Cull
		m_Scene->UpdateCulledBuffer(_camera);
		
		
		Entity* _target_entity = m_Scene->m_Protagonist->GetActorEntity();
		
		if (_camera->GetController())
			_camera->GetController()->UpdateInput(_dt);

		if (_target_entity->HasComponent<Component::ThirdPersonCharacterControllerComponent>())
			_target_entity->GetComponent<Component::ThirdPersonCharacterControllerComponent>().UpdateTargetTransform(_dt);

		_target_entity->Update();

		if (m_Scene->ShouldUseRenderThreadForAnimationUpdate())
			m_Scene->UpdateAnimationTransform();
	}
	void GenesisController::UpdateBuffer(float _dt)
	{
		if (!m_Scene->m_Protagonist) return;
		if (!m_Scene->m_Protagonist->GetCamera()) return;

		Component::CameraComponent* _camera = m_Scene->m_Protagonist->GetCamera();

		_camera->UpdateBuffer(_dt);

		m_Scene->UpdateAnimationComponents();
	}
	void GenesisController::InitRender()
	{
		if (!m_Scene->m_Protagonist) return;
		if (!m_Scene->m_Protagonist->GetCamera()) return;

		Component::CameraComponent* _camera = m_Scene->m_Protagonist->GetCamera();

		m_Scene->m_MyRenderer->ClientCameraPass(_camera);

		m_Scene->m_MyRenderer->RenderFullScreenQuadToDefaultFramebuffer(_camera);

		m_Scene->m_MyRenderer->FlushRenderCommand();
	}
	void GenesisController::OnEvent(OECore::IEvent& e)
	{
		if (!m_Scene->m_Protagonist) return;
		if (!m_Scene->m_Protagonist->GetCamera()) return;

		Component::CameraComponent* _camera = m_Scene->m_Protagonist->GetCamera();
		if (_camera->GetController())
			_camera->GetController()->OnEvent(e);
	}
	void GenesisController::UpdateFrameRes(int _width, int _height)
	{	
		if (!m_Scene->m_Protagonist) return;
		if (!m_Scene->m_Protagonist->GetCamera()) return;

		Component::CameraComponent* _camera = m_Scene->m_Protagonist->GetCamera();
		_camera->UpdateRenderFrameSize(_width, _height);
	}
}