#include "MaterialViewWin.h"


namespace OE1Core
{
	MaterialViewWin::MaterialViewWin(MasterMaterial* _material)
	{
		m_TextureSize = { 100, 100 };
		m_TextureSizeZoom = { 300, 250 };
		m_Material = _material;
		m_WinName = ICON_FA_CIRCLE_HALF_STROKE"\tMaterial: ";
		m_WinName.append(m_Material->GetName());
		m_Open = true;
		PrepareMaterialView();
	}
	MaterialViewWin::~MaterialViewWin()
	{
		if (m_Framebuffer)
			delete m_Framebuffer;
	}
	void MaterialViewWin::Render()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.087f, 0.087f, 0.087f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });

		ImGui::Begin(m_WinName.c_str(), &m_Open, s_BaseWinFlag);
		Update();

		Renderer::CheckMatPreviewTexture tex;
		// If framebuffer is ready
		if (m_Framebuffer)
		{
			tex = m_Framebuffer->GetCheckMaterialTextureX();

			ImGui::Columns(4, "innerList", false);
			PushTextureViewStyle();
			
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Color.first,			"Color",				MaterialType::DIFFUSE,			tex.HasColor);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Normal.first,			"Normal",				MaterialType::NORMAL,			tex.HasNormal);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Metal.first,			"Metal",				MaterialType::METAL,			tex.HasMetal);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Roughness.first,		"Roughness",			MaterialType::ROUGHNESS,		tex.HasRoughness);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().MetalRougness.first,	"Roughness & Metal",	MaterialType::METAL_ROUGHNESS,	tex.HasMetalRougness);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().AO.first,				"AO",					MaterialType::AO,				tex.HasAO);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Emission.first,			"Emission",				MaterialType::EMISSIVE,			tex.HasEmission);
			TexturePreviewPainter(m_Framebuffer->GetTextureAttachment().Alpha.first,			"Alpha",				MaterialType::ALPHA,			tex.HasAlpha);
			
			
			PopTextureViewStyle();

			ImGui::Columns(1);

			ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0f, 0.5f });
			ImGui::PushStyleColor(ImGuiCol_Button, OE1Core::Gui::s_ThemeColor);
			if (ImGui::Button(ICON_FA_FILE_IMAGE"\tNew Texture", {100, 0}))
				ImGui::OpenPopup("texture_list_popup");
			ImGui::PopStyleColor();
			ImGui::PopStyleVar();
			
			if (ImGui::BeginPopup("texture_list_popup"))
			{
				ImVec2 button_size = { 150, 0 };

				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, {0.0f, 0.5f});
				ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, {1.0f, 1.0f});

				TextureListButton("Albedo",				MaterialType::DIFFUSE,			tex.HasColor,			button_size, m_TextureIssueFlag.ColorMapIssued);
				TextureListButton("Normal",				MaterialType::NORMAL,			tex.HasNormal,			button_size, m_TextureIssueFlag.NormalMapIssued);
				TextureListButton("Metal",				MaterialType::METAL,			tex.HasMetal,			button_size, m_TextureIssueFlag.MetalMapIssued);
				TextureListButton("Roughness",			MaterialType::ROUGHNESS,		tex.HasRoughness,		button_size, m_TextureIssueFlag.RoughnessMapIssued);
				TextureListButton("Roughness-Metal",	MaterialType::METAL_ROUGHNESS,	tex.HasMetalRougness,	button_size, m_TextureIssueFlag.MetalRougnessMapIssued);
				TextureListButton("Ambient Occlusion",	MaterialType::AO,				tex.HasAO,				button_size, m_TextureIssueFlag.AOMapIssued);
				TextureListButton("Emission",			MaterialType::EMISSIVE,			tex.HasEmission,		button_size, m_TextureIssueFlag.EmissionMapIssued);
				TextureListButton("Alpha Mask",			MaterialType::ALPHA,			tex.HasAlpha,			button_size, m_TextureIssueFlag.AlphaMapIssued);
				

				ImGui::PopStyleVar(2);
				 

				if (ImGui::BeginPopup("texture_buffer_mini_selector"))
				{

					auto& _texture_list = AssetManager::GetTextureRegistry();
					for (auto iter = _texture_list.begin(); iter != _texture_list.end(); iter++)
					{
						if (ImageWithName(iter->second->GetTexture(), iter->second->GetName(), iter->second->GetSizeMB()))
						{
							m_TempTextureMemPtr = iter->second;
							AnalizeTextureSelectionFlag(iter->second, m_TempTexType);
							ImGui::CloseCurrentPopup();
						}
					}

					ImGui::EndPopup();
				}

				ImGui::EndPopup();
			}
		}

	
		ImGui::BeginChild("main-win-child");

		{
			ImGui::BeginChild("childL", { ImGui::GetContentRegionAvail().x * 0.5f, 0 }, true);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 1.0f, 3.0f });
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, OE1Core::Gui::s_ThemeColor);

			if (!tex.HasColor)
				CustomFrame::UIEditorColor4("Color", glm::value_ptr(m_Material->GetParameter().Color));

			if (!tex.HasMetalRougness)
			{
				if (!tex.HasRoughness)
					CustomFrame::UIEditorFloat("Roughness", &m_Material->GetParameter().MetalRoughEmissionAlpha.g, 0.0f, 1.0f);
				if (!tex.HasMetal)
					CustomFrame::UIEditorFloat("Metal", &m_Material->GetParameter().MetalRoughEmissionAlpha.r, 0.0f, 1.0f);
			}
			
			CustomFrame::UIEditorFloat("Emission Strength", &m_Material->GetParameter().MetalRoughEmissionAlpha.b, 0.0f, 128.0f);
			
			CustomFrame::UIEditorColor4("Emission Color", glm::value_ptr(m_Material->GetParameter().EmissionColor));
			
			if (!tex.HasAlpha)
				CustomFrame::UIEditorFloat("Alpha", &m_Material->GetParameter().MetalRoughEmissionAlpha.a, 0.0f, 1.0f);
			
			CustomFrame::UIEditorFloat("Base Reflectivity", &m_Material->GetParameter().BaseReflectivity_RF_MF.r, 0.0f, 1.0f, "%.3f");
			

			CustomFrame::UIEditorFloat("Roughness Factor", &m_Material->GetParameter().BaseReflectivity_RF_MF.g, 0.0f, 1.0f, "%.3f");
			ImGui::SameLine();
			ImGui::Text(ICON_FA_QUESTION);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Indicates the overall strength of a material's roughness");

			CustomFrame::UIEditorFloat("Metallic Factor", &m_Material->GetParameter().BaseReflectivity_RF_MF.b, 0.0f, 1.0f, "%.3f");
			ImGui::SameLine();
			ImGui::Text(ICON_FA_QUESTION);
			if (ImGui::IsItemHovered())
				ImGui::SetTooltip("Indicates the overall strength of a material's metalness");

			ImGui::PopStyleColor();
			ImGui::PopStyleVar();

			ImGui::EndChild(); // End Sub-Left Child
		}

		ImGui::SameLine();

		ImGui::BeginChild("childR", {0, 0}, true);

		ImGui::Text("Shader");

		ImGui::EndChild(); // End Sub-Right Child


		ImGui::EndChild(); // end main Child 
		ImGui::End();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();

		
		m_Material->Update();
	}
	void MaterialViewWin::TextureListButton(std::string _name, MaterialType _type, bool _has_texture, ImVec2 _size, bool& _issue_flag)
	{
		_has_texture ? _name.append(" [overwrite]") : "";
		if (ImGui::Button(_name.c_str(), _size))
		{
			m_TextureIssueFlag.Reset();
			m_TempTexType = _type;
			ImGui::OpenPopup("texture_buffer_mini_selector");
			_issue_flag = true;
		}
	}
	bool MaterialViewWin::ImageWithName(GLuint _image, std::string _name, float _size)
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
			ImGui::Image((ImTextureID)(uintptr_t)_image, { 350, 300 });
			ImGui::EndTooltip();
		}
		ImGui::SameLine();

		std::string file_name = _name + " [";
		file_name += std::to_string(_size);
		file_name += " Mib]";
		bool _is_clicked = ImGui::Button(file_name.c_str(), { 250, 0 });

		ImGui::PopStyleColor(3);
		ImGui::PopStyleVar(3);


		return _is_clicked;
	}
	void MaterialViewWin::Update()
	{
		ImGui::SetWindowSize({700,450});
	}
	void MaterialViewWin::PrepareMaterialView()
	{

	}
	void MaterialViewWin::PushTextureViewStyle()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });
	}
	void MaterialViewWin::PopTextureViewStyle()
	{
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}
	void MaterialViewWin::PrintTextureName(const char* _name)
	{
		float textWidth = ImGui::CalcTextSize(_name).x;
		float columnWidth = ImGui::GetContentRegionAvail().x;
		float offset = (columnWidth - textWidth) * 0.5f;
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
		ImGui::TextWrapped(_name);
	}
	void MaterialViewWin::PaintTexture(GLuint& _texture, const char* _name, const MaterialType _type)
	{
		ImGui::ImageButton((ImTextureID)(uintptr_t)_texture, m_TextureSize);
		if (ImGui::IsItemHovered())
		{
			ImGui::BeginTooltip();
			ImGui::Image((ImTextureID)(uintptr_t)_texture, m_TextureSizeZoom);
			ImGui::EndTooltip();
		}


		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(ORI_TEXTURE_PACKAGE_PAYLOAD))
			{
				Texture* package = (Texture*)payload->Data;
			
				CommandDef::MaterialtextureUpdateCommandDef command;
				command.Material = m_Material;
				command.TextureType = _type;
				command.NewTexture = AssetManager::GetTexture(Loader::NameHandle::FilterFileName(package->GetName()));
				
				Command::PushMaterialTextureUpdateCommand(command);

				this->PushUpdateViewCommand();
				
			}

			ImGui::EndDragDropTarget();
		}

		PrintTextureName(_name);
	} 

	void MaterialViewWin::AnalizeTextureSelectionFlag(OE1Core::Texture* _texture, OE1Core::MaterialType _type)
	{
		// Construct a command 
		CommandDef::MaterialtextureUpdateCommandDef command;


		command.Material = m_Material;
		command.TextureType = _type;
		command.NewTexture = AssetManager::GetTexture(Loader::NameHandle::FilterFileName(_texture->GetName()));

		Command::PushMaterialTextureUpdateCommand(command);

		this->PushUpdateViewCommand();

		m_TextureIssueFlag.Reset();
	}

	void MaterialViewWin::TexturePreviewPainter(GLuint _index, std::string _name, MaterialType _type, bool _has_texture)
	{
		if (!_has_texture)
			return;
		PaintTexture(_index, _name.c_str(), _type);
		ImGui::NextColumn();
	}
	void MaterialViewWin::PushUpdateViewCommand()
	{
		// Update View
		CommandDef::MaterialTextureExtractionDef mat_view_update_command;
		mat_view_update_command.Material = m_Material;
		mat_view_update_command.MaterialView = this;
		// Queue command
		Command::PushMaterialTextureExtractionCommand(mat_view_update_command);
	}
}