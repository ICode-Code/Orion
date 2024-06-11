#ifndef OE1_PREFERENCE_WIN_H_
#define OE1_PREFERENCE_WIN_H_

#include "BaseMiniWindw.h"

namespace OE1Core
{
	class PreferenceWin : public BaseMiniWindow
	{
	public:
		PreferenceWin();
		~PreferenceWin();
		virtual void Render() override;
		inline static bool s_ShouldOpen = false;
	private:
		virtual void Update() override;
		class Scene* m_Scene = nullptr;
		ImGuiTreeNodeFlags m_Flag = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanFullWidth;
		std::vector<std::string> m_Lables;
		float m_Indent = 16.0f;


	private: // style
		void PushStyle();
		void PopStyle();

		void PreviewItemPushStyle(ImVec4 _col = { 0.15f, 0.15f, 0.15f, 1.0f });
		void PreviewItemPopStyle();

	private: // Win
		void PostProcess();
		void LightRoom();
		void Grid();
		void General();
		void Physics();


	private: // Util func
		void PrintPreviewItemName(const char* _name);
		void UpdateCameraBloomQuality(int _mip_level);

	private: // column
		float m_Padding = 45.0f;
		float m_ThumbnailSize = 65.0f;
		float m_CellSize = m_ThumbnailSize + m_Padding;
		float m_MaxPanelWidth;
		int m_ColumnCount;
		int m_SkyBoxItemSelectID = 0;
		int m_HDRItemSelectID = 0;

	};
}


#endif // !OE1_PREFERENCE_WIN_H_
