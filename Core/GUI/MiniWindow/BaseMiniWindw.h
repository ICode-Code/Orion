#ifndef OE1_BASE_MINI_WINDOW_H_
#define OE1_BASE_MINI_WINDOW_H_


#include "../../AssetManager/AssetManager.h"
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
	
	protected:
		virtual void CleanBuffer(char* _buffer, int _size)
		{
			for (int i = 0; i < _size; i++)
				_buffer[i] = '\0';
		}
		virtual void FORCE_WINDOW_CENTER(ImVec2 local_window_size)
		{
			int mainWinX, mainWinY;
			SDL_GetWindowPosition((SDL_Window*)ImGui::GetIO().UserData, &mainWinX, &mainWinY);

			SDL_Rect display_bound;
			SDL_GetDisplayBounds(0, &display_bound);

			// Calculate the position of the centered window based on the main window's position
			int screenWidth = display_bound.w;
			int screenHeight = display_bound.h;

			float xPos = (float)mainWinX + ((float)(screenWidth) * 0.5f) - (local_window_size.x * 0.5f);
			float yPos = (float)mainWinY + ((float)(screenHeight) * 0.5f) - (local_window_size.y * 0.5f);
			ImGui::SetNextWindowPos(ImVec2(xPos, yPos));
		}

	};
}


#endif // !OE1_BASE_MINI_WINDOW_H_
