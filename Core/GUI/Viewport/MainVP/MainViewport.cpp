#include "MainViewport.h"
#include "../../../Core/Scene/Entity.h"


namespace OE1Core
{
	MainViewport::MainViewport()
	{

	}
	MainViewport::~MainViewport()
	{

	}

	void MainViewport::Update()
	{

	}
	void MainViewport::Render()
	{


		ImGui::Begin("#level_editor", NULL, m_DefaultViewportFlags);

		// Update viewport realated stuff
		UpdateViewport();


		ImGui::SetCursorPos({ 0.0f, 0.0f });
		m_Offset = ImGui::GetCursorPos();

		ImGui::Image((ImTextureID)(intptr_t)ViewportArgs::FINAL_FRAME, m_ViewportSize, { 0, 1 }, { 1, 0 });

		HandleClickOverViewport();
		HandlePayloadPackage();

		ImGui::End();
	}
	void MainViewport::HandleClickOverViewport()
	{
		MousePoseRefToViewport(m_Offset);

		if (ImGui::IsItemHovered())
		{
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				CommandDef::EntitySelectionCommandDef selection_command;
				selection_command.posX = m_MousePosition.x;
				selection_command.posY = m_MousePosition.y;
				selection_command.FrameID = 0;
				Command::PushEntitySelectionCommand(selection_command);
			}
		}
	}
	void MainViewport::HandlePayloadPackage()
	{
		if (ImGui::BeginDragDropTarget())
		{

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(ORI_STATIC_MESH_PACKAGE_PAYLOAD))
			{
				ModelPkg* package = (ModelPkg*)payload->Data;
				
				ActiveEntity::Pick(SceneEntityFactory::CreateRichMeshEntity(package));
			}

			ImGui::EndDragDropTarget();
		}
	}
}