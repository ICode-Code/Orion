#include "ThirdPersonCameraControllerComponent.h"
#include "LogUI.h"

namespace OE1Core
{
	namespace Component
	{
		ThirdPersonCameraControllerComponent::ThirdPersonCameraControllerComponent(SDL_Window* _window, Component::TransformComponent* _tranform)
			: BaseCameraControllerComponent{_window}
		{
			m_FinalPosition = glm::vec3(0.870874405f, 2.5f, 0.002f);
			m_CurrentPosition = m_FinalPosition;

			m_TargetTransform = _tranform;

			m_FullMouseControl = false;
			LockMouse(m_FullMouseControl);
			if (!m_TargetTransform)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCameraControllerComponent ] initilized with <NULL> Target Tranform!", OELog::CRITICAL));
		}

		ThirdPersonCameraControllerComponent::~ThirdPersonCameraControllerComponent()
		{

		}

		void ThirdPersonCameraControllerComponent::SetTargetTransform(Component::TransformComponent* _tranform)
		{
			if (!_tranform)
				LOG_ERROR(LogLayer::Pipe("[ ThirdPersonCameraControllerComponent ] Received <NULL> Target Transform!", OELog::CRITICAL));
			m_TargetTransform = _tranform;
		}
		Component::TransformComponent* ThirdPersonCameraControllerComponent::GetTargetTransform()
		{
			return m_TargetTransform;
		}

