#include "ToolBarLayer.h"


namespace OE1Core
{
	ToolBarLayer::ToolBarLayer()
	{

	}
	ToolBarLayer::~ToolBarLayer()
	{

	}

	void ToolBarLayer::Update()
	{

	}

	void ToolBarLayer::Render()
	{
		ImGui::Begin("##toobar");


		ImGui::End();
	}
}