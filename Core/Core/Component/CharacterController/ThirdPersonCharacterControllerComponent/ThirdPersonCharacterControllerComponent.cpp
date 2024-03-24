#include "ThirdPersonCharacterControllerComponent.h"
#include "LogUI.h"


namespace OE1Core
{
	namespace Component
	{
		ThirdPersonCharacterControllerComponent::ThirdPersonCharacterControllerComponent(
			Component::TransformComponent* _target,
			Component::CameraComponent* _camera,
			Component::AnimationController* _controller)
		{
			m_TargetTransform = _target;
			m_TargetCamera = _camera;
			m_TargetAnimationController = _controller;

			if(!m_TargetCamera)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] initilized with <NULL> Camera Target!", OELog::CRITICAL));
			if(!m_TargetAnimationController)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] initilized with <NULL> Animation Controller!", OELog::CRITICAL));

			if(!m_TargetTransform)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] initilized with <NULL> Target Transform!", OELog::CRITICAL));
		}
		ThirdPersonCharacterControllerComponent::~ThirdPersonCharacterControllerComponent()
		{

		}

		void ThirdPersonCharacterControllerComponent::UpdateTargetTransform(float dt)
		{
			TPCC_ProcessRapidKeyInput(dt);
		}
		void ThirdPersonCharacterControllerComponent::OnEvent(OECore::IEvent& e)
		{
			OECore::IEventDispatcher _dispatcher(e);
			_dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&ThirdPersonCharacterControllerComponent::TPCC_KeyPressEvent, this, std::placeholders::_1));
			_dispatcher.Dispatch<OECore::KeyReleaseEvent>(std::bind(&ThirdPersonCharacterControllerComponent::TPCC_KeyReleaseEvent, this, std::placeholders::_1));
		}
		void ThirdPersonCharacterControllerComponent::SetTargetTransform(TransformComponent* _target, Entity* _host_entity)
		{
			if(!_target)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] Received <NULL> Target Transform!", OELog::CRITICAL));
			m_TargetTransform = _target;
		}
		TransformComponent* ThirdPersonCharacterControllerComponent::GetTargetTransform() { return m_TargetTransform; }
	

		void ThirdPersonCharacterControllerComponent::SetCameraComponent(Component::CameraComponent* _camera)
		{
			if (!_camera)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] Received <NULL> Camera Target!", OELog::CRITICAL));
			m_TargetCamera = _camera;
		}
		Component::CameraComponent* ThirdPersonCharacterControllerComponent::GetCameraComponent() { return m_TargetCamera; }

		void ThirdPersonCharacterControllerComponent::SetTargetAnimationController(Component::AnimationController* _controller)
		{
			if (!_controller)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] Received <NULL> Target Animation Controller!", OELog::CRITICAL));
			m_TargetAnimationController = _controller;
		}
		Component::AnimationController* ThirdPersonCharacterControllerComponent::GetAnimationController() { return m_TargetAnimationController; }

		void ThirdPersonCharacterControllerComponent::TPCC_ProcessRapidKeyInput(float dt)
		{
			if (!m_TargetCamera) return;
			if (!m_TargetAnimationController) return;
			if (!m_TargetTransform) return;

			// running ?
			m_TPCCFreeKeyInputState[SDL_SCANCODE_LSHIFT] ? m_SprintKeyPressed = true : m_SprintKeyPressed = false;


			

			/// Camera position Ignoring Y axis
			glm::vec3 cam_pos = glm::vec3(m_TargetCamera->m_Position.x, 1.0f, m_TargetCamera->m_Position.z);

			/// Target Position Ignoring Y axis
			glm::vec3 targ_pos = glm::vec3(m_TargetTransform->m_Position.x, 1.0f, m_TargetTransform->m_Position.z);

			/// Compute Camera Direction
			glm::vec3 dir = cam_pos - targ_pos;

			/// Get Target Front while ingoring the Y axis
			/// Since in 3rd persone camea controller the camera need to follow
			/// the target from behind we need to know the target traform fron direction
			glm::vec3 targ_front = m_TargetTransform->GetFront();
			targ_front.y = 0.0f; // Ingore Y 

			// Get Target Right Direction
			glm::vec3 targ_left = m_TargetTransform->GetRight();
			targ_left.y = 0.0f; // Ignore Y

			// Normalize
			glm::vec3 camera_forward = glm::normalize(dir);
			glm::vec3 target_forward = glm::normalize(targ_front);
			

			float dot_prod = glm::dot(camera_forward, target_forward);

			float dot_prod_right = glm::dot(camera_forward, glm::normalize(targ_left));


			/// Movement backward and Movment Left is consist of Negative numbers
			/// so we need a flag (this is tem fix)
			bool __negatory = false;

			/// If no key is pressed we set the current speed and rotate value to 0
			/// we are trying to support mutikey input, like turn left or right while walking forward
			/// so we don't wrapp all key input check in one branch
			bool __keypressed = false;



			if (m_TPCCFreeKeyInputState[SDL_SCANCODE_W])
			{
				m_CurrentMoveSpeed = m_SprintKeyPressed ? m_SprintSpeed : m_WalkSpeed;
				__keypressed = true;
				if (dot_prod > m_AlignmentThreshold)
					m_CurrentTurnSpeed = 0.0f;
				else
					m_CurrentTurnSpeed = (dot_prod_right >= 0.0f) ? -m_TurnSpeed : m_TurnSpeed;
			}
			else if (m_TPCCFreeKeyInputState[SDL_SCANCODE_S])
			{
				m_CurrentMoveSpeed = m_SprintKeyPressed ? -m_SprintSpeed : -m_WalkSpeed;
				__negatory = true;
				__keypressed = true;

				if (dot_prod < -m_AlignmentThreshold)
					m_CurrentTurnSpeed = 0.0f;
				else
					m_CurrentTurnSpeed = (dot_prod_right < 0.0f) ? -m_TurnSpeed : m_TurnSpeed;
			}
			
			if (m_TPCCFreeKeyInputState[SDL_SCANCODE_A])
			{
				__negatory = true;
				__keypressed = true;
				m_CurrentMoveSpeed = m_SprintKeyPressed ? -m_SprintSpeed : -m_WalkSpeed;

				if (dot_prod_right > m_AlignmentThreshold)
					m_CurrentTurnSpeed = 0.0f;
				else
					m_CurrentTurnSpeed = (dot_prod < 0.0f) ? -m_TurnSpeed : m_TurnSpeed;
			}
			else if (m_TPCCFreeKeyInputState[SDL_SCANCODE_D])
			{
				m_CurrentMoveSpeed = m_SprintKeyPressed ? m_SprintSpeed : m_WalkSpeed;
				if (__negatory)
					m_CurrentMoveSpeed = -m_CurrentMoveSpeed;
				__keypressed = true;

				if (dot_prod_right < -m_AlignmentThreshold)
					m_CurrentTurnSpeed = 0.0f;
				else
					m_CurrentTurnSpeed = (dot_prod >= 0.0f) ? -m_TurnSpeed : m_TurnSpeed;
			}
			
			if(!__keypressed)
			{
				m_CurrentMoveSpeed = 0.0f;
				m_CurrentTurnSpeed = 0.0f;
			}
			

			/*if (m_TPCCFreeKeyInputState[SDL_SCANCODE_D])
			{
				m_CurrentTurnSpeed = -m_TurnSpeed;
			}
			else if (m_TPCCFreeKeyInputState[SDL_SCANCODE_A])
			{
					m_CurrentTurnSpeed = m_TurnSpeed;
			}*/
			

			//if (m_TPCCFreeKeyInputState[SDL_SCANCODE_SPACE])
			//{
			//	// Jump
			//	if (m_SprintKeyPressed)
			//		m_TargetAnimationController->SetActiveState(ANIMATION_STATE::RUN_JUMP);
			//	else
			//		m_TargetAnimationController->SetActiveState(ANIMATION_STATE::JUMP);
			//}


			m_TargetTransform->m_Euler.y += (m_CurrentTurnSpeed * dt);
			m_TargetTransform->m_Euler.y = fmod(m_TargetTransform->m_Euler.y, 360.0f);
			float distance = m_CurrentMoveSpeed * dt;

			float dx = distance * sin(glm::radians(m_TargetTransform->m_Euler.y));
			float dz = distance * cos(glm::radians(m_TargetTransform->m_Euler.y));

			if (__negatory)
			{
				dx = -dx;
				dz = -dz;
			}

			m_TargetTransform->m_Position.x += dx;
			m_TargetTransform->m_Position.z += dz;
		
		}
		bool ThirdPersonCharacterControllerComponent::TPCC_KeyPressEvent(OECore::KeyPressedEvent& _event)
		{
			if(!m_TargetAnimationController)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCharacterControllerComponent ] Target Animation Controller is <NULL>!", OELog::CRITICAL));
			return true;
		}
		bool ThirdPersonCharacterControllerComponent::TPCC_KeyReleaseEvent(OECore::KeyReleaseEvent& _event)
		{
			return true;
		}

	}
}