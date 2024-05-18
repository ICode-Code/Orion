#include "InspectorComponent.h"
#include "../IComponent.h"
#include "../Core/Scene/SceneManager.h"
#include "../GUI/GUIBase.h"


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
			ICamera();
			IActor();
			IMesh();
			ISkinnedMesh();
			IAnimationComponent();
			ICamController();
			IThirdPersonCameraControllerComponent();
			IThirdPersonCharacterControllerComponent();


			ImGui::PopStyleColor(7);
			ImGui::PopStyleVar(3);
		}
		void InspectorComponent::SetTagComponent(TagComponent* _tag_component) { m_TagComponent = _tag_component; }
		void InspectorComponent::SetTransformComponent(TransformComponent* _transform) { m_TransformComponent = _transform; };
		void InspectorComponent::SetMeshComponent(MeshComponent* _mesh) { m_MeshComponent = _mesh; }
		void InspectorComponent::SetCameraControllerComponent(BaseCameraControllerComponent* _camera_controller) { m_BaseCameraControllerComponent = _camera_controller; }
		void InspectorComponent::SetCameraComponent(CameraComponent* _camera_component) { m_CameraComponent = _camera_component; }
		void InspectorComponent::SetSkinnedMeshComponent(SkinnedMeshComponent* _skinned_mesh_component) { m_SkinnedMeshComponent = _skinned_mesh_component;  };
		void InspectorComponent::SetAnimationComponent(AnimationComponent* _animation_component) { m_AnimationComponent = _animation_component; }
		void InspectorComponent::SetThirdPersonCameraControllerComponent(ThirdPersonCameraControllerComponent* _tp_camera_Controller_component) { m_ThirdPersonCameraControllerComponent = _tp_camera_Controller_component; };
		void InspectorComponent::SetThirdPersonCharacterControllerComponent(ThirdPersonCharacterControllerComponent* _tp_character_Controller_component) { m_ThirdPersonCharacterControllerComponent = _tp_character_Controller_component; };
		void InspectorComponent::SetActorComponent(ActorComponent* _actor) { m_ActorComponent = _actor; };
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
		void InspectorComponent::IActor()
		{
			if (!m_ActorComponent)
				return;

			if (ImGui::TreeNodeEx("Actor", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent(16.0f);

				static int crt = 0;
				static std::string _target_camera_name = "Drop Camera Here..";
				static std::string _target_chararacter_name = "Drop Character Here..";
				ImGui::SetNextItemWidth(200);

				ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.2f , 0.2f, 1.0f });
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });

				ImGui::Combo("Target Camera", &crt, _target_camera_name.c_str());
				

				if (ImGui::BeginDragDropTarget())
				{

					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CameraPayload"))
					{
						Component::SelfComponent* _self = static_cast<Component::SelfComponent*>(payload->Data);

						if (_self)
						{
							Entity _entity((entt::entity)_self->GetEntityID(), SceneManager::GetActiveScene());

							if(SceneManager::GetActiveScene()->GetProtagonist())
							{
								_target_camera_name = _entity.GetComponent<Component::TagComponent>().m_Identifier;
								SceneManager::GetActiveScene()->GetProtagonist()->SetCamera(&_entity.GetComponent<Component::CameraComponent>());
							}
						}
					}

					ImGui::EndDragDropTarget();
				}

				ImGui::SetNextItemWidth(200);

				ImGui::Combo("Target Chararcter", &crt, _target_chararacter_name.c_str());
				
				if (ImGui::BeginDragDropTarget())
				{

					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ActorPayload"))
					{
						Component::SelfComponent* _self = static_cast<Component::SelfComponent*>(payload->Data);
						if (_self)
						{
							Entity _entity((entt::entity)_self->GetEntityID(), SceneManager::GetActiveScene());
							if (SceneManager::GetActiveScene()->GetProtagonist())
							{
								_target_chararacter_name = _entity.GetComponent<Component::TagComponent>().m_Identifier;
								SceneManager::GetActiveScene()->GetProtagonist()->SetActorEntity(&_entity);
							}
						}
					}

					ImGui::EndDragDropTarget();
				}

				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor();

				

				ImGui::Indent(-16.0f);

				ImGui::TreePop();
			}
		}
		void InspectorComponent::IMesh()
		{
			if (!m_MeshComponent)
				return;
			if (ImGui::TreeNodeEx("Mesh Component", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent(16.0f);

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 5 });
				IVModel* package = AssetManager::GetGeometry(m_MeshComponent->GetPackageID());

				IVModelInspect(package);


				if (ImGui::TreeNodeEx("Volume", m_TreeNodeFlags))
				{
					ImGui::Indent(16.0f);


					IVModelBoundVolume(package);

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 1, 1 });
					ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });

					if (CustomFrame::UIEditorCheckbox("Render Volume", &m_MeshComponent->m_ShowBoundVolume))
					{
						Entity _entity((entt::entity)m_MeshComponent->GetUniqueInstanceID(), SceneManager::GetActiveScene());
						
						if (m_MeshComponent->m_ShowBoundVolume)
							SceneEntityFactory::AddBoundingVolumeComponent(_entity, package);
						else
							SceneEntityFactory::RemoveBoundingVolumeComponent(_entity);
					}

					ImGui::PopStyleColor(2);
					ImGui::PopStyleVar();
					


					ImGui::Indent(-16.0f);
					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx("LOD", m_TreeNodeFlags))
				{
					ImGui::Indent(16.0f);


					ImGui::Indent(-16.0f);
					ImGui::TreePop();
				}

				ImGui::PopStyleVar();
				ImGui::Indent(-16.0f);
				ImGui::TreePop();
			}

		}
		void InspectorComponent::ISkinnedMesh()
		{
			if (!m_SkinnedMeshComponent)
				return;

			if (ImGui::TreeNodeEx("Skinned Mesh Component", m_TreeNodeFlags | ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent(16.0f);

				ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 5 });
				IVModel* package = AssetManager::GetGeometry(m_SkinnedMeshComponent->GetPackageID());

				IVModelInspect(package);


				if (ImGui::TreeNodeEx("Volume", m_TreeNodeFlags))
				{
					ImGui::Indent(16.0f);


					IVModelBoundVolume(package);

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 1, 1 });
					ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });

					if (CustomFrame::UIEditorCheckbox("Render Volume", &m_SkinnedMeshComponent->m_ShowBoundVolume))
					{
						Entity _entity((entt::entity)m_SkinnedMeshComponent->GetUniqueInstanceID(), SceneManager::GetActiveScene());

						if (m_SkinnedMeshComponent->m_ShowBoundVolume)
							SceneEntityFactory::AddBoundingVolumeComponent(_entity, package);
						else
							SceneEntityFactory::RemoveBoundingVolumeComponent(_entity);
					}

					ImGui::PopStyleColor(2);
					ImGui::PopStyleVar();



					ImGui::Indent(-16.0f);
					ImGui::TreePop();
				}
				ImGui::PopStyleVar();
				ImGui::Indent(-16.0f);
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

				
				ImGui::SetNextWindowSize({ 300.0f, 400.0f });
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1);

				if(ImGui::BeginPopup("animation-list"))
				{

					ImGui::PushStyleColor(ImGuiCol_Button, { 0.15f, 0.15f, 0.15f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_Border, { 1.0f, 1.0f, 1.0f, 1.0f });
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2);
					ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0f, 0.5f });

					for (auto iter = AssetManager::GetAnimationRegistry().begin(); iter != AssetManager::GetAnimationRegistry().end(); iter++)
					{
						std::string _name = ICON_FA_CODE_BRANCH"\t" + iter->first;

						if (ImGui::Button(_name.c_str(), { 290.0f, 0.0f }))
						{
							DynamicMesh* dynamic_mesh = SceneManager::GetActiveScene()->QueryDynamicMesh(m_SkinnedMeshComponent->GetPackageID());

							Animation* _animation = dynamic_mesh->GetAnimation(iter->first);
							if (_animation)
								m_AnimationComponent->SwitchAnimation(_animation);

						}


						if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
						{
							DynamicMesh* dynamic_mesh = SceneManager::GetActiveScene()->QueryDynamicMesh(m_SkinnedMeshComponent->GetPackageID());
							Animation* package_payload = dynamic_mesh->GetAnimation(iter->first);


							ImGui::SetDragDropPayload("bind_anim_payload", package_payload, sizeof(Animation));
							
							ImGui::BeginTooltip();

							ImGui::Text("Name: %s", package_payload->GetName().c_str());
							ImGui::Text("Bone Count: %i", package_payload->GetBoneCount());
							ImGui::Text("Duration: %f", package_payload->GetDuration());

							ImGui::EndTooltip();

							ImGui::EndDragDropSource();
						}
					}
					ImGui::PopStyleVar(2);
					ImGui::PopStyleColor(2);

					ImGui::EndPopup();
				}

				ImGui::PopStyleVar();

				if (m_AnimationComponent->m_Animation)
				{

					CustomFrame::UIEditorTextValue("Name", m_AnimationComponent->m_Animation->m_Name.c_str());
					CustomFrame::UIEditorTextValue("Duration",std::to_string(m_AnimationComponent->m_Animation->GetDuration()).c_str());
					CustomFrame::UIEditorTextValue("Ticks/Sec",std::to_string(m_AnimationComponent->m_Animation->GetTicksPerSecond()).c_str());
					CustomFrame::UIEditorTextValue("Bone Count",std::to_string(m_AnimationComponent->m_Animation->GetBoneCount()).c_str());
					CustomFrame::UIEditorFloat("Speed", &m_AnimationComponent->m_Animation->m_DeltaFactor, 0.2f, 2.0f, "%.3f");
					CustomFrame::UIEditorFloat("Blend Speed", &m_AnimationComponent->m_Animation->m_TransitionDuration, 0.0f, 1.0f, "%.5f");

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 1, 1 });
					ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });

					CustomFrame::UIEditorCheckbox("Hard Cut", &m_AnimationComponent->m_Animation->m_HardCut);

					ImGui::PopStyleColor(2);
					ImGui::PopStyleVar();
					

					if (ImGui::TreeNodeEx("Advanced", m_TreeNodeFlags))
					{
						ImGui::Indent(16.0f);

						
						if(ImGui::TreeNodeEx("Playback", m_TreeNodeFlags))
						{
							ImGui::Indent(16.0f);

							ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0, 0 });
							ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
							ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
							ImGui::PushStyleColor(ImGuiCol_PlotHistogram, { 0.15f, 0.15f, 0.15f, 1.0f });

							float _prog = (m_AnimationComponent->m_Animation->m_CurrentTime / m_AnimationComponent->m_Animation->m_Duration);
							ImGui::Text("Timeline:");
							ImGui::ProgressBar(_prog, { 0.0f, 0.0f });

							ImGui::PopStyleColor();
							ImGui::PopStyleVar(3);

							ImGui::Indent(-16.0f);

							ImGui::TreePop();
						}
						
						if (ImGui::TreeNodeEx("Hierarchy", m_TreeNodeFlags))
						{
							ImGui::Indent(8.0f);

							IterateBone(&m_AnimationComponent->m_Animation->GetRootNode());

							ImGui::Indent(-8.0f);
							ImGui::TreePop();
						}


						if (ImGui::TreeNodeEx("Bones", m_TreeNodeFlags))
						{
							ImGui::Indent(16.0f);
							
							ImGui::PushStyleColor(ImGuiCol_Button, { 0.08f, 0.08f , 0.08f, 1.0f });
							ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
							ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0f, 0.5f });

							for (size_t i = 0; i < m_AnimationComponent->m_Animation->m_Bones.size(); i++)
							{
								std::string _bone_name = ICON_FA_BONE"\t" + m_AnimationComponent->m_Animation->m_Bones[i].m_Name;
								ImGui::Button(_bone_name.c_str(), { 200.0f, 0.0f });
							}

							ImGui::PopStyleVar(2);
							ImGui::PopStyleColor();

							ImGui::Indent(-16.0f);
							ImGui::TreePop();
						}


						ImGui::Indent(-16.0f);
						ImGui::TreePop();
					}
				

					ImGui::Indent(-16.0f); 

				}


				ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f , 0.1f, 1.0f });
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });

				if (ImGui::Button("Load...", { 80.0f, 0.0f }))
				{
					std::string loaded_file = WindowFileDialog::LoadFile("GLTF and FBX Files (*.gltf;*.glb;*.fbx)\0*.gltf;*.glb;*.fbx\0", WindowManager::GetEngineWindow()->GetWin(), "Load Animation");
					if (!loaded_file.empty())
					{
						CommandDef::AnimationLoadCommandDef _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
						_command.Path = loaded_file;
						_command.PackageID = m_SkinnedMeshComponent->GetPackageID();

						Command::PushAnimationLoadCommand(_command);
					}
				}

				ImGui::SameLine();

				if (ImGui::Button("Select Animation", { 80.0f, 0.0f }))
					ImGui::OpenPopup("animation-list");

				ImGui::SameLine();

				if (ImGui::Button("State Machine", { 80.0f, 0.0f }))
				{
					AnimationManager::RegisterStateMachineWindow(m_TagComponent->m_Identifier, new AnimationStateMachinePad(m_AnimationComponent, m_TagComponent->m_Identifier));
				}

				


				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor();

				/*if (ImGui::Button(ICON_FA_LINK))
					m_AnimationComponent->LinkStateMachine();*/
				ImGui::Indent(-16.0f);
				ImGui::TreePop();
			}
		}
		/*void InspectorComponent::ICameraPackage()
		{
			if (!m_CameraPackageComponent)
				return;
			 
			

		}*/
		void InspectorComponent::IThirdPersonCameraControllerComponent()
		{
			if (!m_ThirdPersonCameraControllerComponent)
				return;

			if (ImGui::TreeNodeEx("TP Camera Controller", m_TreeNodeFlags))
			{

				ImGui::Indent(16.0f);

				bool _has_target_to_follow = m_ThirdPersonCameraControllerComponent->GetTargetTransform() != nullptr;


				ImGui::PushStyleColor(ImGuiCol_Text, _has_target_to_follow ? ImVec4(0.090f, 0.725f, 0.471f, 1.0f) : ImVec4(1.0f, 0.121f, 0.353f, 1.0f));
				
				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.0f, 0.0f });

				ImGui::Button(_has_target_to_follow ? ICON_FA_CIRCLE_CHECK : ICON_FA_TRIANGLE_EXCLAMATION);

				if (ImGui::IsItemHovered())
				{
					if (_has_target_to_follow)
						ImGui::SetTooltip(ICON_FA_CIRCLE_INFO"\tReady!");
					else 
						ImGui::SetTooltip(ICON_FA_CIRCLE_INFO"\tTarget to Follow");
				}

				ImGui::PopStyleColor(3);

				ImGui::SameLine();
				static int crt = 0;
				static std::string _target_name = "...";
				ImGui::SetNextItemWidth(200);

				ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.2f , 0.2f, 1.0f });
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });

				ImGui::Combo("Target to Follow", &crt, _target_name.c_str());

				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor();

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ActorPayload"))
					{
						Component::SelfComponent* _self = static_cast<Component::SelfComponent*>(payload->Data);
						if (_self)
						{

							Entity _entity((entt::entity)_self->GetEntityID(), SceneManager::GetActiveScene());

							if (_entity.HasComponent<Component::ThirdPersonCharacterControllerComponent>())
							{
								_target_name = _entity.GetComponent<Component::TagComponent>().m_Identifier;
								m_ThirdPersonCameraControllerComponent->SetTargetTransform(&_entity.GetComponent<Component::TransformComponent>());
								
								_entity.GetComponent<Component::ThirdPersonCharacterControllerComponent>().SetCameraComponent(m_ThirdPersonCameraControllerComponent->GetCameraComponent());
							}
							else
							{
								LogLayer::Pipe("Entity Doesn't Have Any <CharacterControllerComponent>", OELog::WARNING);
							}

						}

					}
					/*if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CameraPayload"))
					{
						Component::SelfComponent* _self = static_cast<Component::SelfComponent*>(payload->Data);
						if (_self)
						{
							Entity _entity((entt::entity)_self->GetEntityID(), SceneManager::GetActiveScene());

							Component::CameraComponent* _camera = &_entity.GetComponent<Component::CameraComponent>();
							_camera->SetController(m_ThirdPersonCameraControllerComponent);
							m_ThirdPersonCameraControllerComponent->SetCameraComponent(_camera);
						}*/
						//Component::CameraPackageComponent* package = (Component::CameraPackageComponent*)payload->Data;

						//// get real ptr
						//CameraPackage* camera_pkg_ptr = SceneManager::GetActiveScene()->GetCameraManager()->GetCamera(package->GetCameraPackage()->GetName());
						//_target_name = camera_pkg_ptr->GetName();
						//// Link
						//camera_pkg_ptr->SetCameraController(m_ThirdPersonCameraControllerComponent);
						//m_ThirdPersonCameraControllerComponent->SetCameraComponent(camera_pkg_ptr->GetCamera());

						//SceneManager::GetActiveScene()->GetCameraManager()->RegisterActiveGameCamera(camera_pkg_ptr->GetName());
					
					//}

					ImGui::EndDragDropTarget();
				}

				
				



				if (ImGui::TreeNodeEx("Pitch Constrain", m_TreeNodeFlags))
				{

					CustomFrame::UIEditorFloat("Max", &m_ThirdPersonCameraControllerComponent->m_PitchConstrainMax, 45.0f, 89.0f);
					CustomFrame::UIEditorFloat("Min", &m_ThirdPersonCameraControllerComponent->m_PitchConstrainMin, -89.0f, 45.0f);
					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx("Control", m_TreeNodeFlags))
				{

					CustomFrame::UIEditorFloat("Sensitivity", &m_ThirdPersonCameraControllerComponent->m_Sensitivity, 0.001f, 0.5f);

					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 1, 1 });
					ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });

					CustomFrame::UIEditorCheckbox("Flip Mouse Control", &m_ThirdPersonCameraControllerComponent->m_FlipMouse);
					
					ImGui::PopStyleColor(2);
					ImGui::PopStyleVar();

					CustomFrame::UIEditorFloatDrag("Distance To Target", &m_ThirdPersonCameraControllerComponent->m_DistanceToTarget, 0.1f);
					CustomFrame::UIEditorFloatDrag("Camera Height", &m_ThirdPersonCameraControllerComponent->m_FocusHeight, 0.1f);
					CustomFrame::UIEditorFloatDrag("Shift Right Focus", &m_ThirdPersonCameraControllerComponent->m_ShiftRightCameraFocus, 0.1f, -5.0f, 5.0f);
				
					ImGui::TreePop();
				}

				ImGui::Indent(-16.0f);

				ImGui::TreePop();
			}
		}
		void InspectorComponent::IThirdPersonCharacterControllerComponent()
		{
			if (!m_ThirdPersonCharacterControllerComponent)
				return;




			if (ImGui::TreeNodeEx("TP Character Controller", m_TreeNodeFlags))
			{
				ImGui::Indent(16.0f);

				/*bool _has_target_camera = m_ThirdPersonCharacterControllerComponent->GetCameraComponent() != nullptr;


				ImGui::PushStyleColor(ImGuiCol_Text, _has_target_camera ? ImVec4(0.090f, 0.725f, 0.471f, 1.0f) : ImVec4(1.0f, 0.121f, 0.353f, 1.0f));

				ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.0f, 0.0f, 0.0f, 0.0f });
				ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.0f, 0.0f, 0.0f, 0.0f });

				ImGui::Button(_has_target_camera ? ICON_FA_CIRCLE_CHECK : ICON_FA_TRIANGLE_EXCLAMATION);

				if (ImGui::IsItemHovered())
				{
					if (_has_target_camera) 
						ImGui::SetTooltip(ICON_FA_CIRCLE_INFO"\tCharacter-Controller is ready!");
					else
						ImGui::SetTooltip(ICON_FA_CIRCLE_INFO"\tDrag and Drop a target camera here!");
				}

				ImGui::PopStyleColor(3);

				ImGui::SameLine();
				static int crt = 0;
				static std::string _target_name = "...";
				ImGui::SetNextItemWidth(200);

				ImGui::PushStyleColor(ImGuiCol_Button, { 0.2f, 0.2f , 0.2f, 1.0f });
				ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
				ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.5f, 0.5f });

				ImGui::Combo("Target Camera", &crt, _target_name.c_str());

				ImGui::PopStyleVar(2);
				ImGui::PopStyleColor();


				if (ImGui::BeginDragDropTarget())
				{

					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CameraPayload"))
					{
						Component::SelfComponent* _self = static_cast<Component::SelfComponent*>(payload->Data);
						if (_self)
						{
							Entity _entity((entt::entity)_self->GetEntityID(), SceneManager::GetActiveScene());
							m_ThirdPersonCharacterControllerComponent->SetCameraComponent(&_entity.GetComponent<Component::CameraComponent>());
						}
					}

					ImGui::EndDragDropTarget();
				}*/


				CustomFrame::UIEditorFloat("Walk Speed", &m_ThirdPersonCharacterControllerComponent->m_WalkSpeed, 1.0f, 32.0f);
				CustomFrame::UIEditorFloat("Run Speed", &m_ThirdPersonCharacterControllerComponent->m_SprintSpeed, 1.0f, 128.0f);
				CustomFrame::UIEditorFloat("Turn Speed", &m_ThirdPersonCharacterControllerComponent->m_TurnSpeed, 10.0f, 360.0f);

				ImGui::Indent(-16.0f);

				ImGui::TreePop();
			}
		}
		void InspectorComponent::ICamController()
		{
			if (!m_BaseCameraControllerComponent)
				return;


			if (ImGui::TreeNodeEx("Base Controller", m_TreeNodeFlags))
			{
				
				CustomFrame::UIEditorFloat("Smoothness", &m_BaseCameraControllerComponent->m_LerpThreshold, 0.01f, 2.0f);
				CustomFrame::UIEditorFloat("Velocity", &m_BaseCameraControllerComponent->m_Speed, 0.0f, 256.0f);
				CustomFrame::UIEditorFloat("Velocity Factor", &m_BaseCameraControllerComponent->m_SpeedFactor, 0.0f, 256.0f);


				ImGui::TreePop();
			}

		}
		void InspectorComponent::ICamera()
		{
			if (!m_CameraComponent)
				return;

			if (ImGui::TreeNodeEx("Camera", m_TreeNodeFlags))
			{

				CustomFrame::UIEditorColor3("Background", glm::value_ptr(m_CameraComponent->m_Background));
				CustomFrame::UIEditorInt("Field of View", &m_CameraComponent->m_FieldOfView, 1, 100);
				
				ImGui::Indent(16.0f);

				if (ImGui::TreeNodeEx("Clipping Planes", m_TreeNodeFlags))
				{

					CustomFrame::UIEditorFloatDrag("Near Plane", &m_CameraComponent->m_Near);
					CustomFrame::UIEditorFloatDrag("Far Plane", &m_CameraComponent->m_Far);

					ImGui::TreePop();
				}

				if (ImGui::TreeNodeEx("Culling", m_TreeNodeFlags))
				{
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 1, 1 });
					ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.2f, 0.2f, 0.2f, 1.0f });
					ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.2f, 0.2f, 0.2f, 1.0f });

					CustomFrame::UIEditorCheckbox("Frustum Cull", &m_CameraComponent->m_Cull);

					ImGui::PopStyleColor(2);
					ImGui::PopStyleVar();

					ImGui::TreePop();
				}

				ImGui::Indent(-16.0f);


				ImGui::TreePop();
			}
		}

		void InspectorComponent::IVModelInspect(IVModel* package)
		{

			if (ImGui::TreeNodeEx("Sub-Meshs", m_TreeNodeFlags + ImGuiTreeNodeFlags_DefaultOpen))
			{
				ImGui::Indent(16.0f);


				for (size_t i = 0; i < package->SubMeshs.size(); i++)
				{
					if (ImGui::TreeNodeEx(package->SubMeshs[i].Material->GetName().c_str(), m_TreeNodeFlags))
					{
						ImGui::Indent(16.0f);

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

						ImGui::Indent(-16.0f);

						ImGui::TreePop();
					}
				}



				ImGui::Indent(-16.0f);
				ImGui::TreePop();
			}

			if (ImGui::TreeNodeEx("Detail", m_TreeNodeFlags))
			{
				ImGui::Indent(16.0f);

				CustomFrame::UIEditorTextValue("Name", package->Name.c_str());
				//CustomFrame::UIEditorTextValue("Unique Instance ID", std::to_string(m_MeshComponent->m_UniqueInstanceID).c_str());
				//CustomFrame::UIEditorTextValue("Buffer Offset", std::to_string(m_MeshComponent->m_Offset).c_str());
				CustomFrame::UIEditorTextValue("package ID", std::to_string(package->PackageID).c_str());
				CustomFrame::UIEditorTextValue("Indice Count", std::to_string(package->TotalIndicesCount).c_str());
				CustomFrame::UIEditorTextValue("SubMesh Count", std::to_string(package->SubMeshCount).c_str());
				CustomFrame::UIEditorTextValue("Triangle Count", std::to_string(package->TotalTriangleCount).c_str());
				CustomFrame::UIEditorTextValue("Vertex Count", std::to_string(package->TotalVertexCount).c_str());
				CustomFrame::UIEditorTextValue("Material Count", std::to_string(package->SubMeshCount).c_str());


				if (ImGui::TreeNodeEx("Preview", m_TreeNodeFlags))
				{
					ImGui::Indent(16.0f);

					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
					ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
					ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
					ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10.0f, 10.0f });

					if (CustomFrame::UIEditorImageButton("Mesh Preview", (ImTextureID)(uintptr_t)package->Preview, { 70, 70 }, { 0, 1 }, {1, 0}))
					 { }

					ImGui::PopStyleVar(3);
					ImGui::PopStyleColor();

					ImGui::Indent(-16.0f);
					ImGui::TreePop();
				}

				ImGui::Indent(-16.0f);
				ImGui::TreePop();
			}

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
		void InspectorComponent::IVModelBoundVolume(IVModel* _model)
		{

			if (ImGui::TreeNodeEx("Bound", m_TreeNodeFlags))
			{
				ImGui::Indent(16.0f);
				ImGui::BeginDisabled();

				CustomFrame::UIEditorf3<glm::vec3>("Maximum", _model->Bound.Max, 0.0f, 100.0f);
				CustomFrame::UIEditorf3<glm::vec3>("Minimum", _model->Bound.Min, 0.0f, 100.0f);


				ImGui::EndDisabled();
				ImGui::Indent(-16.0f);
				ImGui::TreePop();
			}
		}
	}
}