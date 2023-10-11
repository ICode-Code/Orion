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

		if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
		{
			SceneManager::GetActiveScene()->GetActiveEntity()->GetActive().GetComponent<Component::InspectorComponent>().Inspect();
		}
		else
		{
			ImGui::Text("Click on an item in the viewport to view its entity properties");
		}

		ImGui::End();
	}
}