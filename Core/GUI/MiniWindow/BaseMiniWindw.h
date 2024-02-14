#ifndef OE1_BASE_MINI_WINDOW_H_
#define OE1_BASE_MINI_WINDOW_H_


#include "../../AssetManager/AssetManager.h"
#include "../../Platform/Win/WindowManager.h"
#include "../Native/WindowFileDialog.h"
#include "../../Core/Command/CoreCommand/Commnad.h"
#include "../CustomFrame/CustomFrame.h"
#include <Gui.h>

namespace OE1Core
{
	class BaseMiniWindow
	{
	public:
		BaseMiniWindow();
		virtual ~BaseMiniWindow();

		virtual void Update() = 0;
		virtual void Render() = 0;

	protected:
		inline static float s_TreeIndent;
		inline static ImGuiWindowFlags s_BaseWinFlag;
		inline static ImGuiWindowFlags s_BaseTreeNodeFlag;
	
	protected:
		virtual void ShowEmptyInputError();
		virtual void ShowValidInputCheck();
		virtual void CleanBuffer(char* _buffer, int _size);
		virtual void FORCE_WINDOW_CENTER(ImVec2 local_window_size);

	};
}


#endif // !OE1_BASE_MINI_WINDOW_H_
