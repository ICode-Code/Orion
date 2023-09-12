#include "ProjectCreatorWin.h"



namespace OE1Core
{
	ProjectCreatorWin::ProjectCreatorWin()
	{
		m_EmptyProjectIcon = (ImTextureID)(uintptr_t)AssetManager::GetTexture("EmptyProject")->GetTexture();
		m_PBRTestProjectIcon = (ImTextureID)(uintptr_t)AssetManager::GetTexture("PBRTestProject")->GetTexture();
		m_FPSTestProjectIcon = (ImTextureID)(uintptr_t)AssetManager::GetTexture("FPSTestProject")->GetTexture();
	}
	ProjectCreatorWin::~ProjectCreatorWin()
	{

	}
	void ProjectCreatorWin::Open()
	{
		s_ShouldOpen = true;
	}
	void ProjectCreatorWin::Update()
	{
		ImGui::SetWindowSize({ 1000, 500 });
	}
	void ProjectCreatorWin::Render()
	{
		if (!s_ShouldOpen)
			return;

		ImGui::Begin(ICON_FA_SHAPES"\tNew Project", &s_ShouldOpen, s_BaseWinFlag);
		Update();

		ImGui::ImageButton(m_EmptyProjectIcon, { 300, 200 });
		ImGui::SameLine();
		ImGui::ImageButton(m_PBRTestProjectIcon, { 300, 200 });
		ImGui::SameLine();
		ImGui::ImageButton(m_FPSTestProjectIcon, { 300, 200 });

		ImGui::NewLine();
		
		ImGui::Separator();


		
		ImGui::Button("Create  Project", {200, 0});


		ImGui::End();
	}
}