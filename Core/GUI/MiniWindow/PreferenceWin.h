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

	private: // Win
		void PostProcess();
		void LightRoom();
		void Grid();
		void General();
		void Physics();

	};
}


#endif // !OE1_PREFERENCE_WIN_H_
