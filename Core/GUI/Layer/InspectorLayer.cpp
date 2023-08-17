#include "InspectorLayer.h"


namespace OE1Core
{
	InspectorLayer::InspectorLayer()
	{

	}
	InspectorLayer::~InspectorLayer()
	{

	}

	void InspectorLayer::Update()
	{

	}
	void InspectorLayer::Render()
	{
		ImGui::Begin(ICON_FA_SLIDERS"\tInspector");


		ImGui::End();
	}
}