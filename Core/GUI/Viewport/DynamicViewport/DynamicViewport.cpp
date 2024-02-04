#include "DynamicViewport.h"
#include "../../../Core/Scene/Entity.h"


namespace OE1Core
{
	DynamicViewport::DynamicViewport(CameraPackage* _camera, std::string _name)
	{
		m_Camera = _camera;
		m_Name = ICON_FA_VIDEO"		";
		m_Name.append(_name).append("@").append("VIEW-POINT");
		m_ViewportSize = { 700, 500};
	}
	DynamicViewport::~DynamicViewport()
	{

	}

	void DynamicViewport::Update()
	{
		UpdateViewport();
	}
	void DynamicViewport::Render()
	{
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

	void DynamicViewport::ShowMinActionButton()
	{
		// Get Aveil Window Size
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();


		// Set Position to Begain Draw
		ImGui::SetCursorPos({ 10.0f, vMin.y });

		m_ActionButton.OpenDefaultActionButtonStyle();


		if (ImGui::Button(ICON_FA_PLANE_DEPARTURE"	Pilot Camera", { 90.0f, 0.0f }))
		{
			SceneManager::GetActiveScene()->m_CameraManager->EngagePilotMode(m_Camera->GetName());
		}

		m_ActionButton.CloseDefaultActionButtonStyle();
	}

	void DynamicViewport::UpdateViewport()
	{
		m_IsMouseOverViewPort = ImGui::IsWindowHovered();
		ImVec2 current_size = ImGui::GetWindowSize();
		if ((m_ViewportSize.x == current_size.x) && m_ViewportSize.y == current_size.y)
			return;
		m_ViewportSize = current_size;
		m_Camera->Update((int)m_ViewportSize.x, (int)m_ViewportSize.y);
	}
}