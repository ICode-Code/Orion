#include "BaseCameraControllerComponent.h"

namespace OE1Core
{
	namespace Component
	{
		BaseCameraControllerComponent::BaseCameraControllerComponent(SDL_Window* _active_context)
		{
			m_Window = _active_context;
			m_ControlKey = SDL_BUTTON_RIGHT;
			m_Speed = 10.0f;
			m_Sensitivity = 0.04f;
			SDL_GetWindowSize(m_Window, &m_WinCenterX, &m_WinCenterY);
			m_WinCenterX /= 2;
			m_WinCenterY /= 2;
		}
		void BaseCameraControllerComponent::SwitchContext(SDL_Window* _window)
		{
			m_Window = _window;
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
		void BaseCameraControllerComponent::LockMouse(bool _lock)
		{
			if (_lock)
			{
				SDL_ShowCursor(SDL_DISABLE);
				SDL_SetRelativeMouseMode(SDL_TRUE);
			}
			else
			{
				SDL_ShowCursor(SDL_ENABLE);
				SDL_SetRelativeMouseMode(SDL_FALSE);
			}
		}
		glm::vec3 BaseCameraControllerComponent::Lerp(const glm::vec3& a, const glm::vec3& b, float t)
		{
			return  a + (b - a) * t;
		}
		void BaseCameraControllerComponent::Focus(glm::vec3 _target, float _distance)
		{
			glm::vec3 target_direction = glm::normalize(_target - m_CurrentPosition);

			m_FinalPosition = _target - (target_direction * _distance);

			// Update the camera's pitch and yaw based on the new direction vector
			m_Camera->m_Pitch = glm::degrees(asin(target_direction.y));
			m_Camera->m_Yaw = glm::degrees(atan2(target_direction.z, target_direction.x));

			// Recalculate the camera's front, right, and up vectors
			m_Camera->m_Front = target_direction;
			m_Camera->m_Right = glm::normalize(glm::cross(m_Camera->m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));
			m_Camera->m_Up = glm::normalize(glm::cross(m_Camera->m_Right, m_Camera->m_Front));
		}
		glm::vec3 BaseCameraControllerComponent::GetFinalPosition() { return m_FinalPosition; }
		glm::vec3 BaseCameraControllerComponent::GetCurrentPosition() { return m_CurrentPosition; };
		bool BaseCameraControllerComponent::MousePosition(OECore::MouseMovedEvent& e)				{ return false; };
		bool BaseCameraControllerComponent::KeyPessed(OECore::KeyPressedEvent& e)					{ return false; };
		bool BaseCameraControllerComponent::KeyRepeat(OECore::KeyRepeatEvent& e)					{ return false; }
		bool BaseCameraControllerComponent::KeyRelease(OECore::KeyReleaseEvent& e)					{ return false; };
		bool BaseCameraControllerComponent::MouseKeyPressed(OECore::MouseButtonPressedEvent& e)		{ return false; };
		bool BaseCameraControllerComponent::MouseKeyRelease(OECore::MouseButtonReleaseEvent& e)		{ return false; };
		bool BaseCameraControllerComponent::MouseOnScroll(OECore::MouseScrolledEvent& e)			{ return false; };
		bool BaseCameraControllerComponent::WindowResize(OECore::WindowResizeEvent& e)				{ return false; };
	}
}