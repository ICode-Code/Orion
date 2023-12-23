#include "ContentBrowserLayer.h"

namespace OE1Core
{
	ContentBrowserLayer::ContentBrowserLayer()
	{
		m_FolderIcon = (ImTextureID)(intptr_t)AssetManager::GetInternalTexture("Folder")->GetTexture();
		m_UnknownFileIcon = (ImTextureID)(intptr_t)AssetManager::GetInternalTexture("Unknown")->GetTexture();

		m_ActiveDirectory = ORI_ACTIVE_PATH;
		ORI_PROJECT_HOT_DIRECTORY = ORI_ACTIVE_PATH;

		SyncDataEntry();
		ExecutionHandler::RegisterContentBrowserLayerNotifyCallback(std::bind(&ContentBrowserLayer::SyncDataEntry, this));
	}
	ContentBrowserLayer::~ContentBrowserLayer()
	{
		m_DirEntry.clear();
		m_MusicEntry.clear();
		m_AssetEntry.clear();
		m_MaterialEntry.clear();
		m_ScriptEntry.clear();
		m_TextureEntry.clear();
		m_UnknownFileEntry.clear();
	}
	void ContentBrowserLayer::ContentBrowserMiniOptionPopup()
	{
		ImGui::SetNextWindowSize(ImVec2(270.0f, 60.0f));
		ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.09f, 0.09f, 0.09f, 1.0f));
		if (ImGui::BeginPopup("content_setting"))
		{
			CustomFrame::UIEditorFloat("Padding", &m_Padding, 32, 100, "%.3f", 0, 70);
			CustomFrame::UIEditorFloat("Thumbnail", &m_ThumbnailSize, 32, 100, "%.3f", 0, 70);

			ImGui::EndPopup();
		}
		ImGui::PopStyleColor();
	}
	void ContentBrowserLayer::Render()
	{
		ImGui::Begin(ICON_FA_FOLDER_OPEN"\tContent Browser");
		
		DrawHeader();
		ImGui::Separator();


		m_CellSize = m_ThumbnailSize + m_Padding;
		m_MaxPanelWidth = ImGui::GetContentRegionAvail().x;
		m_ColumnCount = (int)(m_MaxPanelWidth / m_CellSize);
		if (m_ColumnCount < 1)
			m_ColumnCount = 1;

		PathIterator();

		ImGui::End();


	}
	void ContentBrowserLayer::Update()
	{
		
	}

	void ContentBrowserLayer::DrawHeader()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 6, 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 15, 5 });

		ImGui::BeginChild("#content_header", { ImGui::GetContentRegionMax().x, 15.0f }, false, ImGuiWindowFlags_NoBackground);

		//mUtil.RenderImportMenu();


		///////////////////////////////////////////////////////// Navigate Backward if it is not on Base Directory
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });

		ImGui::Text(ICON_FA_LEFT_LONG);
		if (ImGui::IsItemClicked())
		{
			if (m_ActiveDirectory != ORI_ACTIVE_PATH)
			{
				m_ActiveDirectory = m_ActiveDirectory.parent_path();
				ORI_PROJECT_HOT_DIRECTORY = m_ActiveDirectory.string();
				SyncDataEntry();
			}
		}
		ImGui::SameLine();
		ImGui::BeginDisabled();
		ImGui::Text(ICON_FA_RIGHT_LONG);
		ImGui::EndDisabled();
		ImGui::SameLine();
		ImGui::Text(m_ActiveDirectory.string().c_str());

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - 40);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0.0f, 0.0f });

		if (ImGui::Button(ICON_FA_ARROWS_ROTATE))
		{
			SyncDataEntry();
		}
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip(ICON_FA_CIRCLE_INFO"\tSync");
		ImGui::SameLine();
		if (ImGui::Button(ICON_FA_ELLIPSIS_VERTICAL))
		{
			ImGui::OpenPopup("content_setting");
		}

		ContentBrowserMiniOptionPopup();
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(4);

		

		////////////////////////////////////////////////// End Header
		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}
	void ContentBrowserLayer::SyncDataEntry()
	{
		if (!std::filesystem::exists(m_ActiveDirectory))
			return;

		m_DirEntry.clear();
		m_MusicEntry.clear();
		m_AssetEntry.clear();
		m_MaterialEntry.clear();
		m_ScriptEntry.clear();
		m_TextureEntry.clear();
		m_UnknownFileEntry.clear();

		for (auto& data_iter : std::filesystem::directory_iterator(m_ActiveDirectory))
		{
			std::string name = data_iter.path().stem().string();
			std::string path = data_iter.path().string();
			std::string ext = data_iter.path().extension().string();

			DirEntryInfo info(name, path, ext);

			if (data_iter.is_directory())
				m_DirEntry.push_back(std::make_pair(info, data_iter));
			else if (ext == ORI_ASSET_POSTFIX)
				m_AssetEntry.push_back(std::make_pair(info, data_iter));
			else if (ext == ORI_TEXTURE_POSTFIX)
				m_TextureEntry.push_back(std::make_pair(info, data_iter));
			else if (ext == ".wav" || ext == ".mp3")
				m_MusicEntry.push_back(std::make_pair(info, data_iter));
			else 
				m_UnknownFileEntry.push_back(std::make_pair(info, data_iter));

		}
	}
	void ContentBrowserLayer::PathIterator()
	{


		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.051f, 0.051f, 0.051f, 1.0f });
		ImGui::BeginChild("#dir_itrator");
		ImGui::Columns(m_ColumnCount, "innerList", false);

		s_ASSET_DRAG_ID = 0;
		s_TEXTURE_DRAG_ID = 100;

		for (size_t i = 0; i < m_DirEntry.size(); i++)
		{
			PushPanalItemStyle();
			ImGui::ImageButton(m_FolderIcon, { m_ThumbnailSize, m_ThumbnailSize });
			PopPanalItemStyle();

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_ActiveDirectory = m_DirEntry[i].first.Path;
				ORI_PROJECT_HOT_DIRECTORY = m_ActiveDirectory.string();
				SyncDataEntry();
				break;
			}

			PrintName(m_DirEntry[i].first.Name.c_str());
			ImGui::NextColumn();
		}

		for (size_t i = 0; i < m_AssetEntry.size(); i++)
		{
			ImGui::PushID(s_ASSET_DRAG_ID++);

			PushPanalItemStyle();
			
			ImGui::ImageButton((ImTextureID)(uintptr_t)AssetManager::s_RenderableGeometry[m_AssetEntry[i].first.Name].SnapShot, { m_ThumbnailSize, m_ThumbnailSize }, {0, 1}, {1, 0});

			PopPanalItemStyle();

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ModelPkg* package_payload = AssetManager::GetGeometry(m_AssetEntry[i].first.Name);

				ImGui::SetDragDropPayload(ORI_STATIC_MESH_PACKAGE_PAYLOAD, package_payload, sizeof(ModelPkg));

				ImGui::EndDragDropSource();
			}

			PrintName(m_AssetEntry[i].first.Name.c_str());
			ImGui::NextColumn();

			ImGui::PopID();
		}

		for (size_t i = 0; i < m_TextureEntry.size(); i++)
		{
			ImGui::PushID(s_TEXTURE_DRAG_ID++);

			PushPanalItemStyle();

			ImGui::ImageButton((ImTextureID)(uintptr_t)AssetManager::s_TextureRegistry[m_TextureEntry[i].first.Name]->GetTexture(), {m_ThumbnailSize, m_ThumbnailSize}, {0, 1}, {1, 0});

			PopPanalItemStyle();

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				Texture* package_payload = AssetManager::s_TextureRegistry[m_TextureEntry[i].first.Name];

				ImGui::SetDragDropPayload(ORI_TEXTURE_PACKAGE_PAYLOAD, package_payload, sizeof(ModelPkg));

				ImGui::EndDragDropSource();
			}

			PrintName(m_TextureEntry[i].first.Name.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		
		ImGui::Columns(1);

		ImGui::EndChild();
		ImGui::PopStyleColor();

	}
	void ContentBrowserLayer::PrintName(const char* _name)
	{
		float textWidth = ImGui::CalcTextSize(_name).x;
		float columnWidth = ImGui::GetContentRegionAvail().x;
		float offset = (columnWidth - textWidth) * 0.5f;
		ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
		ImGui::TextWrapped(_name);
	}
	void ContentBrowserLayer::PushPanalItemStyle(ImVec4 _col)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, _col);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });
	}
	void ContentBrowserLayer::PopPanalItemStyle()
	{
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}
}