#include "CustomFrame.h"




bool OE1Core::CustomFrame::UIEditorDropdown(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::Combo(_lab.c_str(), current_item, items_separated_by_zeros, height_in_items);
	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::SliderScalar(_lab.c_str(), ImGuiDataType_Float, v, &v_min, &v_max, format, flags);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorFloatDrag(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::DragScalar(_lab.c_str(), ImGuiDataType_Float, v, v_speed, &v_min, &v_max, format, flags);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::SliderScalar(_lab.c_str(), ImGuiDataType_S32, v, &v_min, &v_max, format, flags);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorColor3(const char* label, float col[3], ImGuiColorEditFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);

	bool _rt = ImGui::ColorEdit4(_lab.c_str(), col, flags | ImGuiColorEditFlags_NoAlpha);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorf3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, float power, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::DragFloat3(_lab.c_str(), v, v_speed, v_min, v_max, format);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorColor4(const char* label, float col[4], ImGuiColorEditFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);

	bool _rt = ImGui::ColorEdit4(_lab.c_str(), col, flags | ImGuiColorEditFlags_NoAlpha);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorDragf2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);

	bool _rt = ImGui::DragScalarN(_lab.c_str(), ImGuiDataType_Float, v, 2, v_speed, &v_min, &v_max, format, flags);

	ImGui::Columns(1);
	return _rt;
}

bool OE1Core::CustomFrame::UIEditorCheckbox(const char* label, bool* v, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	bool _rt = ImGui::Checkbox(_lab.c_str(), v);

	ImGui::Columns(1);
	return _rt;
}

void OE1Core::CustomFrame::UIEditorLabel(const char* lable, std::string _tool_tip)
{
	ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Button(lable);
	if (!_tool_tip.empty())
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(_tool_tip.c_str());
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void OE1Core::CustomFrame::UIEditorTextValue(const char* label, const char* value, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();
	std::string _lab = "##";
	_lab.append(label);
	ImGui::Text(value);
	ImGui::Columns(1);
}

void OE1Core::CustomFrame::UIEditorImage(const char* label, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col, float width)
{
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, width);
	UIEditorLabel(label);

	ImGui::NextColumn();

	ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);

	ImGui::Columns(1);
}
