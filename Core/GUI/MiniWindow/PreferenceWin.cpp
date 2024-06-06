#include "PreferenceWin.h"
#include "../../Core/Scene/SceneManager.h"

namespace OE1Core
{
	PreferenceWin::PreferenceWin()
	{
		m_Lables.push_back(ICON_FA_SLIDERS"\tGeneral");
		m_Lables.push_back(ICON_FA_BRUSH"\tPostprocess");
		m_Lables.push_back(ICON_FA_SUN"\tLight Room");
		m_Lables.push_back(ICON_FA_APPLE_WHOLE"\tPhysics");
		m_Lables.push_back(ICON_FA_HASHTAG"\tGrid");
	}
	PreferenceWin::~PreferenceWin()
	{

	}

	void PreferenceWin::PushStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 7 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);

		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, { 0.7f, 0.7f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0.7f, 0.7f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_Header, { 0.13f, 0.13f, 0.13f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_CheckMark, { 0.8f, 0.8f, 0.8f, 1.0f });
		ImGui::NewLine();
	}

	void PreferenceWin::PopStyle()
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();


		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}

	void PreferenceWin::PreviewItemPushStyle(ImVec4 _col)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, _col);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });
	}
	void PreferenceWin::PreviewItemPopStyle()
	{
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}

	void PreferenceWin::Update()
	{

	}
	void PreferenceWin::Render()
	{
		if (!PreferenceWin::s_ShouldOpen) return;

		m_Scene = SceneManager::GetActiveScene();
		if (!m_Scene) return;

		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 7, 8 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 14, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { .5f, .5f });

		ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.078f, 0.078f , 0.078f, 1.0f });


		ImGui::Begin(ICON_FA_GEAR"\tPreference", &PreferenceWin::s_ShouldOpen, s_BaseWinFlag | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDocking);
		static size_t selected = 0;

		ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, { 0.1f, 0.5f });
		ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { 0.5f, 0.5f });
		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 3, 12 });


		ImGui::PushStyleColor(ImGuiCol_Header, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 0.0f, 0.439f, 0.878f, 1.0f });


		ImGui::BeginChild("left pane", ImVec2(200, 0), true);
		ImGui::NewLine();
		for (size_t i = 0; i < m_Lables.size(); i++)
		{
			if (ImGui::Selectable(m_Lables[i].c_str(), selected == i))
				selected = i;
		}

		ImGui::EndChild();


		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();

		ImGui::SameLine();


		ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5);
		ImGui::BeginGroup();
		ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us

		PushStyle();

		switch (selected)
		{
			case 0: General();		break;
			case 1:	PostProcess();  break;
			case 2: LightRoom();	break;
			case 3: Physics();		break;
			case 4: Grid();			break;
			default:				break;
		}

		PopStyle();

		ImGui::EndChild();
		ImGui::EndGroup();
		ImGui::PopStyleVar();


		ImGui::End();





		ImGui::PopStyleColor();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	void PreferenceWin::PrintPreviewItemName(const char* _name)
	{
		float textWidth = ImGui::CalcTextSize(_name).x;
		float columnWidth = ImGui::GetContentRegionAvail().x;
		float offset = (columnWidth - textWidth) * 0.5f;
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
		ImGui::TextWrapped(_name);
	}

	void PreferenceWin::PostProcess()
	{
		if (ImGui::TreeNodeEx("PostProcess", m_Flag))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });


			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
	}
	void PreferenceWin::LightRoom()
	{

		m_CellSize = m_ThumbnailSize + m_Padding;
		m_MaxPanelWidth = ImGui::GetContentRegionAvail().x;
		m_ColumnCount = (int)(m_MaxPanelWidth / m_CellSize);
		if (m_ColumnCount < 1)
			m_ColumnCount = 1;


		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });

		if (ImGui::TreeNodeEx("World Lighting", m_Flag))
		{


			if (CustomFrame::UIEditorFloat("World Light Strength", &m_Scene->m_EnvVarBuffer.WorldLightIntensity, 0.01f, 16.0f))
				m_Scene->UpdateEnvVar();
			if (CustomFrame::UIEditorFloat("Gamma", &m_Scene->m_EnvVarBuffer.Gamma, 0.01f, 4.0f))
				m_Scene->UpdateEnvVar();
			if (CustomFrame::UIEditorFloat("Fresnel", &m_Scene->m_EnvVarBuffer.Fresnel, 0.01f, 0.5f))
				m_Scene->UpdateEnvVar();
			if (CustomFrame::UIEditorFloat("Exposure", &m_Scene->m_EnvVarBuffer.Exposure, 0.01f, 5.0f))
				m_Scene->UpdateEnvVar();

			
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Indirect Light", m_Flag))
		{

			m_HDRItemSelectID = 0;

			ImGui::Columns(m_ColumnCount, "hdr_list", false);

			for (auto& hdr_iter : m_Scene->m_LightRoomManager->GetSpeculars()->m_PrefilteredReflectionMaps)
			{

				ImGui::PushID(m_HDRItemSelectID++);

				PreviewItemPushStyle();
				GLuint __preview = m_Scene->m_LightRoomManager->GetSpeculars()->GetPrefilteredPreviewReflectionMap(hdr_iter.first);
				bool _reg_click = ImGui::ImageButton((ImTextureID)(uintptr_t)__preview, { m_ThumbnailSize, m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
				PreviewItemPopStyle();

				if (_reg_click)
				{
					m_Scene->SetLightRoom(
						m_Scene->m_LightRoomManager->GetDiffuseIrradiance()->GetIrradianceMap(hdr_iter.first),
						hdr_iter.second,
						0
					);
				}


				PrintPreviewItemName(hdr_iter.first.c_str());

				ImGui::NextColumn();
				ImGui::PopID();
			}

			ImGui::Columns(1);
			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Sky Dom", m_Flag))
		{
			auto& cube_map_reg = AssetManager::GetCubeMapTextureRegistry();
			m_SkyBoxItemSelectID = 0;

			ImGui::Columns(m_ColumnCount, "sky_dom_list", false);

			for (auto& cube_map : cube_map_reg)
			{
				ImGui::PushID(m_SkyBoxItemSelectID++);
				PreviewItemPushStyle();
				
				bool _reg_click = ImGui::ImageButton((ImTextureID)(uintptr_t)cube_map.second->GetPreview(), { m_ThumbnailSize, m_ThumbnailSize }, { 0, 1 }, { 1, 0 });
				PreviewItemPopStyle();
				if (_reg_click)
				{
					m_Scene->m_LightRoom->m_ActiveCubeMap = cube_map.second;
				}

				PrintPreviewItemName(cube_map.first.c_str());

				ImGui::NextColumn();
				ImGui::PopID();
			}

			ImGui::Columns(1);
			ImGui::TreePop();
		}

		ImGui::PopStyleVar();
	}
	void PreferenceWin::Grid()
	{
		if (ImGui::TreeNodeEx("Grid", m_Flag))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });


			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
	}
	void PreferenceWin::General()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });
		if (ImGui::TreeNodeEx("General", m_Flag))
		{
			
			CustomFrame::UIEditorCheckbox("Render Thread for Animation", &m_Scene->m_UseActiveThreadForAnimation);


			ImGui::TreePop();
		}
		if (ImGui::TreeNodeEx("Editor Camera", m_Flag))
		{
			ImGui::Indent(m_Indent);

			if (ImGui::TreeNodeEx("Motion", m_Flag))
			{
				ImGui::Indent(m_Indent);

				CustomFrame::UIEditorFloat("Speed", &m_Scene->m_MasterSceneCamera->Controller->m_Speed, 1.0f, 256.0f);
				CustomFrame::UIEditorFloat("Speed Factor", &m_Scene->m_MasterSceneCamera->Controller->m_SpeedFactor, 1.0f, 256.0f);
				CustomFrame::UIEditorFloatDrag("Sensitivity", &m_Scene->m_MasterSceneCamera->Controller->m_Sensitivity, 0.003f, 0.001f, 1.0f, "%.3f", 0);
				CustomFrame::UIEditorFloat("Smoothness", &m_Scene->m_MasterSceneCamera->Controller->m_LerpThreshold, 1.0f, 64.0f);

				ImGui::Indent(-m_Indent);
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("View", m_Flag))
			{
				ImGui::Indent(m_Indent);

				CustomFrame::UIEditorInt("Field of View", &m_Scene->m_MasterSceneCamera->Camera->m_FieldOfView, 35, 120);
				
				ImGui::Indent(-m_Indent);
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Clipping", m_Flag))
			{
				ImGui::Indent(m_Indent);

				CustomFrame::UIEditorFloatDrag("Near", &m_Scene->m_MasterSceneCamera->Camera->m_Near, 1.0f, 0.001f, 64.0f, "%.3f");
				CustomFrame::UIEditorFloatDrag("Far", &m_Scene->m_MasterSceneCamera->Camera->m_Far, 1.0f, 65, 1000000.0f, "%.3f");

				ImGui::Indent(-m_Indent);
				ImGui::TreePop();
			}
			

			ImGui::Indent(-m_Indent);
			ImGui::TreePop();
		}

		ImGui::PopStyleVar();
	}
	void PreferenceWin::Physics()
	{
		if (ImGui::TreeNodeEx("Physics", m_Flag))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });


			ImGui::PopStyleVar();
			ImGui::TreePop();
		}
	}
}