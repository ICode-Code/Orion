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
			ISkinnedMesh();
			IAnimationComponent();
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
		void InspectorComponent::SetSkinnedMeshComponent(class SkinnedMeshComponent* _skinned_mesh_component) { m_SkinnedMeshComponent = _skinned_mesh_component;  };
		void InspectorComponent::SetAnimationComponent(class AnimationComponent* _animation_component) { m_AnimationComponent = _animation_component; }

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
				IVModel* package = AssetManager::GetGeometry(m_MeshComponent->GetPackageID());

				IVModelInspect(package);

				ImGui::PopStyleVar();

				ImGui::TreePop();
			}

		}
		void InspectorComponent::ISkinnedMesh()
		{
			if (!m_SkinnedMeshComponent)
				return;

			if (ImGui::TreeNodeEx("Skinned Mesh Component", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 4 });
				IVModel* package = AssetManager::GetGeometry(m_SkinnedMeshComponent->GetPackageID());

				IVModelInspect(package);

				ImGui::PopStyleVar();

				ImGui::TreePop();
			}
		}
		void InspectorComponent::IAnimationComponent()
		{
			if (!m_AnimationComponent)
				return;

			if (ImGui::TreeNodeEx("Animation Component", m_TreeNodeFlags))
			{

				ImGui::Indent(16.0f);

				if (ImGui::Button("Load..", { 100.0f, 25.0f }))
				{
					std::string loaded_file = WindowFileDialog::LoadFile("GLTF and FBX Files (*.gltf;*.glb;*.fbx)\0*.gltf;*.glb;*.fbx\0", WindowManager::GetWindow(ENGINE_MAIN_WINDOW)->GetWin(), "Load Animation");
					if (!loaded_file.empty())
					{
						CommandDef::AnimationLoadCommandDef _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
						_command.Path = loaded_file;
						_command.PackageID = m_SkinnedMeshComponent->GetPackageID();

						Command::PushAnimationLoadCommand(_command);
					}
				}

				if (ImGui::TreeNodeEx("Animation List", m_TreeNodeFlags))
				{

					for (auto iter = AssetManager::GetAnimationRegistry().begin(); iter != AssetManager::GetAnimationRegistry().end(); iter++)
					{
						if (ImGui::Button(iter->first.c_str(), { 200.0f, 25.0f }))
						{
							SceneManager::GetActiveScene()->QueryDynamicMesh(m_SkinnedMeshComponent->GetPackageID())->SetActiveAnimation(iter->first);
							m_AnimationComponent->m_Animation = SceneManager::GetActiveScene()->QueryDynamicMesh(m_SkinnedMeshComponent->GetPackageID())->GetActiveAnimation();
						}
					}


					ImGui::TreePop();
				}
				CustomFrame::UIEditorTextValue("Name", m_AnimationComponent->m_Animation->m_Name.c_str());
				CustomFrame::UIEditorTextValue("Duration",std::to_string(m_AnimationComponent->m_Animation->GetDuration()).c_str());
				CustomFrame::UIEditorTextValue("Ticks/Sec",std::to_string(m_AnimationComponent->m_Animation->GetTicksPerSecond()).c_str());
				CustomFrame::UIEditorTextValue("Bone Count",std::to_string(m_AnimationComponent->m_Animation->GetBoneCount()).c_str());
				CustomFrame::UIEditorFloat("Speed", &m_AnimationComponent->m_Animation->m_DeltaFactor, 0.2f, 2.0f, "%.3f");

				ImGui::Separator();

				ImGui::Indent(8.0f);

				IterateBone(&m_AnimationComponent->m_Animation->GetRootNode());
				
				ImGui::Indent(-8.0f);

				ImGui::Separator();

				if (ImGui::TreeNodeEx("Bone Set", m_TreeNodeFlags))
				{
					for (size_t i = 0; i < m_AnimationComponent->m_Animation->m_Bones.size(); i++)
					{
						CustomFrame::UIEditorLabel(m_AnimationComponent->m_Animation->m_Bones[i].m_Name.c_str());
					}

					ImGui::TreePop();
				}
				

				ImGui::Indent(-16.0f);

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

		void InspectorComponent::IVModelInspect(IVModel* package)
		{
			for (size_t i = 0; i < package->SubMeshs.size(); i++)
			{
				ImGui::Indent(16.0f);
				if (ImGui::TreeNodeEx(package->SubMeshs[i].Material->GetName().c_str(), m_TreeNodeFlags + ImGuiTreeNodeFlags_DefaultOpen))
				{
					MasterMaterial* ActiveMat = package->SubMeshs[i].Material;

					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });

					if (CustomFrame::UIEditorImageButton("Orion Material", (ImTextureID)(uintptr_t)ActiveMat->GetPreviewRef(), { 60, 60 }))
					{
						if (MaterialManager::GetMaterialView().size() < ORI_MATERIAL_WINDOW_ALLOCATION_THRESHOLD)
						{
							MaterialManager::RegisterMaterialView(MaterialManager::GetMaterial(package->SubMeshs[i].MaterialID));
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
					bool has_color_map = package->SubMeshs[i].Material->HasColorMap();
					bool has_non_color_map = package->SubMeshs[i].Material->HasNonColorMap();

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
			//CustomFrame::UIEditorTextValue("Unique Instance ID", std::to_string(m_MeshComponent->m_UniqueInstanceID).c_str());
			//CustomFrame::UIEditorTextValue("Buffer Offset", std::to_string(m_MeshComponent->m_Offset).c_str());
			CustomFrame::UIEditorTextValue("package ID", std::to_string(package->PackageID).c_str());
			CustomFrame::UIEditorTextValue("Indice Count", std::to_string(package->TotalIndicesCount).c_str());
			CustomFrame::UIEditorTextValue("SubMesh Count", std::to_string(package->SubMeshCount).c_str());
			CustomFrame::UIEditorTextValue("Triangle Count", std::to_string(package->TotalTriangleCount).c_str());
			CustomFrame::UIEditorTextValue("Vertex Count", std::to_string(package->TotalVertexCount).c_str());
			CustomFrame::UIEditorTextValue("Material Count", std::to_string(package->SubMeshCount).c_str());


			CustomFrame::UIEditorImage("Preview", (ImTextureID)(uintptr_t)package->Preview, { 100, 100 });


		}

		void InspectorComponent::IterateBone(struct AnimNode* _node)
		{
			ImGuiTreeNodeFlags flag_mod = (_node->ChildCount == 0 ? ImGuiTreeNodeFlags_Bullet : 0) | ImGuiTreeNodeFlags_Framed;
			
			bool is_node_open = ImGui::TreeNodeEx(_node->Name.c_str(), flag_mod, _node->Name.c_str());
			
			if (is_node_open)
			{
				ImGui::Indent(8.0f);

				for (size_t i = 0; i < _node->ChildCount; i++)
					IterateBone(&_node->Children[i]);

				ImGui::Indent(-8.0f);

				ImGui::TreePop();
			}
		}
	}
}