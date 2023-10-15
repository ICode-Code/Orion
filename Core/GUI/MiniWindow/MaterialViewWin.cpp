#include "MaterialViewWin.h"


namespace OE1Core
{
	MaterialViewWin::MaterialViewWin(MasterMaterial* _material)
	{
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
			ImVec2 text_size = { 100, 100 };
			tex = m_Framebuffer->GetCheckMaterialTextureX();

			ImGui::Columns(4, "innerList", false);
			PushTextureViewStyle();
			if (tex.HasColor)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Color.first, text_size);
				PrintTextureName("Albedo");
				ImGui::NextColumn();
			}
			
			if (tex.HasNormal)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Normal.first, text_size);
				PrintTextureName("Normal");
				ImGui::NextColumn();
			}


			if (tex.HasMetal)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Metal.first, text_size);
				PrintTextureName("Metal");
				ImGui::NextColumn();
			}

			if (tex.HasRoughness)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Roughness.first, text_size);
				PrintTextureName("Roughness");
				ImGui::NextColumn();
			}

			if (tex.HasMetalRougness)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().MetalRougness.first, text_size);
				PrintTextureName("Roughness Metal");
				ImGui::NextColumn();
			}

			if (tex.HasAO)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().AO.first, text_size);
				PrintTextureName("AO");
				ImGui::NextColumn();
			}

			if (tex.HasEmission)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Emission.first, text_size);
				PrintTextureName("Emission");
				ImGui::NextColumn();
			}

			if (tex.HasAlpha)
			{
				ImGui::ImageButton((ImTextureID)(uintptr_t)m_Framebuffer->GetTextureAttachment().Alpha.first, text_size);
				PrintTextureName("Alpha");
				ImGui::NextColumn();
			}

			

			PopTextureViewStyle();

			ImGui::Columns(1);

			static glm::vec3 color = glm::vec3(1.0f);
			static float val = 0.5f;
		}

	
		ImGui::BeginChild("main-win-child");

		{
			ImGui::BeginChild("childL", { ImGui::GetContentRegionAvail().x * 0.5f, 0 }, true);

			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 1.0f, 3.0f });

			if (!tex.HasColor)
				CustomFrame::UIEditorColor4("Color", glm::value_ptr(m_Material->GetParameter().Color));

			if (!tex.HasMetalRougness)
			{
				if (!tex.HasRoughness)
					CustomFrame::UIEditorFloatDrag("Roughness", &m_Material->GetParameter().MetalRoughEmissionAlpha.g, 0.001f, 0.0f, 1.0f);
				if (!tex.HasMetal)
					CustomFrame::UIEditorFloatDrag("Metal", &m_Material->GetParameter().MetalRoughEmissionAlpha.r, 0.001f, 0.0f, 1.0f);
			}
			
			CustomFrame::UIEditorFloatDrag("Emission Strength", &m_Material->GetParameter().MetalRoughEmissionAlpha.b, 0.001f, 0.0f, 128.0f);
			
			CustomFrame::UIEditorColor4("Emission Color", glm::value_ptr(m_Material->GetParameter().EmissionColor));
			
			if (!tex.HasAlpha)
				CustomFrame::UIEditorFloatDrag("Alpha", &m_Material->GetParameter().MetalRoughEmissionAlpha.a, 0.01f, 0.0f, 1.0f);
			
			CustomFrame::UIEditorFloatDrag("Base Reflectivity", &m_Material->GetParameter().BaseReflectivityPadding.r, 0.001f, 0.0f, 1.0f, "%.3f");

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
		ImGui::SetWindowSize({700,400});
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
}