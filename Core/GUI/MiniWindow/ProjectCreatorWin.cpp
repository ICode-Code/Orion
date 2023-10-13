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
		CleanBuffer(s_ProjectNameBuffer, s_ProjectNameBufferSize);
	}
	void ProjectCreatorWin::Open()
	{
		s_ShouldOpen = true;
	}
	void ProjectCreatorWin::Update()
	{
		ImGui::SetWindowSize(s_LocalWinSize);
	}
	void ProjectCreatorWin::Render()
	{
		if (!s_ShouldOpen)
			return;


		//FORCE_WINDOW_CENTER(s_LocalWinSize);

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.087f, 0.087f, 0.087f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });
		

		ImGui::Begin(ICON_FA_SHAPES"\tNew Project", &s_ShouldOpen, s_BaseWinFlag | ImGuiWindowFlags_NoMove);
		Update();

		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 2.0f, 2.0f });


		if (ProjectImageButton(ProjectType::Empty, m_EmptyProjectIcon))
		{
			s_ProjectType = ProjectType::Empty;
		} 
		ImGui::SameLine();
		if (ProjectImageButton(ProjectType::PBR_Template, m_PBRTestProjectIcon))
		{
			s_ProjectType = ProjectType::PBR_Template;
		}
		ImGui::SameLine();
		if (ProjectImageButton(ProjectType::FPS_Template, m_FPSTestProjectIcon))
		{
			s_ProjectType = ProjectType::FPS_Template;
		}

		

		ImGui::PopStyleVar(3);
		
		

		static bool test = true;
		CustomFrame::UIEditorCheckbox("Inlucde Startup Pack", &test);
		CustomFrame::UIEditorCheckbox("Option 1", &test);
		CustomFrame::UIEditorCheckbox("Option 2", &test);



		ImGui::NewLine();
		ImGui::Separator();
		ImGui::Text("Project Name");
		
		ImGui::PushItemWidth(400);
		static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
		ImGui::InputText("##sourceFolderName", s_ProjectNameBuffer, IM_ARRAYSIZE(s_ProjectNameBuffer), flags);
		ImGui::PopItemWidth();
		ImGui::SameLine();
		
		if (s_EmptyTextError)
		{
			ShowEmptyInputError();
			ImGui::SameLine();
		}

		ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));

		if (ImGui::Button("Create  Project", { 200, 0 }))
		{
			size_t input_length = strlen(s_ProjectNameBuffer);
			if (input_length == 0)
				s_EmptyTextError = true;
			else
			{
				s_EmptyTextError = false;
				if (input_length > 0 && input_length < s_ProjectNameBufferSize)
					s_ProjectNameBuffer[input_length] = '\0';
			}

			CleanBuffer(s_ProjectNameBuffer, s_ProjectNameBufferSize);
		}

		ImGui::PopStyleColor(3);


		ImGui::End();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	bool ProjectCreatorWin::ProjectImageButton(ProjectType _type, ImTextureID& _image, const ImVec2& _size)
	{
		if(s_ProjectType == _type)
			ImGui::PushStyleColor(ImGuiCol_Button, Gui::s_ThemeColor);

		bool _button_action = ImGui::ImageButton(_image, _size);
		

		if (s_ProjectType == _type)
			ImGui::PopStyleColor();
		
		return _button_action;
	}
}