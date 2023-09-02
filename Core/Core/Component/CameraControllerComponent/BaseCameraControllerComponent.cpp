#include "BaseCameraControllerComponent.h"
#include <GLFW/glfw3.h>

namespace OE1Core
{
	namespace Component
	{
		BaseCameraControllerComponent::BaseCameraControllerComponent(GLFWwindow* _active_context)
		{
			m_Window = _active_context;
			m_ControlKey = GLFW_MOUSE_BUTTON_RIGHT;
		}

		void BaseCameraControllerComponent::SetControlMouseKey(int _key)
		{

		}
		/*void BaseCameraControllerComponent::SetTransform(Component::TransformComponent* _transform)
		{
			m_Transform = _transform;
		}*/
		void BaseCameraControllerComponent::SetCameraComponent(Component::CameraComponent* _camera)
		{
			m_Camera = _camera;
			UpdateCameraView();
			m_Camera->Update(m_CurrentPosition);
		}

		Component::CameraComponent* BaseCameraControllerComponent::GetCameraComponent()
		{
			return m_Camera;
		}
		/*Component::TransformComponent* BaseCameraControllerComponent::GetTransformComponent()
		{
			return m_Transform;
		}*/
		void BaseCameraControllerComponent::LockMouse(bool _v)
		{
			m_FirstMouse = _v;
			_v ? glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED)
				: glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		glm::vec3 BaseCameraControllerComponent::Lerp(const glm::vec3& a, const glm::vec3& b, float t)
		{
			return  a + (b - a) * t;
		}
		void BaseCameraControllerComponent::Focus(glm::vec3 _target)
		{
			glm::vec3 target_direction = glm::normalize(_target - m_CurrentPosition);

			m_FinalPosition = _target - (target_direction * m_DistanceFromFocusTarget);

			// Update the camera's pitch and yaw based on the new direction vector
			m_Camera->m_Pitch = glm::degrees(asin(target_direction.y));
			m_Camera->m_Yaw = glm::degrees(atan2(target_direction.z, target_direction.x));

			// Recalculate the camera's front, right, and up vectors
			m_Camera->m_Front = target_direction;
			m_Camera->m_Right = glm::normalize(glm::cross(m_Camera->m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
			m_Camera->m_Up = glm::normalize(glm::cross(m_Camera->m_Right, m_Camera->m_Front));
		}
		bool BaseCameraControllerComponent::MousePosition(MouseMovedEvent& e)				{ return false; };
		bool BaseCameraControllerComponent::KeyPessed(KeyPressedEvent& e)					{ return false; };
		bool BaseCameraControllerComponent::KeyRepeat(KeyRepeatEvent& e)					{ return false; }
		bool BaseCameraControllerComponent::KeyRelease(KeyReleaseEvent& e)					{ return false; };
		bool BaseCameraControllerComponent::MouseKeyPressed(MouseButtonPressedEvent& e)		{ return false; };
		bool BaseCameraControllerComponent::MouseKeyRelease(MouseButtonReleaseEvent& e)		{ return false; };
		bool BaseCameraControllerComponent::MouseOnScroll(MouseScrolledEvent& e)			{ return false; };
	}
}