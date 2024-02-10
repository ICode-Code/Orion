#include "InspectorComponent.h"
#include "../IComponent.h"
#include "../Core/Scene/SceneManager.h"


namespace OE1Core
{
	namespace Component
	{
		void InspectorComponent::Inspect()
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 4, 8 });
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 3 });

			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.0f, 0.439f, 0.878f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.0f, 0.439f, 0.878f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_SliderGrab, { 0.7f, 0.7f, 0.7f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0.7f, 0.7f, 0.7f, 1.0f });

			ImGui::PushStyleColor(ImGuiCol_Header, { 0.1f, 0.1f, 0.1f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 0.12f, 0.12f, 0.12f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_HeaderActive, { 0.12f, 0.12f, 0.12f, 1.0f });

			ITag();
			ITransform();
			ICamController();
			ICamera();
			IMesh();
			ICameraPackage();

			ImGui::PopStyleColor(7);
			ImGui::PopStyleVar(3);
		}
		void InspectorComponent::SetCameraPackageComponent(class CameraPackageComponent* _camera_package_component) { m_CameraPackageComponent = _camera_package_component;}
		void InspectorComponent::SetTagComponent(class TagComponent* _tag_component) { m_TagComponent = _tag_component; }
		void InspectorComponent::SetTransformComponent(class TransformComponent* _transform) { m_TransformComponent = _transform; };
		void InspectorComponent::SetMeshComponent(class MeshComponent* _mesh) { m_MeshComponent = _mesh; }
		void InspectorComponent::SetCameraControllerComponent(class BaseCameraControllerComponent* _camera_controller) { m_BaseCameraControllerComponent = _camera_controller; }
		void InspectorComponent::SetCameraComponent(class CameraComponent* _camera_component) { m_CameraComponent = _camera_component; }
		void InspectorComponent::ITag()
		{
			if (!m_TagComponent)
				return;
			std::string _uid = "UUID: " + std::to_string(m_TagComponent->m_UID);
			bool _open = ImGui::TreeNodeEx("Tag Component", m_TreeNodeFlags);
			if (_open)
			{
				CustomFrame::UIEditorTextValue("Identifier", m_TagComponent->m_Identifier.c_str());

				CustomFrame::UIEditorTextValue("UUID", std::to_string(m_TagComponent->m_UID).c_str());

				ImGui::TreePop();
			}

			if (ImGui::IsItemHovered() && !_open)
				ImGui::SetTooltip(_uid.c_str());
		}
		void InspectorComponent::ITransform()
		{
			if (!m_TransformComponent)
				return;
			/*
			if (SceneManager::QueryActiveEntity()->IsBatchMode())
				m_TransformComponent = &SceneManager::QueryActiveEntity()->GetProxyTransform();*/

			if (ImGui::TreeNodeEx("Transform Component", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				CustomFrame::UIEditorf3<glm::vec3>("Translation", m_TransformComponent->m_Position, 0.0f, 100.0f);
				CustomFrame::UIEditorf3<glm::vec3>("Rotation", m_TransformComponent->m_Euler, 0.0f, 100.0f);
				CustomFrame::UIEditorf3<glm::vec3>("Scale", m_TransformComponent->m_Scale, 0.0f, 100.0f);

				ImGui::TreePop();
			}

		}
		void InspectorComponent::IMesh()
		{
			if (!m_MeshComponent)
				return;
			if (ImGui::TreeNodeEx("Mesh Component", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });
				ModelPkg* package = AssetManager::GetGeometry(m_MeshComponent->GetPackageID());



				for (size_t i = 0; i < package->MeshList.size(); i++)
				{
					ImGui::Indent(16.0f);
					if (ImGui::TreeNodeEx(package->MeshList[i].Material->GetName().c_str(), m_TreeNodeFlags + ImGuiTreeNodeFlags_DefaultOpen))
					{
						MasterMaterial* ActiveMat = package->MeshList[i].Material;
						
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
						ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
						ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });

						if (CustomFrame::UIEditorImageButton("Orion Material", (ImTextureID)(uintptr_t)ActiveMat->GetPreviewRef(), { 60, 60 }))
						{
							if (MaterialManager::GetMaterialView().size() < ORI_MATERIAL_WINDOW_ALLOCATION_THRESHOLD)
							{
								MaterialManager::RegisterMaterialView(MaterialManager::GetMaterial(package->MeshList[i].MaterialID));
							}
							else
							{
								LOG_ERROR("Unable to open a new material window. Please close any existing material windows, as the allocation threshold has reached maximum capacity.");
							}
						}
						ImGui::PopStyleVar(3);
						ImGui::PopStyleColor();

						if (ImGui::BeginDragDropTarget())
						{

							if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(ORI_MATERIAL_PACKAGE_PAYLOAD))
							{
								
							}

							ImGui::EndDragDropTarget();
						}
						
						ImGui::BeginDisabled();
						bool has_color_map = package->MeshList[i].Material->HasColorMap();
						bool has_non_color_map = package->MeshList[i].Material->HasNonColorMap();
						
						ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 2, 2 });

						CustomFrame::UIEditorCheckbox("Has Color Map", &has_color_map);
						CustomFrame::UIEditorCheckbox("Has Non-Color Map", &has_non_color_map);

						ImGui::PopStyleVar();

						ImGui::EndDisabled();

						ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.0f, 0.0f });
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });

						

						ImGui::PopStyleColor(2);

						ImGui::TreePop();
					}
					ImGui::Indent(-16.0f);
				}


				CustomFrame::UIEditorTextValue("Name", package->Name.c_str());
				CustomFrame::UIEditorTextValue("Unique Instance ID", std::to_string(m_MeshComponent->m_UniqueInstanceID).c_str());
				CustomFrame::UIEditorTextValue("Buffer Offset", std::to_string(m_MeshComponent->m_Offset).c_str());
				CustomFrame::UIEditorTextValue("package ID", std::to_string(package->PackageID).c_str());
				CustomFrame::UIEditorTextValue("Indice Count", std::to_string(package->IndicesCount).c_str());
				CustomFrame::UIEditorTextValue("SubMesh Count", std::to_string(package->SubMeshCount).c_str());
				CustomFrame::UIEditorTextValue("Triangle Count", std::to_string(package->TriangleCount).c_str());
				CustomFrame::UIEditorTextValue("Vertex Count", std::to_string(package->VertexCount).c_str());
				CustomFrame::UIEditorTextValue("Material Count", std::to_string(package->SubMeshCount).c_str());
			

				CustomFrame::UIEditorImage("Preview", (ImTextureID)(uintptr_t)package->SnapShot, { 100, 100 });


				ImGui::PopStyleVar();

				ImGui::TreePop();
			}

		}
		void InspectorComponent::ICameraPackage()
		{
			if (!m_CameraPackageComponent)
				return;

			if (ImGui::TreeNodeEx("Camera View Point", m_TreeNodeFlags))
			{
				
				
				ImGui::TreePop();
			}

		}
		void InspectorComponent::ICamController()
		{
			if (!m_BaseCameraControllerComponent)
				return;
		}
		void InspectorComponent::ICamera()
		{
			if (!m_CameraComponent)
				return;
		}
	}
}