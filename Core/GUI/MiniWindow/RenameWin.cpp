#include "RenameWin.h"
#include "../../Core/Scene/SceneEntityFactory.h"


namespace OE1Core
{
	RenameWin::RenameWin()
	{

	}
	RenameWin::~RenameWin()
	{

	}

	void RenameWin::Update()
	{

	}
	void RenameWin::Open(Component::TagComponent& _tag)
	{
		s_ActiveTag = &_tag;
		for (size_t i = 0; i < s_ActiveTag->m_Identifier.size(); i++)
			s_NewNameBuffer[i] = s_ActiveTag->m_Identifier[i];

		s_ShouldOpen = true;
	}
	void RenameWin::Close()
	{
		s_ShouldOpen = false;
	}
	void RenameWin::Render()
	{
		if (!RenameWin::s_ShouldOpen)
			return;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0535f, 0.0535f, 0.0535f, 1.0f });

		ImGui::OpenPopup(ICON_FA_GEAR"\tRename");
		ImGui::SetNextWindowSize(ImVec2(400, 0));
		if (ImGui::BeginPopupModal(ICON_FA_GEAR"\tRename", &RenameWin::s_ShouldOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::SetItemDefaultFocus();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });

			ImGui::PushItemWidth(350);
			ImGui::InputText("##NewSourceName", s_NewNameBuffer, IM_ARRAYSIZE(s_NewNameBuffer), ImGuiInputTextFlags_AllowTabInput);
			ImGui::PopItemWidth();


			ImGui::SameLine();
			strlen(s_NewNameBuffer) > 0 ? ShowValidInputCheck() : ShowEmptyInputError();


			ImGui::Separator();

			ImGui::SetCursorPosX(ImGui::GetContentRegionAvail().x * 0.5f - 120.0f);
			if (ImGui::Button("Okay", ImVec2(120, 0)))
			{
				size_t input_length = strlen(s_NewNameBuffer);
				if (input_length == 0)
				{
					s_EmptyTextError = true;
				}
				else
				{
					// Add Terminating char
					if (input_length > 0 && input_length < s_NewNameBufferSize)
					{
						s_NewNameBuffer[input_length] = '\0';

						std::string new_name = std::string(s_NewNameBuffer);

						if (new_name != s_ActiveTag->m_Identifier)
						{
							s_ActiveTag->m_Identifier = SceneEntityFactory::CheckNameCollision(new_name);
							s_ActiveTag->RefreshRootName();
						}
					}

					s_EmptyTextError = false;
					CleanBuffer(s_NewNameBuffer, s_NewNameBufferSize);
					Close();
					ImGui::CloseCurrentPopup();
				}	
			}
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0)))
			{
				CleanBuffer(s_NewNameBuffer, s_NewNameBufferSize);
				Close();
				ImGui::CloseCurrentPopup();
			}

			ImGui::PopStyleVar();

			ImGui::EndPopup();
		}
		ImGui::PopStyleColor();
	}
}