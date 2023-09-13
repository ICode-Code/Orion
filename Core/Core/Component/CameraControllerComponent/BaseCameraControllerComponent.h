#ifndef OE1_BASE_CAMERA_CONTROLLER_COMPONENT_H_
#define OE1_BASE_CAMERA_CONTROLLER_COMPONENT_H_

#include <SDL.h>

// Component
#include "../CameraComponent/CameraComponent.h"

#include <glm/glm.hpp>
#include <IEvent/IEvent.h>
 

namespace OE1Core
{
	namespace Component
	{
		class BaseCameraControllerComponent
		{
		public:
			BaseCameraControllerComponent(SDL_Window* _active_context);
			virtual ~BaseCameraControllerComponent() = default;

			virtual void UpdateCameraView() = 0;
			virtual void UpdateInput(float _dt) = 0;
			virtual void OnEvent(OECore::IEvent& _e) = 0;
			virtual void HandleKeyInput() = 0;
		
			//virtual void SetTransform(Component::TransformComponent* _transform);
			virtual void SetCameraComponent(Component::CameraComponent* _camera);

			virtual Component::CameraComponent* GetCameraComponent();
			//virtual Component::TransformComponent* GetTransformComponent();

			virtual void SetControlMouseKey(int _key);
			virtual void LockMouse(bool _lock);
			virtual glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t);
			virtual void Focus(glm::vec3 _target);


		protected: // Event
			virtual bool MousePosition(OECore::MouseMovedEvent& e);
			virtual bool KeyPessed(OECore::KeyPressedEvent& e);
			virtual bool KeyRelease(OECore::KeyReleaseEvent& e);
			virtual bool KeyRepeat(OECore::KeyRepeatEvent& e);
			virtual bool MouseKeyPressed(OECore::MouseButtonPressedEvent& e);
			virtual bool MouseKeyRelease(OECore::MouseButtonReleaseEvent& e);
			virtual bool MouseOnScroll(OECore::MouseScrolledEvent& e);
			virtual bool WindowResize(OECore::WindowResizeEvent& e);


		protected:
			glm::vec3 m_DeltaPosition = glm::vec3(0.0f);
			glm::vec3 m_FinalPosition = glm::vec3(0.0f);
			glm::vec3 m_InitialPosition = glm::vec3(0.0f);
			glm::vec3 m_CurrentPosition = glm::vec3(0.0f);
			glm::vec2 m_LastMousePosition = glm::vec2(0.0f);

			// Flag
			bool m_LockMouseAtCenter = true;
			bool m_IsControlKeyPressed = false;

			// Controller Specific Data
			float m_Sensitivity = 0.03f;
			float m_Speed = 15.0f;
			float m_SpeedFactor = 5.0f;
			float m_DeltaTime = 0.0f;
			float m_DistanceFromFocusTarget = 5.0f;
			int m_ControlKey;
			float m_LerpThreshold = 0.3f;

			// Data
			//Component::TransformComponent* m_Transform = nullptr;
			Component::CameraComponent* m_Camera = nullptr;
		protected:
			const Uint8* m_KeyState = SDL_GetKeyboardState(NULL);
			SDL_Window* m_Window = nullptr;
			int m_WinCenterX = 500;
			int m_WinCenterY = 500;
		};
	}
}

#endif // !OE1_BASE_CAMERA_CONTROLLER_COMPONENT_H_
