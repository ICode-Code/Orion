#include "SceneHierarchyLayer.h"


namespace OE1Core
{
	SceneHierarchyLayer::SceneHierarchyLayer()
	{

	}

	SceneHierarchyLayer::~SceneHierarchyLayer()
	{

	}

	void SceneHierarchyLayer::Update()
	{

	}
	void SceneHierarchyLayer::Render()
	{
		ImGui::Begin(ICON_FA_CUBES_STACKED"\tHierarchy");

		ImGui::End();
	}
}