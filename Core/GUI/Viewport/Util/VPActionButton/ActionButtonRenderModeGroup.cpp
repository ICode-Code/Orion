#include "ActionButtonRenderModeGroup.h"

namespace OE1Core
{
	ActionButtonRenderModeGroup::ActionButtonRenderModeGroup()
	{
		m_LitPass = std::make_pair(RenderMode::LIT, new VPNavButton(ICON_FA_LIGHTBULB));
		m_MaterialPass = std::make_pair(RenderMode::BASE_COLOR, new VPNavButton(ICON_FA_CUBE));
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
		//DrawButton(m_MaterialPass, _render_mode); 

		if(DrawButton_EXT(m_MaterialPass, _render_mode))
			ImGui::OpenPopup("quick_mat_preview");

		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));

		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10, 6 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.05f, 0.5f });

		if (ImGui::BeginPopup("quick_mat_preview"))
		{
			ImVec2 _size = { 170.0f, 0 };

			if (ImGui::Button("Color", _size))
				_render_mode = RenderMode::BASE_COLOR;
			else if (ImGui::Button("Normal", _size))
				_render_mode = RenderMode::NORMAL;
			else if (ImGui::Button("Metal", _size))
				_render_mode = RenderMode::METAL;
			else if (ImGui::Button("Roughness", _size))
				_render_mode = RenderMode::ROUGHNESS;
			else if (ImGui::Button("Emission", _size))
				_render_mode = RenderMode::EMISSION;
			else if (ImGui::Button("AO", _size))
				_render_mode = RenderMode::AO;
			else if (ImGui::Button("Alpha", _size))
				_render_mode = RenderMode::ALPHA;
			
			
			ImGui::EndPopup();
		}

		ImGui::PopStyleVar(4);
		ImGui::PopStyleColor();

		ImGui::SameLine();
		DrawButton(m_WireFrame, _render_mode);

		CloseDefaultActionButtonStyle();
	}
	bool ActionButtonRenderModeGroup::DrawButton(std::pair<RenderMode, VPNavButton*>& _button, RenderMode& _value)
	{
		bool type_matched = (_value == std::get<0>(_button));

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);

		bool _pushed_button = std::get<1>(_button)->Draw();
		if (_pushed_button)
			_value = std::get<0>(_button);

		if (type_matched)
			ImGui::PopStyleColor();

		return _pushed_button;
	}
	bool ActionButtonRenderModeGroup::DrawButton_EXT(std::pair<RenderMode, VPNavButton*>& _button, RenderMode& _value)
	{
		bool type_matched =
			RenderMode::BASE_COLOR == _value	||
			RenderMode::NORMAL == _value		||
			RenderMode::METAL == _value			||
			RenderMode::ROUGHNESS == _value		||
			RenderMode::EMISSION == _value		||
			RenderMode::AO == _value			||
			RenderMode::ALPHA == _value;

		if (type_matched)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);

		bool _pushed_button = std::get<1>(_button)->Draw();
		if (_pushed_button)
			_value = std::get<0>(_button);

		if (type_matched)
			ImGui::PopStyleColor();

		return _pushed_button;
	}
}