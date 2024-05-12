#ifndef OE1_INPUT_CONTROLLER_H_
#define OE1_INPUT_CONTROLLER_H_

#include <IEvent/IEvent.h>

namespace OE1Core
{
	namespace Component
	{
		class BaseCameraControllerComponent;
	}
	/// <summary>
	/// This class is a passage for any input update operation 
	/// for any component fopr, anything that is related to input update it happen here!
	/// </summary>
	class InputController
	{
	public:
		InputController(class Scene* _scene);
		~InputController();


		/// <summary>
		/// Any component that need requier event will be updated here
		/// </summary>
		/// <param name="e"></param>
		void OnEventControllerComponent(OECore::IEvent& e);
		void QuickInputUpdateControllerComponent(float _dt);
		

		// Buffer update
		void MasterCameraBufferUpdate(float _dt);
		void ControllerComponentBufferUpdate(float _dt);

		void QuickInputUpdateMasterCamera(float _dt);
		void OnEventMasterCamera(OECore::IEvent& e);


		// Specicifc Camera Controller Update
		void UpdateCameraInput(Component::BaseCameraControllerComponent* _controller, float _dt);

		// Charatcer Controller Component Update
		void ThirdPersonCharacterControllerInputUpdate(float _dt);
		void FirstPersonCharacterControllerInputUpdate(float _dt);


		// Player entity update
		void UpdateActivePlayerEntity();


	private:
		class Scene* m_Scene = nullptr;
	};
}

#endif // !OE1_INPUT_CONTROLLER_H_
