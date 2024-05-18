#include "PreferenceWin.h"
#include "../../Core/Scene/SceneManager.h"

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
		if (!PreferenceWin::s_ShouldOpen) return;

		m_Scene = SceneManager::GetActiveScene();

		if (!m_Scene) return;


		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.235f, 0.235f, 0.235f, 1.0f });
		ImGui::Begin(ICON_FA_GEAR"\tPreference",&PreferenceWin::s_ShouldOpen, s_BaseWinFlag);

		CustomFrame::UIEditorCheckbox("Use Render Thread for Animtion Update", &m_Scene->m_UseActiveThreadForAnimation);

		ImGui::End();
		ImGui::PopStyleColor();
	}
}