#include "ActionButtonUtilityGroup.h"


namespace OE1Core
{
	ActionButtonUtilityGroup::ActionButtonUtilityGroup()
	{
		m_QuickCamera = std::make_pair(false, new VPNavButton(ICON_FA_VIDEO));
		m_HideTool = std::make_pair(false, new VPNavButton(ICON_FA_EYE_SLASH));
	}
	ActionButtonUtilityGroup::~ActionButtonUtilityGroup()
	{
		delete std::get<1>(m_QuickCamera);
		delete std::get<1>(m_HideTool);
	}

	void ActionButtonUtilityGroup::Draw(bool& _show_action_button, Component::CameraComponent* _camera, Component::BaseCameraControllerComponent* _camera_controller)
	{
		OpenDefaultActionButtonStyle();

		if (std::get<1>(m_QuickCamera)->Draw())
			ImGui::OpenPopup("quick_camera_setting");

		ImGui::SetNextWindowSize(ImVec2(300.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
		if (ImGui::BeginPopup("quick_camera_setting"))
		{

			CustomFrame::UIEditorFloat("Speed", &_camera_controller->m_Speed, 0.1f, 256.0f, "%.3f",0, 100.0f);
			CustomFrame::UIEditorFloat("Factor", &_camera_controller->m_SpeedFactor, 1.0f, 128.0f, "%.3f", 0, 100.0f);
			//CustomFrame::UIEditorFloat("Smoothness", &_camera.m_Controller->m_LerpThreshold, 0.01f, 0.5f, "%.3f", 0, 100.0f);
			CustomFrame::UIEditorInt("FOV", &_camera->m_FieldOfView, 30, 95, "%d", 0, 100);
			CustomFrame::UIEditorf3<glm::vec3>("Position", _camera_controller->m_FinalPosition, 0.0f, 107.0f);
			ImGui::EndPopup();
		}

		ImGui::PopStyleColor();

		ImGui::SameLine();
		if (std::get<1>(m_HideTool)->Draw())
			_show_action_button = !_show_action_button;

		CloseDefaultActionButtonStyle();
	}
}