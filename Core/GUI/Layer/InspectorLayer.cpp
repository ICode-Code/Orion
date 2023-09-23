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
			ImGui::Text("Select item in the viewport to see entity property!");
		}

		ImGui::End();
	}
}