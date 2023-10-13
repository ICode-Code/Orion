#include "CloseWin.h"


namespace OE1Core
{
	CloseWin::CloseWin()
	{
		m_LogoutTexture = (ImTextureID)(intptr_t)AssetManager::GetTexture("Question")->GetTexture();
	}
	CloseWin::~CloseWin()
	{

	}

	void CloseWin::Update()
	{

	}
	void CloseWin::Render()
	{
		if (!s_ShouldOpen)
			return;

		
		ImGui::OpenPopup("Departing Orion's Realm");
		if (ImGui::BeginPopupModal("Departing Orion's Realm", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Image(m_LogoutTexture, { 60, 60 }); ImGui::SameLine();
			ImGui::Text("Warning! Exiting now might cause a disturbance in the Orion Engine space-time codecontinuum. \nYour stellar creations deserve a safe landing – make sure to save your work and avoid cosmic \nglitches before embarking on your intergalactic journey");
			ImGui::Separator();


			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
			ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x * 0.5f - 120.0f);
			if (ImGui::Button("Cosmic Checkout", ImVec2(120, 0)))
			{
				WindowManager::GetWindow(ENGINE_MAIN_WINDOW)->Close();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Star Safeguard", ImVec2(120, 0)))
			{
				s_ShouldOpen = false;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("Void Voyage", ImVec2(120, 0)))
			{
				s_ShouldOpen = false;
				ImGui::CloseCurrentPopup();
			}

			ImGui::PopStyleVar();

			ImGui::EndPopup();
		}

	}
}