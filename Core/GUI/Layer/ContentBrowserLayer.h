#ifndef OE1_CONTENT_BROWSER_LAYER_H_
#define OE1_CONTENT_BROWSER_LAYER_H_

#include "LayerBase.h"
#include "PreDef.h"
#include <filesystem>

#include <ShlObj.h>
#include <Shlwapi.h> // For PathFileExists

namespace OE1Core
{
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
		void QueryProjectDir();
		std::string WideStrToNarrowStr(std::wstring _str);
		void DrawHeader();
		void PathIterator();

	private: // popups
		void ContentBrowserMiniOptionPopup();

	private: // Directory
		std::string m_RootDirectory = "\\ORion\\PRJ_Pilot";
		std::filesystem::path m_CurrentDirectory;
		std::filesystem::path m_ActiveDirectory = m_RootDirectory;

	private: // Spacing and Size
		float m_Padding = 42.0f;
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

	private: // iter paramater
		std::string m_IterName;
		std::string m_IterPath;
		std::string m_IterExt;
	};
}

#endif // !OE1_CONTENT_BROWSER_LAYER_H_
