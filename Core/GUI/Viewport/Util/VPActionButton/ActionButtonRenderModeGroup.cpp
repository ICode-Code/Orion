#include "ActionButtonRenderModeGroup.h"

namespace OE1Core
{
	ActionButtonRenderModeGroup::ActionButtonRenderModeGroup()
	{
		m_LitPass = std::make_pair(RenderMode::LIT, new VPNavButton(ICON_FA_LIGHTBULB));
		m_MaterialPass = std::make_pair(RenderMode::MATERIAL, new VPNavButton(ICON_FA_CUBE));
		m_WireFrame = std::make_pair(RenderMode::XRAY, new VPNavButton(ICON_FA_CIRCLE_NODES));
	}
	ActionButtonRenderModeGroup::~ActionButtonRenderModeGroup()
	{
		delete std::get<1>(m_LitPass);
		delete std::get<1>(m_MaterialPass);
		delete std::get<1>(m_WireFrame);
	}

	void ActionButtonRenderModeGroup::Draw(RenderMode& _render_mode)
	{
		OpenDefaultActionButtonStyle();

		DrawButton(m_LitPass, _render_mode);
		ImGui::SameLine();
		DrawButton(m_MaterialPass, _render_mode);
		ImGui::SameLine();
		DrawButton(m_WireFrame, _render_mode);

		CloseDefaultActionButtonStyle();
	}
	void ActionButtonRenderModeGroup::DrawButton(std::pair<RenderMode, VPNavButton*>& _button, RenderMode& _value)
	{
		bool type_matched = (_value == std::get<0>(_button));

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);


		if (std::get<1>(_button)->Draw())
			_value = std::get<0>(_button);

		if (type_matched)
			ImGui::PopStyleColor();
	}
}