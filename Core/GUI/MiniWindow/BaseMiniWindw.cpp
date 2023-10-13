#include "BaseMiniWindw.h"

namespace OE1Core
{
	BaseMiniWindow::BaseMiniWindow()
	{
		s_BaseWinFlag = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking;
		s_BaseTreeNodeFlag = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_DefaultOpen;
		s_TreeIndent = 16.0f;
	}
	BaseMiniWindow::~BaseMiniWindow()
	{

	}

	void BaseMiniWindow::ShowEmptyInputError()
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f, 0.121f, 0.353f, 1.0f });
		ImGui::Text(ICON_FA_TRIANGLE_EXCLAMATION);
		ImGui::PopStyleColor();
	}
	void BaseMiniWindow::ShowValidInputCheck()
	{
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.090f, 0.725f, 0.471f, 1.0f });
		ImGui::Text(ICON_FA_CIRCLE_CHECK);
		ImGui::PopStyleColor();
	}
	void BaseMiniWindow::CleanBuffer(char* _buffer, int _size)
	{
		for (int i = 0; i < _size; i++)
			_buffer[i] = '\0';
	}
	void BaseMiniWindow::FORCE_WINDOW_CENTER(ImVec2 local_window_size)
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
}