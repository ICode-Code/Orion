#include "ActionButtonTransformGroup.h"


namespace OE1Core
{
	ActionButtonTransformGroup::ActionButtonTransformGroup()
	{
		m_Bound = std::make_pair(ImGuizmo::OPERATION::BOUNDS, new VPNavButton(ICON_FA_ARROW_POINTER));
		m_Translation = std::make_pair(ImGuizmo::OPERATION::TRANSLATE, new VPNavButton(ICON_FA_ARROWS_UP_DOWN_LEFT_RIGHT));
		m_Rotation = std::make_pair(ImGuizmo::OPERATION::ROTATE, new VPNavButton(ICON_FA_ROTATE));
		m_Scale = std::make_pair(ImGuizmo::OPERATION::SCALE, new VPNavButton(ICON_FA_UP_RIGHT_AND_DOWN_LEFT_FROM_CENTER));
	}
	ActionButtonTransformGroup::~ActionButtonTransformGroup()
	{
		delete std::get<1>(m_Bound);
		delete std::get<1>(m_Translation);
		delete std::get<1>(m_Rotation);
		delete std::get<1>(m_Scale);
	}
	void ActionButtonTransformGroup::Draw(ImGuizmo::OPERATION& _operation)
	{
		OpenDefaultActionButtonStyle();

		DrawButton(m_Bound, _operation);
		ImGui::SameLine();
		DrawButton(m_Translation, _operation);
		ImGui::SameLine();
		DrawButton(m_Rotation, _operation);
		ImGui::SameLine();
		DrawButton(m_Scale, _operation);

		CloseDefaultActionButtonStyle();
	}

	void ActionButtonTransformGroup::DrawButton(std::pair<ImGuizmo::OPERATION, VPNavButton*>& _button, ImGuizmo::OPERATION& _operation)
	{
		bool type_matched = (_operation == std::get<0>(_button));

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);


		if (std::get<1>(_button)->Draw())
			_operation = std::get<0>(_button);

		if (type_matched)
			ImGui::PopStyleColor();
	}
}