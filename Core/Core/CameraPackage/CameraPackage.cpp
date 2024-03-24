#include "CameraPackage.h"

namespace OE1Core
{
	CameraPackage::CameraPackage(SDL_Window* _window, CAMERA_TYPE _type, std::string _name)
	{
		m_Name = _name;
		m_Camera = new Component::CameraComponent();
		m_CameraType = _type;


		// Init-Framebuffer
		m_MainPassFramebuffer = new Renderer::IVForwardMainPassFramebuffer(Renderer::IVFrameSize::R_1k);
	}
	CameraPackage::~CameraPackage()
	{
		delete m_Camera;
		delete m_MainPassFramebuffer;
	}
	Component::CameraComponent* CameraPackage::GetCamera() { return m_Camera; }
	void CameraPackage::Update(float _dt)
	{ 
		//if(IsPilotMode())
		if (m_BaseCameraController)
			m_BaseCameraController->UpdateInput(_dt);

		m_SceneTransform.CameraPosition = m_Camera->GetPosition();
		m_SceneTransform.Projection = m_Camera->m_Projection;
		m_SceneTransform.View = m_Camera->m_View;
		m_SceneTransform.PV = m_Camera->m_Projection * m_Camera->m_View;
		m_SceneTransform.Delta = _dt;
	};
	void CameraPackage::Update(int _width, int _height)
	{
		if (!Renderer::Policy::ValidateResolution(_width, _height))
			return;

		m_Camera->SetResolution(glm::vec2((float)_width, (float)_height));
		m_MainPassFramebuffer->Update(_width, _height);
	}
	void CameraPackage::AttachFramebuffer(bool _clean_buffer, GLenum _usage)
	{
		m_MainPassFramebuffer->Attach(_clean_buffer, _usage);
	}
	void CameraPackage::DetachFramebuffer()
	{
		m_MainPassFramebuffer->Detach();
	}
	bool CameraPackage::UpdateBufferOffset(GLintptr _offset)
	{
		return false;
	}
	Memory::SceneTransfrom& CameraPackage::GetSceneTransform()
	{
		return m_SceneTransform;
	}

	Component::BaseCameraControllerComponent* CameraPackage::GetCameraController()
	{
		return m_BaseCameraController;
	}
	Component::BaseCameraControllerComponent* CameraPackage::SetCameraController(Component::BaseCameraControllerComponent* _controller)
	{
		return m_BaseCameraController = _controller;
	}

	void CameraPackage::OnEvent(OECore::IEvent& e) 
	{ 
		if(m_BaseCameraController)
			m_BaseCameraController->OnEvent(e); 
	}
	GLuint CameraPackage::GetRenderedScene() { return m_MainPassFramebuffer->GetAttachment(0); }
	std::string CameraPackage::GetName() { return m_Name; }
	Renderer::IVForwardMainPassFramebuffer* CameraPackage::GetMainPassFramebuffer()
	{
		return m_MainPassFramebuffer;
	}
	CAMERA_TYPE CameraPackage::GetType() { return m_CameraType; };
	void CameraPackage::PowerOn() { m_PowerState = CameraState::Power::ON; }
	void CameraPackage::PowerOff() { m_PowerState = CameraState::Power::OFF; }
	CameraState::Power CameraPackage::GetPowerState() { return m_PowerState; }
	bool CameraPackage::IsPowerOn() { return m_PowerState == CameraState::Power::ON; }

	void CameraPackage::ActivatePilotCamera() { m_FlightState = CameraState::FlightState::PILOT; }
	void CameraPackage::DeactivatePilotMode() { m_FlightState = CameraState::FlightState::REST; }
	bool CameraPackage::IsPilotMode() { return m_FlightState == CameraState::FlightState::PILOT;};

	void CameraPackage::SetParentEntityID(uint32_t _id)
	{
		m_HasParentEntityID = true;
		m_ParentEntityID = _id;
	}
	uint32_t CameraPackage::GetParentEntity() { return m_ParentEntityID; }
	bool CameraPackage::HasParentEntity()
	{
		return m_HasParentEntityID;
	}
}