		void ThirdPersonCameraControllerComponent::OnEvent(OECore::IEvent& e)
		{
			OECore::IEventDispatcher Dispatcher(e);
			Dispatcher.Dispatch<OECore::MouseMovedEvent>(std::bind(&ThirdPersonCameraControllerComponent::MousePosition, this, std::placeholders::_1));
			Dispatcher.Dispatch<OECore::MouseScrolledEvent>(std::bind(&ThirdPersonCameraControllerComponent::MouseOnScroll, this, std::placeholders::_1));
			Dispatcher.Dispatch<OECore::WindowResizeEvent>(std::bind(&ThirdPersonCameraControllerComponent::WindowResize, this, std::placeholders::_1));
			
			Dispatcher.Dispatch<OECore::MouseButtonPressedEvent>(std::bind(&ThirdPersonCameraControllerComponent::MouseKeyPressed, this, std::placeholders::_1));
			Dispatcher.Dispatch<OECore::MouseButtonReleaseEvent>(std::bind(&ThirdPersonCameraControllerComponent::MouseKeyRelease, this, std::placeholders::_1));

			Dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&ThirdPersonCameraControllerComponent::KeyPessed, this, std::placeholders::_1));
			Dispatcher.Dispatch<OECore::KeyReleaseEvent>(std::bind(&ThirdPersonCameraControllerComponent::KeyRelease, this, std::placeholders::_1));

		}
		void ThirdPersonCameraControllerComponent::UpdateCameraView()
		{

			float horizonatlDistance = m_DistanceToTarget * cos(glm::radians(m_Camera->m_Pitch));
			float verticalDistance = m_DistanceToTarget * sin(glm::radians(m_Camera->m_Pitch));

			//m_TargetTransform->m_Euler.y = m_Camera->m_Yaw;

			float theta = m_Camera->m_Yaw;// glm::mix(m_TargetTransform->m_Euler.y, , 0.4f);
			 
			float offsetX = horizonatlDistance * sin(glm::radians(theta));
			float offsetZ = horizonatlDistance * cos(glm::radians(theta));


			m_FinalPosition.x = m_TargetTransform->m_Position.x - offsetX;
			m_FinalPosition.y = m_TargetTransform->m_Position.y + verticalDistance;
			m_FinalPosition.z = m_TargetTransform->m_Position.z - offsetZ;

			m_Camera->m_Front = m_TargetTransform->m_Position;
		}
		void ThirdPersonCameraControllerComponent::UpdateInput(float _dt)
		{
			m_DeltaTime = _dt;
			m_InitialPosition = m_CurrentPosition;

			HandleKeyInput();
			UpdateCameraView();

			float delta_dist = glm::length(m_FinalPosition - m_CurrentPosition);
			if (delta_dist > 0.001f)
			{
				m_DeltaPosition = Lerp(m_InitialPosition, m_FinalPosition, m_DeltaTime * m_SpeedFactor);
				m_CurrentPosition = m_DeltaPosition;
			}
			glm::vec3 targ = m_TargetTransform->m_Position;
			targ.y += m_FocusHeight;
			targ.x += m_ShiftRightCameraFocus;
			m_Camera->Update(m_FinalPosition, targ);
		}
		void ThirdPersonCameraControllerComponent::OverrideFinalPosition(glm::vec3 _final_position, float _dt)
		{
			/*m_DeltaTime = _dt;
			m_InitialPosition = m_CurrentPosition;

			float delta_dist = glm::length(_final_position - m_CurrentPosition);
			if (delta_dist > 0.001f)
			{
				m_DeltaPosition = Lerp(m_InitialPosition, _final_position, m_DeltaTime * m_SpeedFactor);
				m_CurrentPosition = m_DeltaPosition;
			}
			m_Camera->Update(m_CurrentPosition);*/
		}
		void ThirdPersonCameraControllerComponent::HandleKeyInput() 
		{
			//m_FinalPosition = m_TargetTransform->m_Position - (glm::normalize(m_TargetTransform->Getback()) * m_DistanceToTarget);
			//m_FinalPosition.y += m_FocusHeight;

		}

		bool ThirdPersonCameraControllerComponent::MousePosition(OECore::MouseMovedEvent& e)
		{
			if (!m_Camera) return true;
			if (!m_FullMouseControl) return true;

			float x_offset = (float)e.GetX() * m_Sensitivity;
			float y_offset = -(float)e.GetY() * m_Sensitivity;

			SDL_WarpMouseInWindow(m_Window, m_WinCenterX, m_WinCenterY);

			if (!m_FlipMouse)
			{
				m_Camera->m_Pitch -= y_offset;
				m_Camera->m_Yaw -= x_offset;
			}
			else
			{
				m_Camera->m_Pitch += y_offset;
				m_Camera->m_Yaw += x_offset;
			}

			if (m_Camera->m_Pitch > m_PitchConstrainMax)
				m_Camera->m_Pitch = m_PitchConstrainMax;
			else if (m_Camera->m_Pitch < m_PitchConstrainMin)
				m_Camera->m_Pitch = m_PitchConstrainMin;


			m_LastMousePosition.x = (float)e.GetX();
			m_LastMousePosition.y = (float)e.GetY();


			return true;

		}
		bool ThirdPersonCameraControllerComponent::WindowResize(OECore::WindowResizeEvent& e)
		{
			m_WinCenterX = e.GetWidth();
			m_WinCenterY = e.GetHeight();

			m_WinCenterX /= 2;
			m_WinCenterY /= 2;


			return true;
		}
		bool ThirdPersonCameraControllerComponent::MouseKeyPressed(OECore::MouseButtonPressedEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = true;
				LockMouse(m_IsControlKeyPressed);
			}
			return true;
		}
		bool ThirdPersonCameraControllerComponent::MouseKeyRelease(OECore::MouseButtonReleaseEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = false;
				LockMouse(m_IsControlKeyPressed);
			}

			return true;
		}
		bool ThirdPersonCameraControllerComponent::KeyPessed(OECore::KeyPressedEvent& e)
		{
			return true;
		}
		bool ThirdPersonCameraControllerComponent::KeyRelease(OECore::KeyReleaseEvent& e)
		{
			if (e.GetKeyCode() == SDLK_ESCAPE)
				m_FullMouseControl = !m_FullMouseControl;

			LockMouse(m_FullMouseControl);
			return true;
		}
		bool ThirdPersonCameraControllerComponent::MouseOnScroll(OECore::MouseScrolledEvent& e) 
		{

			return true; 
		}
	}
}