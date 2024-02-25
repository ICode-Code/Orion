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

		ImGui::PushItemWidth(200);
		
		
		if (Loader::IVLoadedAsset::s_TotalRegistedTexture != Loader::IVLoadedAsset::s_TotalRelaesedTexture)
		{
			ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 1.0f, 0.2f, 1.0f });
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });

			ImGui::TextWrapped(ICON_FA_TRIANGLE_EXCLAMATION"\tScanned Texture [%i] - Freed Texture [%i]\n", Loader::IVLoadedAsset::s_TotalRegistedTexture, Loader::IVLoadedAsset::s_TotalRelaesedTexture);
			

			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 0.5f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });

			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_ARROWS_ROTATE, { 20, 15 }))
				Loader::IVLoadedAsset::FreeUnusedTexture();

			ImGui::PopStyleVar();
			ImGui::PopStyleColor(4);
			if (ImGui::IsItemHovered())
			{
				ImGui::SetTooltip("Attention required! Just Click here! If it is in loading process ...[DON'T FUCKING TOUCH THIS]");
			}

			ImGui::PopStyleVar();
			ImGui::PopStyleColor();

		}

		ImGui::PopItemWidth();
		
		ImGui::Separator();


		auto& _texture_list = AssetManager::GetTextureRegistry();
		for (auto iter = _texture_list.begin(); iter != _texture_list.end(); iter++)
		{
			ImageWithName(iter->second->GetTexture(), iter->second->GetName());

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				Texture* package_payload = iter->second;

				ImGui::SetDragDropPayload(ORI_TEXTURE_PACKAGE_PAYLOAD, package_payload, sizeof(Texture));

				ImGui::EndDragDropSource(); 
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