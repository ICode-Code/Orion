#include "ContentBrowserLayer.h"

namespace OE1Core
{
	ContentBrowserLayer::ContentBrowserLayer()
	{
		m_FolderIcon = (ImTextureID)(intptr_t)AssetManager::GetTexture("Folder")->GetTexture();
		m_UnknownFileIcon = (ImTextureID)(intptr_t)AssetManager::GetTexture("Unknown")->GetTexture();

		QueryProjectDir();
	}
	ContentBrowserLayer::~ContentBrowserLayer()
	{

	}
	std::string ContentBrowserLayer::WideStrToNarrowStr(std::wstring _str)
	{
		std::string dest;
		for (wchar_t c : _str)
			dest += (char)c;
		return dest;
	}
	void ContentBrowserLayer::QueryProjectDir()
	{
		PWSTR my_documents_path = nullptr;
		if (SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &my_documents_path) == S_OK)
		{
			std::wstring project_folder_path_wide = my_documents_path;
			CoTaskMemFree(my_documents_path);
			std::string project_folder_path = WideStrToNarrowStr(project_folder_path_wide);
			project_folder_path += m_RootDirectory;
			m_RootDirectory = project_folder_path;
			m_ActiveDirectory = m_RootDirectory;
		}
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
			if (m_ActiveDirectory != m_RootDirectory)
				m_ActiveDirectory = m_ActiveDirectory.parent_path();
		ImGui::SameLine();
		ImGui::BeginDisabled();
		ImGui::Text(ICON_FA_RIGHT_LONG);
		ImGui::EndDisabled();
		ImGui::SameLine();
		ImGui::Text(m_ActiveDirectory.string().c_str());

		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - 20);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		if (ImGui::Button(ICON_FA_ELLIPSIS_VERTICAL))
		{
			ImGui::OpenPopup("content_setting");
		}
		ContentBrowserMiniOptionPopup();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(4);

		

		////////////////////////////////////////////////// End Header
		ImGui::EndChild();

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}
	void ContentBrowserLayer::PathIterator()
	{


		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.051f, 0.051f, 0.051f, 1.0f });
		ImGui::BeginChild("#dir_itrator");
		ImGui::Columns(m_ColumnCount, "innerList", false);

		int drag_id = 0;
		for (auto& data_iter : std::filesystem::directory_iterator(m_ActiveDirectory))
		{
			ImGui::PushID(drag_id++);
			m_IterName = data_iter.path().stem().string();
			m_IterPath = data_iter.path().string();
			m_IterExt = data_iter.path().extension().string();


			if (data_iter.is_directory())
			{
				PushPanalItemStyle();
				ImGui::ImageButton(m_FolderIcon, { m_ThumbnailSize, m_ThumbnailSize });
				PopPanalItemStyle();

				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					m_ActiveDirectory = m_IterPath;
				}
			}
			else if (m_IterExt == ORI_ASSET_POSTFIX)
			{
				PushPanalItemStyle();
				ImGui::ImageButton((ImTextureID)(uintptr_t)AssetManager::s_RenderableGeometry[m_IterName].SnapShot, {m_ThumbnailSize, m_ThumbnailSize});
				PopPanalItemStyle();
			}
			else if (m_IterExt == ".wav" || m_IterExt == ".mp3")
			{

			}
			else
			{

				PushPanalItemStyle();
				ImGui::ImageButton(m_UnknownFileIcon, { m_ThumbnailSize, m_ThumbnailSize });
				PopPanalItemStyle();

			}
			float textWidth = ImGui::CalcTextSize(m_IterName.c_str()).x;
			float columnWidth = ImGui::GetContentRegionAvail().x;
			float offset = (columnWidth - textWidth) * 0.5f;
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);
			ImGui::TextWrapped(m_IterName.c_str());
			ImGui::NextColumn();

			ImGui::PopID();
		}
		ImGui::Columns(1);

		ImGui::EndChild();
		ImGui::PopStyleColor();

	}
	void ContentBrowserLayer::PushPanalItemStyle()
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 8 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 5.0f });
	}
	void ContentBrowserLayer::PopPanalItemStyle()
	{
		ImGui::PopStyleVar(3);
		ImGui::PopStyleColor(2);
	}
}