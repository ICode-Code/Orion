#include "PreferenceWin.h"


namespace OE1Core
{
	PreferenceWin::PreferenceWin()
	{

	}
	PreferenceWin::~PreferenceWin()
	{

	}

	void PreferenceWin::Update()
	{

	}
	void PreferenceWin::Render()
	{
		if (!PreferenceWin::s_ShouldOpen)
			return;

		//

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.235f, 0.235f, 0.235f, 1.0f });
		ImGui::Begin(ICON_FA_GEAR"\tPreference",&PreferenceWin::s_ShouldOpen, s_BaseWinFlag);



		ImGui::End();
		ImGui::PopStyleColor();
	}
}