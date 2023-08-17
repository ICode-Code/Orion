#include "ProjectDirLayer.h"


namespace OE1Core
{
	ProjectDirLayer::ProjectDirLayer()
	{

	}
	ProjectDirLayer::~ProjectDirLayer()
	{

	}

	void ProjectDirLayer::Update()
	{

	}
	void ProjectDirLayer::Render()
	{
		ImGui::Begin(ICON_FA_FOLDER"\tDirectory");


		ImGui::End();
	}
}