#include "3DAssetLoaderWin.h"


namespace OE1Core
{
	Asset3DLoaderWin::Asset3DLoaderWin()
	{

	}
	Asset3DLoaderWin::~Asset3DLoaderWin()
	{

	}

	void Asset3DLoaderWin::Update()
	{
		ImGui::SetWindowSize({ 500, 600 });
	}
	void Asset3DLoaderWin::Open(std::string _asset_path)
	{
		if (_asset_path.empty())
			return;

		s_ShouldOpen = true;
		s_AssetPath = _asset_path;
		s_LoadArgs.Reset();
	}
	void Asset3DLoaderWin::Render()
	{
		if (!s_ShouldOpen)
			return;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.2f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, { 0.28f, 0.28f, 0.28f, 1.0f });
		ImGui::Begin(ICON_FA_DOWNLOAD"\tLoad 3D Asset", &s_ShouldOpen, s_BaseWinFlag);
		
		Update();

		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 7, 8 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 14, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, { .5f, .5f });


		if (ImGui::TreeNodeEx("Asset Identifier Info", s_BaseTreeNodeFlag))
		{
			ImGui::Indent(s_TreeIndent);


			CustomFrame::UIEditorTextValue("Name",			Loader::NameHandle::FilterFileName(s_AssetPath).c_str());
			CustomFrame::UIEditorTextValue("Path",			Loader::NameHandle::FilterPath(s_AssetPath).c_str());
			CustomFrame::UIEditorTextValue("Extension",		Loader::NameHandle::FilterFileNameExt(s_AssetPath).c_str());


			ImGui::Indent(-s_TreeIndent);
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Transform", s_BaseTreeNodeFlag))
		{
			ImGui::Indent(s_TreeIndent);

			static glm::vec3 temp_pos = glm::vec3(0.0f);
			CustomFrame::UIEditorf3<glm::vec3>("Translation", temp_pos, 0.0f, 100.0f);
			CustomFrame::UIEditorf3<glm::vec3>("Rotation", temp_pos, 0.0f, 100.0f);
			CustomFrame::UIEditorf3<glm::vec3>("Scale", temp_pos, 0.0f, 100.0f);

			ImGui::Indent(-s_TreeIndent);
			ImGui::TreePop();
		}

		if (ImGui::TreeNodeEx("Parameters", s_BaseTreeNodeFlag))
		{
			ImGui::Indent(s_TreeIndent);

			static bool separte_by_dir = false;


			CustomFrame::UIEditorCheckbox("Has Animation", &s_LoadArgs.HasAnimation);
			CustomFrame::UIEditorCheckbox("Load Material", &s_LoadArgs.CreateMaterial);
			CustomFrame::UIEditorCheckbox("Create Directory", &separte_by_dir);
			CustomFrame::UIEditorCheckbox("Generate LOD", &s_LoadArgs.GenerateDynamicLOD);
			

			ImGui::Indent(-s_TreeIndent);
			ImGui::TreePop();
		}


		ImVec2 avail_region = ImGui::GetContentRegionAvail();
		ImGui::SetCursorPosY(510.0f);

		ImGui::Separator();
		ImGui::NewLine();

		ImGui::SetCursorPosX((avail_region.x / 2.0f) - 120.0f);
		if (ImGui::Button("Import", ImVec2(120.0f, 0.0f)))
		{
			s_LoadArgs.SourcePath = s_AssetPath;
			s_LoadArgs.DestinationPath = "none";
			Loader::GeometryLoader::LoadGeometry(s_LoadArgs);
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
		{

		}


		ImGui::PopStyleVar(4);

		ImGui::End();
		ImGui::PopStyleColor(2);
	}
}