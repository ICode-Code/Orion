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

	void ActionButtonModeGroup::Draw(ImGuizmo::MODE& _mode, bool& _snap)
	{
		OpenDefaultActionButtonStyle();

		DrawButton(m_Mode, _mode);
		ImGui::SameLine();
		DrawButton(m_Snap, _snap);


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
			_snap = !_snap;

		if (type_matched)
			ImGui::PopStyleColor();
	}
}