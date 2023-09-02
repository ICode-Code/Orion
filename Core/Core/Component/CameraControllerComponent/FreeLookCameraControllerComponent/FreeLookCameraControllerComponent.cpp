#include "FreeLookCameraControllerComponent.h"
#include <GLFW/glfw3.h>


namespace OE1Core
{
	namespace Component
	{
		FreeLookCameraControllerComponent::FreeLookCameraControllerComponent(GLFWwindow* _window)
			: BaseCameraControllerComponent{_window}
		{
			m_FinalPosition = glm::vec3(0.870874405f, 2.5f, 0.002f);
			m_CurrentPosition = m_FinalPosition;
		}


		void FreeLookCameraControllerComponent::OnEvent(Event& e)
		{
			EventDispatcher Dispatcher(e);
			Dispatcher.Dispatch<MouseMovedEvent>			(std::bind(&FreeLookCameraControllerComponent::MousePosition,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<MouseButtonPressedEvent>	(std::bind(&FreeLookCameraControllerComponent::MouseKeyPressed,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<MouseButtonReleaseEvent>	(std::bind(&FreeLookCameraControllerComponent::MouseKeyRelease,			this,		std::placeholders::_1));
			Dispatcher.Dispatch<KeyPressedEvent>			(std::bind(&FreeLookCameraControllerComponent::KeyPessed,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<KeyReleaseEvent>			(std::bind(&FreeLookCameraControllerComponent::KeyRelease,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<KeyRepeatEvent>				(std::bind(&FreeLookCameraControllerComponent::KeyRepeat,				this,		std::placeholders::_1));
			Dispatcher.Dispatch<MouseScrolledEvent>			(std::bind(&FreeLookCameraControllerComponent::MouseOnScroll,			this,		std::placeholders::_1));
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


			if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
				Direction += m_Camera->m_Front;

			if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
				Direction -= m_Camera->m_Front;

			if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
				Direction -= m_Camera->m_Right;

			if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
				Direction += m_Camera->m_Right;

			if (glfwGetKey(m_Window, GLFW_KEY_E) == GLFW_PRESS)
				Direction += m_Camera->m_Up;

			if (glfwGetKey(m_Window, GLFW_KEY_Q) == GLFW_PRESS)
				Direction -= m_Camera->m_Up;

			if (glm::length(Direction) > 0.0f)
				m_FinalPosition = m_CurrentPosition + (glm::normalize(Direction) * speed);

		}
		void FreeLookCameraControllerComponent::UpdateInput(float _dt)
		{
			m_DeltaTime = _dt;
			m_InitialPosition = m_CurrentPosition;
			HandleKeyInput();
			
			if (glm::length(m_FinalPosition - m_CurrentPosition) > 0.001f)
			{
				m_DeltaPosition = Lerp(m_InitialPosition, m_FinalPosition, m_DeltaTime * m_SpeedFactor);
				m_CurrentPosition = m_DeltaPosition;
			}
			m_Camera->Update(m_CurrentPosition);
		}

		bool FreeLookCameraControllerComponent::MousePosition(MouseMovedEvent& e)
		{
			if (!m_IsControlKeyPressed)
				return true;

			if (m_FirstMouse)
			{
				m_LastMousePosition.x = (float)e.GetX();
				m_LastMousePosition.y = (float)e.GetY();
				m_FirstMouse = false;
			}

			float x_offset = (float)e.GetX() - m_LastMousePosition.x;
			float y_offset = m_LastMousePosition.y - (float)e.GetY();


			x_offset *= m_Sensitivity;
			y_offset *= m_Sensitivity;

			m_Camera->m_Pitch += y_offset;
			m_Camera->m_Yaw += x_offset;

			if (m_Camera->m_Pitch > 89.0f)
				m_Camera->m_Pitch = 89.0f;
			else if (m_Camera->m_Pitch < -89.0f)
				m_Camera->m_Pitch = -89.0f;

			/*glm::clamp(m_Camera->m_Pitch, -89.0f, 89.0f);*/

			m_LastMousePosition.x = (float)e.GetX();
			m_LastMousePosition.y = (float)e.GetY();

			UpdateCameraView();

			return true;

		}
		bool FreeLookCameraControllerComponent::KeyPessed(KeyPressedEvent& e)			{ return true; }
		bool FreeLookCameraControllerComponent::KeyRelease(KeyReleaseEvent& e)			{ return true; }
		bool FreeLookCameraControllerComponent::KeyRepeat(KeyRepeatEvent& e)			{ return true; }
		bool FreeLookCameraControllerComponent::MouseOnScroll(MouseScrolledEvent& e)	{ return false; }
		bool FreeLookCameraControllerComponent::MouseKeyPressed(MouseButtonPressedEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = true;
				LockMouse(true);
			}
			return true;
		}
		bool FreeLookCameraControllerComponent::MouseKeyRelease(MouseButtonReleaseEvent& e)
		{
			if (m_ControlKey == e.GetButton())
			{
				m_IsControlKeyPressed = false;
				LockMouse(false);
			}
			return true;
		}
	}
}