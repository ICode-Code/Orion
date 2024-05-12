#include "DynamicViewport.h"
#include "../../../Core/Scene/Entity.h"
#include "LogUI.h"


namespace OE1Core
{
	DynamicViewport::DynamicViewport(Component::CameraComponent* _camera, std::string _name, Entity _entity)
	{
		m_Entity = _entity;
		m_TransformComponent = &m_Entity.GetComponent<Component::TransformComponent>();

		m_Camera = _camera;
		m_Tag = _name;
		m_Name = ICON_FA_VIDEO"		";
		m_Name.append(_name).append("@").append("VIEW-POINT");
		m_ViewportSize = { 700, 500};
	}
	DynamicViewport::~DynamicViewport()
	{

	}

	void DynamicViewport::Update()
	{
		m_Entity.Update();

		UpdateViewport(); 
	}
	void DynamicViewport::Render()
	{
		if (!m_Open)
		{
			if (!m_PurgeCommandSent)
				SendPurgeCommand();
			return;
		}
		ImGui::SetNextWindowSizeConstraints(ImVec2(
			(float)Renderer::Policy::MIN_RESOLUTION_X, 
			(float)Renderer::Policy::MIN_RESOLUTION_Y
		), 
			ImVec2(
				(float)Renderer::Policy::MAX_RESOLUTION_X, 
				(float)Renderer::Policy::MAX_RESOLUTION_Y)
		);
		ImGui::Begin(m_Name.c_str(), &m_Open, m_LocalViewportFlags);
		Update();

		ImGui::SetCursorPos({ 0.0f, 0.0f });
		m_Offset = ImGui::GetCursorPos();

		ImGui::Image((ImTextureID)(intptr_t)m_Camera->GetRenderedScene(), m_ViewportSize, { 0, 1 }, { 1, 0 });


		ShowMinActionButton();

		ImGui::End();
		
	}
	void DynamicViewport::OnEvent(OECore::IEvent& e)
	{

	}
	bool DynamicViewport::IsOpen() { return m_Open; }
	void DynamicViewport::Open() { m_Open = true; }
	void DynamicViewport::Close() { m_Open = false; };
	void DynamicViewport::SendPurgeCommand()
	{
		// Turn off the camera
		m_Camera->SetPowerState(CameraParameter::CAMERA_POWER_STATE::OFF);
		m_Camera->SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE::IDEL);

		CommandDef::PurgeDynamicViewportCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
		command.Name = m_Tag;
		Command::PushDynamicViewportPurgeCommand(command);
		m_PurgeCommandSent = true;
	}
	void DynamicViewport::ShowMinActionButton()
	{
		// Get Aveil Window Size
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();


		// Set Position to Begain Draw
		ImGui::SetCursorPos({ 10.0f, vMin.y });

		m_ActionButton.OpenDefaultActionButtonStyle();

		std::string ButtonName;
		if (m_Camera->GetFlightState() == CameraParameter::CAMERA_FLIGHT_STATE::PILOT)
		{
			ButtonName = ICON_FA_PLANE_LOCK" ";
		}
		else
		{
			ButtonName = ICON_FA_PLANE_DEPARTURE" ";
		}
		ButtonName.append("Pilot Camera  ");
		
		if (ImGui::Button(ButtonName.c_str(), {100.0f, 0.0f}))
		{
				SceneManager::GetActiveScene()->m_CameraManager->EngagePilotMode(m_Camera->GetID());

			if (!m_Camera->GetController())
				LogLayer::Pipe("Camera cannot be piloted: No attached controller found.", OELog::CRITICAL);
		}

		ImGui::SameLine();

		if (m_Camera->GetPowerState() == CameraParameter::CAMERA_POWER_STATE::ON)
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.3f, 0.9f, 0.3f, 1.0f });
		else 
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.9f, 0.3f, 0.3f, 1.0f });

		if (ImGui::Button(ICON_FA_POWER_OFF, { 30.0f, 0.0f }))
		{
			if (m_Camera->GetPowerState() == CameraParameter::CAMERA_POWER_STATE::ON)
				m_Camera->SetPowerState(CameraParameter::CAMERA_POWER_STATE::OFF);
			else 
				m_Camera->SetPowerState(CameraParameter::CAMERA_POWER_STATE::ON);
		}

		ImGui::PopStyleColor();


		m_ActionButton.CloseDefaultActionButtonStyle();
	}

	void DynamicViewport::UpdateViewport()
	{
		m_IsMouseOverViewPort = ImGui::IsWindowHovered();
		ImVec2 current_size = ImGui::GetWindowSize();
		if ((m_ViewportSize.x == current_size.x) && m_ViewportSize.y == current_size.y)
			return;
		m_ViewportSize = current_size;
		m_Camera->UpdateRenderFrameSize((int)m_ViewportSize.x, (int)m_ViewportSize.y);
	}
}