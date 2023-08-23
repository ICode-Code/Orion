#ifndef OE1_BASE_MINI_WINDOW_H_
#define OE1_BASE_MINI_WINDOW_H_



#include "../../Platform/Win/WindowManager.h"
#include "../Native/WindowFileDialog.h"
#include "../../Core/Command/Commnad.h"
#include "../CustomFrame/CustomFrame.h"
#include <Gui.h>

namespace OE1Core
{
	class BaseMiniWindow
	{
	public:
		BaseMiniWindow()
		{ }
		~BaseMiniWindow()
		{ }

		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		inline static float s_TreeIndent = 16.0f;
		inline static ImGuiWindowFlags s_BaseWinFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
		inline static ImGuiWindowFlags s_BaseTreeNodeFlag = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
	};
}


#endif // !OE1_BASE_MINI_WINDOW_H_
