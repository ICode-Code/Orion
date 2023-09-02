#ifndef OE1_CAMERA_PACKAGE_H_
#define OE1_CAMERA_PACKAGE_H_

#include "../Component/CameraControllerComponent/FreeLookCameraControllerComponent/FreeLookCameraControllerComponent.h"
#include "UniformBuffer/UniformBlockManager.h"
namespace OE1Core
{
	class CameraPackage
	{
	public:
		CameraPackage(GLFWwindow* _window);
		~CameraPackage();

		Component::CameraComponent* GetCamera();
		Component::FreeLookCameraControllerComponent* GetController();
		void Update(float _dt);
		void OnEvent(Event& e);
		Memory::SceneTransfrom& GetSceneTransform();


	protected:
		Memory::SceneTransfrom m_SceneTransform;
		Component::CameraComponent* m_Camera = nullptr;
		Component::FreeLookCameraControllerComponent* m_Controller;
	};
}

#endif // !OE1_CAMERA_PACKAGE_H_
