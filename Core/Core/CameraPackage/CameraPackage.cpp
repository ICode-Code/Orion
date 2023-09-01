#include "CameraPackage.h"


namespace OE1Core
{
	CameraPackage::CameraPackage(GLFWwindow* _window)
	{
		m_Camera = new Component::CameraComponent();
		m_Controller = new Component::FreeLookCameraControllerComponent(_window);
	}
	CameraPackage::~CameraPackage()
	{
		delete m_Camera;
		delete m_Controller;
	}
	Component::CameraComponent* CameraPackage::GetCamera() { return m_Camera; }
	Component::FreeLookCameraControllerComponent* CameraPackage::GetController() { return m_Controller; }
	void CameraPackage::Update(float _dt) { m_Controller->UpdateInput(_dt); };
	void CameraPackage::OnEvent(Event& e) { m_Controller->OnEvent(e); }

}