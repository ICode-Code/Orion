#include "ActionButtonModeGroup.h"


namespace OE1Core
{
	ActionButtonModeGroup::ActionButtonModeGroup()
	{
		m_Mode = std::make_pair(ImGuizmo::MODE::WORLD, new VPNavButton(ICON_FA_EARTH_AFRICA));
		m_Snap = std::make_pair(true, new VPNavButton(ICON_FA_MAGNET));
	}
	ActionButtonModeGroup::~ActionButtonModeGroup()
	{
		delete std::get<1>(m_Mode);
		delete std::get<1>(m_Snap);
	}

	void ActionButtonModeGroup::Draw(ImGuizmo::MODE& _mode, bool& _snap, float& _snap_position, float& _snap_rotation)
	{
		OpenDefaultActionButtonStyle();

		DrawButton(m_Mode, _mode);
		ImGui::SameLine();
		DrawButton(m_Snap, _snap);

		ImGui::SetNextWindowSize(ImVec2(200.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
		if (ImGui::BeginPopup("Snap_Value_Setting"))
		{
			CustomFrame::UIEditorFloat("Translation", &_snap_position, 1.0f, 128.0f, "%.0f", 0, 100.0f);
			CustomFrame::UIEditorFloat("Angle", &_snap_rotation, 1.0f, 180.0f, "%.0f", 0, 100.0f);

			ImGui::EndPopup();
		}
		ImGui::PopStyleColor();


		CloseDefaultActionButtonStyle();
	}
	void ActionButtonModeGroup::DrawButton(std::pair<ImGuizmo::MODE, VPNavButton*>& _button, ImGuizmo::MODE& _mode)
	{
		bool type_matched = (_mode == std::get<0>(_button));

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);


		if (std::get<1>(_button)->Draw())
		{
			if (_mode == ImGuizmo::MODE::WORLD)
				_mode = ImGuizmo::MODE::LOCAL;
			else
				_mode = std::get<0>(_button);
		}

		if (type_matched)
			ImGui::PopStyleColor();
	}
	void ActionButtonModeGroup::DrawButton(std::pair<bool, VPNavButton*>& _button, bool& _snap)
	{
		bool type_matched = (_snap == std::get<0>(_button));

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);


		if (std::get<1>(_button)->Draw())
		{
			_snap = !_snap;
			ImGui::OpenPopup("Snap_Value_Setting");
		}

		if (type_matched)
			ImGui::PopStyleColor();
	}
}