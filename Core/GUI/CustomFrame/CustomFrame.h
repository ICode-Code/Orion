#ifndef OE1_CUSTOM_FRAME_H_
#define OE1_CUSTOM_FRAME_H_

#include <Gui.h>
#include <string>

namespace OE1Core
{
	class CustomFrame
	{
	public:
		static bool UIEditorDropdown(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items = -1, float width = s_DefaultStyleWidth);
		
		static bool UIEditorFloat(const char* label, float* v, float v_min = 0.0f, float v_max = 1.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0, float width = s_DefaultStyleWidth);
		
		static bool UIEditorFloatDrag(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0, float width = s_DefaultStyleWidth);
		
		static bool UIEditorInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0, float width = s_DefaultStyleWidth);

		static bool UIEditorColor3(const char* label, float col[3], ImGuiColorEditFlags flags = 0, float width = s_DefaultStyleWidth);
		
		static bool UIEditorf3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f, float width = s_DefaultStyleWidth);
		
		static bool UIEditorColor4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, float width = s_DefaultStyleWidth);
		
		static bool UIEditorDragf2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0, float width = s_DefaultStyleWidth);
		
		static bool UIEditorCheckbox(const char* label, bool* v, float width = s_DefaultStyleWidth);
		
		static void UIEditorLabel(const char* lable, std::string _tool_tip = "");
		
		static void UIEditorTextValue(const char* label, const char* value, float width = s_DefaultStyleWidth);
		
		static bool UIEditorPushButton(const char* label, const char* button_name, const ImVec2& size = ImVec2(0, 0), float width = s_DefaultStyleWidth);

		static bool UIEditorImageButton(const char* lable, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0, 0, 0, 0), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), float width = s_DefaultStyleWidth);

		static void UIEditorImage(const char* label, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1), const ImVec4& tint_col = ImVec4(1, 1, 1, 1), const ImVec4& border_col = ImVec4(0, 0, 0, 0), float width = s_DefaultStyleWidth);
		
		template<typename T> static bool UIEditorf3(
			const std::string& lable,
			T& Val,
			float resetValue = 1.0f,
			float columnetWidth = 70.0f);
		inline static ImGuiTreeNodeFlags _Flags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_FramePadding;


	private:
		inline static float s_DefaultStyleWidth = 140.0f;
	};
	template<typename T>
	inline bool CustomFrame::UIEditorf3(const std::string& lable, T& Valus, float resetValue, float columnetWidth)
	{
		bool __return_val = false;
		ImGui::PushID(lable.c_str());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 9.0f, 5.0f });



		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });
		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnetWidth);
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
		ImGui::Button(lable.c_str());
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth() + 50.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		//ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };
		ImVec2 buttonSize = { 3.0f, lineHeight }; // Ex



		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.910f, 0.290f, 0.373f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.810f, 0.190f, 0.273f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.810f, 0.190f, 0.273f, 1.000f });

		if (ImGui::Button("X", buttonSize))
		{
			Valus[0] = resetValue;
			__return_val = true;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##X", &Valus[0], 0.1f, 0.0f, 0.0f, "%.3f"))
			__return_val = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.051f, 0.647f, 0.455f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.041f, 0.547f, 0.355f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.041f, 0.547f, 0.355f, 1.000f });
		if (ImGui::Button("Y", buttonSize))
		{
			Valus[1] = resetValue;
			__return_val = true;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##Y", &Valus[1], 0.1f, 0.0f, 0.0f, "%.3f"))
			__return_val = true;
		ImGui::PopItemWidth();
		ImGui::SameLine();


		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.051f, 0.541f, 0.737f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.041f, 0.441f, 0.637f, 1.000f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.041f, 0.441f, 0.637f, 1.000f });
		if (ImGui::Button("Z", buttonSize))
		{
			Valus[2] = resetValue;
			__return_val = true;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		if (ImGui::DragFloat("##Z", &Valus[2], 0.1f, 0.0f, 0.0f, "%.3f"))
			__return_val = true;
		ImGui::PopItemWidth();


		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::Columns(1);

		ImGui::PopID();

		return __return_val;
	}
}

#endif // !OE1_CUSTOM_FRAME_H_
