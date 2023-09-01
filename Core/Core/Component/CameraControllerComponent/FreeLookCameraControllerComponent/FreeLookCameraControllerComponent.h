#ifndef OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_
#define OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_

#include "../BaseCameraControllerComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class FreeLookCameraControllerComponent : public BaseCameraControllerComponent
		{
		public:
			FreeLookCameraControllerComponent(GLFWwindow* _window);
			~FreeLookCameraControllerComponent() = default;


			void OnEvent(Event& e) override;
			void UpdateCameraView() override;
			void UpdateInput(float _dt) override;


		protected:
			virtual void HandleKeyInput() override;

		protected:
			bool MousePosition(MouseMovedEvent& e) override;
			bool KeyPessed(KeyPressedEvent& e) override;
			bool KeyRelease(KeyReleaseEvent& e) override;
			bool KeyRepeat(KeyRepeatEvent& e) override;
			bool MouseKeyPressed(MouseButtonPressedEvent& e) override;
			bool MouseKeyRelease(MouseButtonReleaseEvent& e) override;
			bool MouseOnScroll(MouseScrolledEvent& e) override;

		};
	}
}

#endif // !OE1_FREE_LOOK_CAMERA_CONTROLLER_COMPONENT_H_
