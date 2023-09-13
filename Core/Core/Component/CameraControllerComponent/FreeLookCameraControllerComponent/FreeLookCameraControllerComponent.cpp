#include "FreeLookCameraControllerComponent.h"

namespace OE1Core
{
	namespace Component
	{
		FreeLookCameraControllerComponent::FreeLookCameraControllerComponent(SDL_Window* _window)
			: BaseCameraControllerComponent{_window}
		{
			m_FinalPosition = glm::vec3(0.870874405f, 2.5f, 0.002f);
			m_CurrentPosition = m_FinalPosition;
		}


		void FreeLookCameraControllerComponent::OnEvent(OECore::IEvent& e)
		{
			OECore::IEventDispatcher Dispatcher(e);
			Dispatcher.Dispatch<OECore::MouseMovedEvent>			(std::bind(&FreeLookCameraControllerComponent::MousePosition,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::MouseButtonPressedEvent>	(std::bind(&FreeLookCameraControllerComponent::MouseKeyPressed,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::MouseButtonReleaseEvent>	(std::bind(&FreeLookCameraControllerComponent::MouseKeyRelease,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::KeyPressedEvent>			(std::bind(&FreeLookCameraControllerComponent::KeyPessed,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::KeyReleaseEvent>			(std::bind(&FreeLookCameraControllerComponent::KeyRelease,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::KeyRepeatEvent>				(std::bind(&FreeLookCameraControllerComponent::KeyRepeat,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<OECore::MouseScrolledEvent>			(std::bind(&FreeLookCameraControllerComponent::MouseOnScroll,			this,		std::placeholders::_1));
		}
		void FreeLookCameraControllerComponent::UpdateCameraView()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(m_Camera->m_Yaw)) * cos(glm::radians(m_Camera->m_Pitch));
			front.y = sin(glm::radians(m_Camera->m_Pitch));
			front.z = sin(glm::radians(m_Camera->m_Yaw)) * cos(glm::radians(m_Camera->m_Pitch));

			m_Camera->m_Front = glm::normalize(front);

			m_Camera->m_Right = glm::normalize(glm::cross(m_Camera->m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
			m_Camera->m_Up = glm::normalize(glm::cross(m_Camera->m_Right, m_Camera->m_Front));
		}
		void FreeLookCameraControllerComponent::HandleKeyInput()
		{
			if (!m_IsControlKeyPressed)
				return;

			float speed = (m_Speed * m_SpeedFactor) * m_DeltaTime;

			glm::vec3 Direction = glm::vec3(0.0f);

			if (m_KeyState[SDL_SCANCODE_W])
				Direction += m_Camera->m_Front;

			if (m_KeyState[SDL_SCANCODE_S])
				Direction -= m_Camera->m_Front;

			if (m_KeyState[SDL_SCANCODE_A])
				Direction -= m_Camera->m_Right;

			if (m_KeyState[SDL_SCANCODE_D])
				Direction += m_Camera->m_Right;

			if (m_KeyState[SDL_SCANCODE_E])
				Direction += m_Camera->m_Up;

			if (m_KeyState[SDL_SCANCODE_Q])
				Direction -= m_Camera->m_Up;

			if (glm::length(Direction) > 0.0f)
				m_FinalPosition = m_CurrentPosition + (glm::normalize(Direction) * speed);

		}
		void FreeLookCameraControllerComponent::UpdateInput(float _dt)
		{
			m_DeltaTime = _dt;
			m_InitialPosition = m_CurrentPosition;

			HandleKeyInput();
			
			float delta_dist = glm::length(m_FinalPosition - m_CurrentPosition);
			if (delta_dist > 0.001f)
			{
				m_DeltaPosition = Lerp(m_InitialPosition, m_FinalPosition, m_DeltaTime * m_SpeedFactor);
				m_CurrentPosition = m_DeltaPosition;
			}
			m_Camera->Update(m_CurrentPosition);
		}

		bool FreeLookCameraControllerComponent::MousePosition(OECore::MouseMovedEvent& e)
		{
			if (!m_IsControlKeyPressed)
				return true;

			float x_offset = (float)e.GetX() * m_Sensitivity;
			float y_offset = -(float)e.GetY() * m_Sensitivity;

			SDL_WarpMouseInWindow(m_Window, m_WinCenterX, m_WinCenterY);

			m_Camera->m_Pitch += y_offset;
			m_Camera->m_Yaw += x_offset;

			if (m_Camera->m_Pitch > 89.0f)
				m_Camera->m_Pitch = 89.0f;
			else if (m_Camera->m_Pitch < -89.0f)
				m_Camera->m_Pitch = -89.0f;


			m_LastMousePosition.x = (float)e.GetX();
			m_LastMousePosition.y = (float)e.GetY();

			UpdateCameraView();

			return true;

		}
		bool FreeLookCameraControllerComponent::KeyPessed(OECore::KeyPressedEvent& e)			
		{ 

			return true; 
		}
		bool FreeLookCameraControllerComponent::KeyRelease(OECore::KeyReleaseEvent& e)			{ return true; }
		bool FreeLookCameraControllerComponent::KeyRepeat(OECore::KeyRepeatEvent& e)			{ return true; }
		bool FreeLookCameraControllerComponent::MouseOnScroll(OECore::MouseScrolledEvent& e)	{ return false; }
		bool FreeLookCameraControllerComponent::WindowResize(OECore::WindowResizeEvent& e)
		{
			m_WinCenterX = e.GetWidth();
			m_WinCenterY = e.GetHeight();

			m_WinCenterX /= 2;
			m_WinCenterY /= 2;


			return true;
		}
		bool FreeLookCameraControllerComponent::MouseKeyPressed(OECore::MouseButtonPressedEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = true;
				LockMouse(m_IsControlKeyPressed);
			}
			return true;
		}
		bool FreeLookCameraControllerComponent::MouseKeyRelease(OECore::MouseButtonReleaseEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = false;
				LockMouse(m_IsControlKeyPressed);
			}

			return true;
		}
	}
}