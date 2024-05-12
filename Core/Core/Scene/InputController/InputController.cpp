#include "InputController.h"
#include "../Scene.h"
#include "../Entity.h"


namespace OE1Core
{
	InputController::InputController(Scene* _scene)
	{
		m_Scene = _scene;
	}
	InputController::~InputController()
	{

	}
	void InputController::MasterCameraBufferUpdate(float _dt)
	{
		m_Scene->m_MasterSceneCamera->Camera->UpdateBuffer(_dt);
	}
	void InputController::ControllerComponentBufferUpdate(float _dt)
	{
		auto __camera_view = m_Scene->m_EntityRegistry.view<Component::CameraComponent>();

		for (auto ent : __camera_view)
		{
			Component::CameraComponent& _camera = __camera_view.get<Component::CameraComponent>(ent);

			if ((_camera.GetPowerState() == CameraParameter::CAMERA_POWER_STATE::OFF))
				continue;

			_camera.UpdateBuffer(_dt);
		}
	}
	void InputController::QuickInputUpdateControllerComponent(float _dt)
	{

		auto __camera_view = m_Scene->m_EntityRegistry.view<Component::CameraComponent>();

		for (auto ent : __camera_view)
		{
			Component::CameraComponent& _camera = __camera_view.get<Component::CameraComponent>(ent);
			Component::TransformComponent& _transform = m_Scene->m_EntityRegistry.get<Component::TransformComponent>(ent);
			
			if ((_camera.GetPowerState() == CameraParameter::CAMERA_POWER_STATE::OFF))
				continue;

			if (_camera.GetController() && (_camera.GetFlightState() == CameraParameter::CAMERA_FLIGHT_STATE::PILOT))
			{
				_camera.GetController()->UpdateInput(_dt);
				_transform.m_Position = _camera.GetPosition();
			}
			else if (_camera.GetController())
				_camera.GetController()->OverrideFinalPosition(_transform.m_Position, _dt);
		}
	}

	void InputController::OnEventControllerComponent(OECore::IEvent& e)
	{
		auto __camera_view = m_Scene->m_EntityRegistry.view<Component::CameraComponent>();

		for (auto ent : __camera_view)
		{
			Component::CameraComponent& _camera = __camera_view.get<Component::CameraComponent>(ent);
			Component::TransformComponent& _transform = m_Scene->m_EntityRegistry.get<Component::TransformComponent>(ent);

			if ((_camera.GetPowerState() == CameraParameter::CAMERA_POWER_STATE::OFF))
				continue;

			if (_camera.GetController() && (_camera.GetFlightState() == CameraParameter::CAMERA_FLIGHT_STATE::PILOT))
				_camera.GetController()->OnEvent(e);
		}
	}
	void InputController::OnEventMasterCamera(OECore::IEvent& e)
	{
		if (m_Scene->m_MasterSceneCamera->Camera->GetFlightState() == CameraParameter::CAMERA_FLIGHT_STATE::IDEL)
			return;

		m_Scene->m_MasterSceneCamera->Controller->OnEvent(e);
	}
	void InputController::QuickInputUpdateMasterCamera(float _dt)
	{
		if (m_Scene->m_MasterSceneCamera->Camera->GetFlightState() == CameraParameter::CAMERA_FLIGHT_STATE::IDEL)
			return;
		m_Scene->m_MasterSceneCamera->Controller->UpdateInput(_dt);
	}

	void InputController::ThirdPersonCharacterControllerInputUpdate(float _dt)
	{
		auto tpcc_comp = m_Scene->m_EntityRegistry.view<Component::ThirdPersonCharacterControllerComponent>();
		for (auto ent : tpcc_comp)
		{
			Component::ThirdPersonCharacterControllerComponent& tpcc = tpcc_comp.get<Component::ThirdPersonCharacterControllerComponent>(ent);
			tpcc.UpdateTargetTransform(_dt);
		}
	}
	void InputController::FirstPersonCharacterControllerInputUpdate(float _dt)
	{

	}

	void InputController::UpdateCameraInput(Component::BaseCameraControllerComponent* _controller, float _dt)
	{
		_controller->UpdateInput(_dt);

		if (_controller->GetCameraComponent())
			_controller->GetCameraComponent()->UpdateBuffer(_dt);
	}

	void InputController::UpdateActivePlayerEntity()
	{
		if (m_Scene->m_ActivePlayerEntity)
			m_Scene->m_ActivePlayerEntity->Update();
	}



}