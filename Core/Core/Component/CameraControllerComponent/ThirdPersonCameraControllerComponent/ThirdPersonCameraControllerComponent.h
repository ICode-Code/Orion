#ifndef OE1_THIRD_PERSON_CAMERA_CONTROLLER_COMPONENT_H_
#define OE1_THIRD_PERSON_CAMERA_CONTROLLER_COMPONENT_H_


#include "../../TransformComponent/TransformComponent.h"
#include "../BaseCameraControllerComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class ThirdPersonCameraControllerComponent : public BaseCameraControllerComponent
		{
			friend class InspectorComponent;
			friend class CameraPackageComponent;
			friend class ActionButtonUtilityGroup;
		public:
			ThirdPersonCameraControllerComponent(SDL_Window* _window, Component::TransformComponent* _tranform);
			~ThirdPersonCameraControllerComponent();

			void OnEvent(OECore::IEvent& e) override;
			void UpdateCameraView() override;
			void UpdateInput(float _dt) override;

			void SetTargetTransform(Component::TransformComponent* _tranform);
			Component::TransformComponent* GetTargetTransform();

		protected:
			virtual void HandleKeyInput() override;

		protected:
			bool MousePosition(OECore::MouseMovedEvent& e) override;
			bool MouseOnScroll(OECore::MouseScrolledEvent& e) override;
			bool WindowResize(OECore::WindowResizeEvent& e) override;
			bool MouseKeyPressed(OECore::MouseButtonPressedEvent& e) override;
			bool MouseKeyRelease(OECore::MouseButtonReleaseEvent& e) override;
			bool KeyPessed(OECore::KeyPressedEvent& e) override;
			bool KeyRelease(OECore::KeyReleaseEvent& e) override;


		private:
			Component::TransformComponent* m_TargetTransform = nullptr;

		private: // Control Arg
			float m_DistanceToTarget = 6.0f;
			float m_FocusHeight = m_DistanceToTarget / 2.0f;
			float m_ShiftRightCameraFocus = 0.0f;
			float m_PitchConstrainMax = 65.0f;
			float m_PitchConstrainMin = 0.0f;

			bool m_FullMouseControl = true;
			bool m_FlipMouse = false;
		};
	}
}
#endif // !OE1_THIRD_PERSON_CAMERA_CONTROLLER_COMPONENT_H_
