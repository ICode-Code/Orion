#include "MainViewport.h"
#include "../../../Core/Scene/Entity.h"


namespace OE1Core
{
	MainViewport::MainViewport()
	{
		m_Operation				= ImGuizmo::OPERATION::BOUNDS;
		m_Mode					= ImGuizmo::MODE::LOCAL;

		m_SnapValue				= glm::vec3(1.0f);
		m_SnapTranslation		= 1.0f;
		m_SnapRotation			= 45.0f;

		m_EnableSnap			= false;
		m_ShowActionButton		= true;
		m_MouseOverViewport		= false;

		m_IsLeftShitPressed		= false;
		m_IsCloning				= false;
	}
	MainViewport::~MainViewport()
	{

	}

	void MainViewport::Update()
	{

	}
	void MainViewport::OnEvent(OECore::IEvent& e)
	{
		OECore::IEventDispatcher dispatcher(e);
		dispatcher.Dispatch<OECore::KeyReleaseEvent>(std::bind(&MainViewport::HandleKeyRelease, this, std::placeholders::_1));
		dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&MainViewport::HandleKeyPress, this, std::placeholders::_1));
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
		HandleActionButton();
		HandleGIZMO();

		ImGui::End();
	}
	void MainViewport::HandleActionButton()
	{
		if (!m_ShowActionButton)
			return;
		// Get Aveil Window Size
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();


		// Set Position to Begain Draw
		ImGui::SetCursorPos({ (vMax.x / 2.0f) + 90.0f, vMin.y});

		m_TransformGroupButton.Draw(m_Operation);
		
		ImGui::SameLine();
		
		m_ModeGroup.Draw(m_Mode, m_EnableSnap, m_SnapTranslation, m_SnapRotation);

		ImGui::SameLine();
		
		m_RenderModeGroup.Draw(SceneManager::GetActiveScene()->GetRenderMode());

		ImGui::SameLine();

		m_UtilityGroup.Draw(m_ShowActionButton, SceneManager::GetActiveScene()->m_CameraPkg);
	}
	void MainViewport::HandleGIZMO()
	{
		if (!SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
			return;
		Entity picked_entity = SceneManager::GetActiveScene()->GetActiveEntity()->GetActive();
		CameraPackage& scene_camera = SceneManager::GetActiveScene()->m_CameraPkg;

		PrepareGIZMO();

		
		Component::TransformComponent& transform_component = picked_entity.GetComponent<Component::TransformComponent>();
		glm::mat4 object_transform = transform_component.QueryWorldTransform();
		
		
		m_SnapValue = glm::vec3(m_Operation == ImGuizmo::OPERATION::ROTATE ? m_SnapRotation : m_SnapTranslation);
		ImGuizmo::Manipulate(
			glm::value_ptr(scene_camera.GetCamera()->m_View),
			glm::value_ptr(scene_camera.GetCamera()->m_Projection),
			m_Operation, m_Mode, glm::value_ptr(object_transform), nullptr, m_EnableSnap ? glm::value_ptr(m_SnapValue) : nullptr
		);

		if (ImGuizmo::IsUsing())
		{
			glm::mat4 world_transform = glm::mat4(1.0f);
			if (transform_component.m_Parent)
				world_transform = transform_component.m_Parent->GetComponent<Component::TransformComponent>().QueryWorldTransform();

			glm::mat4 local_transform = glm::inverse(world_transform) * object_transform;

			glm::vec3 scale, translation, skew;
			glm::vec4 perspective;
			glm::quat rotation;

			/// This function is a bit expensive but it is just for manipulating when ever we drag
			/// so I don't really care if it is that expensive 
			glm::decompose(local_transform, scale, rotation, translation, skew, perspective);


			switch (m_Operation)
			{
			case ImGuizmo::TRANSLATE:
				if (m_IsLeftShitPressed && !m_IsCloning)
				{
					m_IsCloning = true;
					ActiveEntity* active_entity = SceneManager::GetActiveScene()->GetActiveEntity();
					
					active_entity->Pick(SceneEntityFactory::Clone(active_entity->GetActive()));
				}
				else
				{
					transform_component.m_Position = translation;
				}
				break;
			case ImGuizmo::ROTATE:
				transform_component.SetRotation(rotation);
				break;
			case ImGuizmo::SCALE:
				transform_component.m_Scale = scale;
				break;
			case ImGuizmo::BOUNDS:
				break;
			default:
				break;
			}

		}
		else
		{
			m_IsCloning = false;
		}

	}
	void MainViewport::HandleClickOverViewport()
	{
		MousePoseRefToViewport(m_Offset);

		if (m_MouseOverViewport = ImGui::IsItemHovered())
		{

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)		||
				ImGui::IsMouseClicked(ImGuiMouseButton_Right)		|| 
				ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))  
				SceneManager::GetActiveScene()->GetActiveEntity()->Hold(false);

			if (SceneManager::GetActiveScene()->GetActiveEntity()->IsHold())
			{
				glm::vec3 position = (SceneManager::GetActiveScene()->GetRay()->GetRayDirection(m_MousePosition) * 6.0f) + SceneManager::GetActiveScene()->m_CameraPkg.GetController()->GetCurrentPosition();
				Entity entity = SceneManager::GetActiveScene()->GetActiveEntity()->GetActive();
				entity.GetComponent<Component::TransformComponent>().m_Position = position;
			}

			if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
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
				
				glm::vec3 position = (SceneManager::GetActiveScene()->GetRay()->GetRayDirection(m_MousePosition) * 10.0f) + SceneManager::GetActiveScene()->m_CameraPkg.GetController()->GetCurrentPosition();
				Entity droped_entity = SceneEntityFactory::CreateRichMeshEntity(package, position);
				SceneManager::GetActiveScene()->GetActiveEntity()->Pick(droped_entity, true);
			}

			ImGui::EndDragDropTarget();
		}
	}


	bool MainViewport::HandleKeyRelease(OECore::KeyReleaseEvent& e)
	{
		if (e.GetKeyCode() == SDLK_LSHIFT)
			m_IsLeftShitPressed = false;

		if (!m_MouseOverViewport)
			return false;
		if (e.GetKeyCode() == SDLK_g)
		{
			if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
				SceneManager::GetActiveScene()->GetActiveEntity()->Hold(true);
			return true;
		}

		if (e.GetKeyCode() == SDLK_1)
		{
			m_Operation = ImGuizmo::OPERATION::BOUNDS;
			return true;
		}
		if (e.GetKeyCode() == SDLK_2)
		{
			m_Operation = ImGuizmo::OPERATION::TRANSLATE;
			return true;
		}
		if (e.GetKeyCode() == SDLK_3)
		{
			m_Operation = ImGuizmo::OPERATION::ROTATE;
			return true;
		}
		if (e.GetKeyCode() == SDLK_4)
		{
			m_Operation = ImGuizmo::OPERATION::SCALE;
			return true;
		}

		if (e.GetKeyCode() == SDLK_F1)
		{
			m_ShowActionButton = !m_ShowActionButton;
			return true;
		}

		if (e.GetKeyCode() == SDLK_f)
		{
			if (SceneManager::GetActiveScene()->GetActiveEntity()->ValidSelection())
			{
				SceneManager::GetActiveScene()->m_CameraPkg.GetController()->Focus(
					SceneManager::GetActiveScene()->GetActiveEntity()->GetActive().GetComponent<Component::TransformComponent>().m_Position
				);
			}
			
		}

		return false;
	}
	bool MainViewport::HandleKeyPress(OECore::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == SDLK_LSHIFT)
			m_IsLeftShitPressed = true;


		return true;
	}
}