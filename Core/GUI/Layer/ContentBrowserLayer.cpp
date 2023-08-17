#include "ContentBrowserLayer.h"

namespace OE1Core
{
	ContentBrowserLayer::ContentBrowserLayer()
	{

	}
	ContentBrowserLayer::~ContentBrowserLayer()
	{

	}

	void ContentBrowserLayer::Render()
	{
		ImGui::Begin(ICON_FA_FOLDER_OPEN"\tContent Browser");

		ImGui::End();
	}
	void ContentBrowserLayer::Update()
	{

	}
}