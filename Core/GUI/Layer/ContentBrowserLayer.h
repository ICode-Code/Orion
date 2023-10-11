#ifndef OE1_CONTENT_BROWSER_LAYER_H_
#define OE1_CONTENT_BROWSER_LAYER_H_

#include "LayerBase.h"
#include "PreDef.h"
#include <filesystem>

#include <ShlObj.h>
#include <Shlwapi.h> // For PathFileExists

namespace OE1Core
{
	struct DirEntryInfo
	{
		DirEntryInfo(std::string _name = "", std::string _path = "", std::string _ext = "")
			: Name(_name), Path(_path), Extenstion(_ext) {}
		std::string Name;
		std::string Path;
		std::string Extenstion;
	};


	class ContentBrowserLayer : public LayerBase
	{
	public:
		ContentBrowserLayer();
		~ContentBrowserLayer();

		virtual void Update() override;
		virtual void Render() override;



	private: // Util functions
		void PushPanalItemStyle();
		void PopPanalItemStyle();
		void DrawHeader();
		void PathIterator();
		void SyncDataEntry();
		void PrintName(const char* _name);

	private: // popups
		void ContentBrowserMiniOptionPopup();


	private: // Directory
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_ActiveDirectory;

		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_DirEntry;
		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_MusicEntry;
		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_AssetEntry;
		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_MaterialEntry;
		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_ScriptEntry;
		std::vector<std::pair<DirEntryInfo, std::filesystem::directory_entry>> m_UnknownFileEntry;

	private: // Spacing and Size
		float m_Padding = 45.0f;
		float m_ThumbnailSize = 65.0f;
		float m_CellSize = m_ThumbnailSize + m_Padding;
		float m_MaxPanelWidth;
		int m_ColumnCount;// = (int)(m_MaxPanelWidth / m_CellSize);
		ImGuiTreeNodeFlags m_TreeNode = ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;

	private: // Icons
		ImTextureID m_FolderIcon		= 0;
		ImTextureID m_UnknownFileIcon	= 0;
		ImTextureID m_AudioIcon			= 0;
		ImTextureID m_AnimationIcon		= 0;
		inline static int s_DRAG_ID = 0;
	};
}

#endif // !OE1_CONTENT_BROWSER_LAYER_H_
