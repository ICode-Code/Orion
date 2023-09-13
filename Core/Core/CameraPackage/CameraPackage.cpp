#include "CameraPackage.h"

namespace OE1Core
{
	CameraPackage::CameraPackage(SDL_Window* _window)
	{
		m_Camera = new Component::CameraComponent();
		m_Controller = new Component::FreeLookCameraControllerComponent(_window);
		m_Controller->SetCameraComponent(m_Camera);
	}
	CameraPackage::~CameraPackage()
	{
		delete m_Camera;
		delete m_Controller;
	}
	Component::CameraComponent* CameraPackage::GetCamera() { return m_Camera; }
	Component::FreeLookCameraControllerComponent* CameraPackage::GetController() { return m_Controller; }
	void CameraPackage::Update(float _dt)
	{ 
		m_Controller->UpdateInput(_dt); 

		m_SceneTransform.CameraPosition = m_Camera->GetPosition();
		m_SceneTransform.Projection = m_Camera->m_Projection;
		m_SceneTransform.View = m_Camera->m_View;
		m_SceneTransform.PV = m_Camera->m_Projection * m_Camera->m_View;
		m_SceneTransform.Delta = _dt;
	};
	Memory::SceneTransfrom& CameraPackage::GetSceneTransform()
	{
		return m_SceneTransform;
	}
	void CameraPackage::OnEvent(OECore::IEvent& e) { m_Controller->OnEvent(e); }

}