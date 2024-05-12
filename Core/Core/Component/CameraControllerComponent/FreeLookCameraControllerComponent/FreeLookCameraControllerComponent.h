#ifndef OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_
#define OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_

#include "../BaseCameraControllerComponent.h"

namespace OE1Core
{
	class ActionButtonUtilityGroup;
	namespace Component
	{
		class FreeLookCameraControllerComponent : public BaseCameraControllerComponent
		{
			friend class InspectorComponent;
			friend class CameraPackageComponent;
			friend class ActionButtonUtilityGroup;
		public:
			FreeLookCameraControllerComponent(SDL_Window* _window);
			~FreeLookCameraControllerComponent() = default;


			void OnEvent(OECore::IEvent& e) override;
			void UpdateCameraView() override;
			void UpdateInput(float _dt) override;
			void OverrideFinalPosition(glm::vec3 _val, float _dt) override;


		protected:
			virtual void HandleKeyInput() override;
		protected:
			bool MousePosition(OECore::MouseMovedEvent& e) override;
			bool KeyPessed(OECore::KeyPressedEvent& e) override;
			bool KeyRelease(OECore::KeyReleaseEvent& e) override;
			bool KeyRepeat(OECore::KeyRepeatEvent& e) override;
			bool MouseKeyPressed(OECore::MouseButtonPressedEvent& e) override;
			bool MouseKeyRelease(OECore::MouseButtonReleaseEvent& e) override;
			bool MouseOnScroll(OECore::MouseScrolledEvent& e) override;
			bool WindowResize(OECore::WindowResizeEvent& e) override;

		};
	}
}

#endif // !OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_
