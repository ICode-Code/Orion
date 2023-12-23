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
			if (tex.HasColor)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Color.first, "Color", MaterialType::DIFFUSE);
				ImGui::NextColumn();
			}
			
			if (tex.HasNormal)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Normal.first, "Normal", MaterialType::NORMAL);
				ImGui::NextColumn();
			}


			if (tex.HasMetal)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Metal.first, "Metal", MaterialType::METAL);
				ImGui::NextColumn();
			}

			if (tex.HasRoughness)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Roughness.first, "Roughness", MaterialType::ROUGHNESS);
				ImGui::NextColumn();
			}

			if (tex.HasMetalRougness)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().MetalRougness.first, "Roughness & Metal", MaterialType::METAL_ROUGHNESS);
				ImGui::NextColumn();
			}

			if (tex.HasAO)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().AO.first, "AO", MaterialType::AO);
				ImGui::NextColumn();
			}

			if (tex.HasEmission)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Emission.first, "Emission", MaterialType::EMISSIVE);
				ImGui::NextColumn();
			}

			if (tex.HasAlpha)
			{
				PaintTexture(m_Framebuffer->GetTextureAttachment().Alpha.first, "Alpha", MaterialType::ALPHA);
				ImGui::NextColumn();
			}

			

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

				std::string albedo_bt_name = "Albedo";
				tex.HasColor ? albedo_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(albedo_bt_name.c_str(), button_size))
				{

				}

				std::string normal_bt_name = "Normal";
				tex.HasNormal ? normal_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(normal_bt_name.c_str(), button_size))
				{

				}

				std::string metal_bt_name = "Metal";
				tex.HasMetal ? metal_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(metal_bt_name.c_str(), button_size))
				{

				}

				std::string Roughness_bt_name = "Roughness";
				tex.HasRoughness ? Roughness_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(Roughness_bt_name.c_str(), button_size))
				{

				}

				std::string Roughness_metal_bt_name = "Roughness-Metal";
				tex.HasMetalRougness ? Roughness_metal_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(Roughness_metal_bt_name.c_str(), button_size))
				{

				}

				std::string ambient_occlu_bt_name = "Ambient Occlusion";
				tex.HasAO ? ambient_occlu_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(ambient_occlu_bt_name.c_str(), button_size))
				{

				}

				std::string emission_bt_name = "Emission";
				tex.HasEmission ? emission_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(emission_bt_name.c_str(), button_size))
				{

				}

				std::string alpha_bt_name = "Alpha Mask";
				tex.HasAlpha ? alpha_bt_name.append(" [overwrite]") : "";

				if (ImGui::Button(alpha_bt_name.c_str(), button_size))
				{

				}

				ImGui::PopStyleVar(2);

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
			
				printf(package->GetName().c_str());
				printf("\n");

				CommandDef::MaterialtextureUpdateCommandDef command;
				command.Material = m_Material;
				command.TextureType = _type;
				command.NewTexture = AssetManager::GetTexture(Loader::NameHandle::FilterFileName(package->GetName()));
				command.IsColor = ((_type == MaterialType::DIFFUSE) || (_type == MaterialType::EMISSIVE));
				
				Command::PushMaterialTextureUpdateCommand(command);
				
				
			}

			ImGui::EndDragDropTarget();
		}

		PrintTextureName(_name);
	}
}