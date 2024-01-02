#include "MinTextureFilterWin.h"


namespace OE1Core
{
	MinTextureFilterWin::MinTextureFilterWin()
	{
		m_LocalSize = ImVec2(320, 300);
	}
	MinTextureFilterWin::~MinTextureFilterWin()
	{

	}

	void MinTextureFilterWin::Open() { s_ShouldOpen = true; }
	void MinTextureFilterWin::Close() { s_ShouldOpen = false; }
	bool MinTextureFilterWin::IsOpen() { return s_ShouldOpen; }


	void MinTextureFilterWin::Render()
	{
		if (!s_ShouldOpen)
			return;
		ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, { 3 });
		ImGui::Begin(ICON_FA_IMAGES"\tTexture Buffer", &s_ShouldOpen, s_BaseWinFlag);
		Update();

		ImGui::Text(ICON_FA_FILTER" Filter...");
		ImGui::SameLine();
		ImGui::PushItemWidth(200);
		static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
		ImGui::InputText("##filterTextureName", s_TextureNameFilterInputBuffer, IM_ARRAYSIZE(s_TextureNameFilterInputBuffer), flags);
		ImGui::PopItemWidth();
		ImGui::Separator();


		auto& _texture_list = AssetManager::GetTextureRegistry();
		for (auto iter = _texture_list.begin(); iter != _texture_list.end(); iter++)
		{
			if (ImageWithName(iter->second->GetTexture(), iter->second->GetName()))
			{

			}
		}

		ImGui::End();
		ImGui::PopStyleVar();
	}

	void MinTextureFilterWin::Update()
	{
		ImGui::SetWindowSize(m_LocalSize);
	}
	bool MinTextureFilterWin::ImageWithName(GLuint _image, std::string _name, float _size)
	{

		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 0, 2 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.1f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.15f, 0.15f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.15f, 0.15f, 0.15f, 1.0f });

		ImGui::Image((ImTextureID)(uintptr_t)_image, { 20, 23 }, { 0, 1 }, { 1, 0 });
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Image((ImTextureID)(uintptr_t)_image, {350, 300});
			ImGui::EndTooltip();
		}
		ImGui::SameLine();

		std::string file_name = _name + " [";
		file_name += std::to_string(_size);
		file_name += " Mib]";
		bool _is_clicked = ImGui::Button(file_name.c_str(), { 285, 0 });

		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar(3);


		return _is_clicked;
	}
}