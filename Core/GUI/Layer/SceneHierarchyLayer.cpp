#include "SceneHierarchyLayer.h"


namespace OE1Core
{
	SceneHierarchyLayer::SceneHierarchyLayer()
	{
		m_NodeFlags = ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanFullWidth;
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

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 6 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 2 });
		ImGui::PushStyleColor(ImGuiCol_Header, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 0.0f, 0.439f, 0.878f, 1.0f });

		/*if (ImGui::IsMouseReleased(ImGuiMouseButton_Right) && ImGui::IsWindowHovered())
		{
			SceneEntityFactory::CreateFolderEntity("folder");
		}*/

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* package = ImGui::AcceptDragDropPayload(ORI_ENTITY_REPARENT_PACKAGE_PAYLOAD))
			{
				Entity entity = (*(Entity*)package->Data);
				Component::TransformComponent& transform = entity.GetComponent<Component::TransformComponent>();
				if (transform.m_Parent)
				{
					transform.RemoveParent();
				}
			}
			ImGui::EndDragDropTarget();
		}


		SceneManager::GetActiveScene()->m_EntityRegistry.each([&](auto _entt)
			{
				Entity _entity(_entt, SceneManager::GetActiveScene());
				
				Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();

				if (!transform.m_Parent)
					DrawEntityNode(_entity, SceneManager::GetActiveScene()->GetActiveEntity());
			});

		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		ImGui::End();
	}
	void SceneHierarchyLayer::DrawEntityNode(Entity& _entity, ActiveEntity* _active_entity)
	{

		Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
		Component::TagComponent& tag = _entity.GetComponent<Component::TagComponent>();

		ImGuiTreeNodeFlags flag_mod = (transform.IsLeaf() ? ImGuiTreeNodeFlags_Bullet : 0) | (((_active_entity->IsPicked(_entity)) ? ImGuiTreeNodeFlags_Selected : 0) | m_NodeFlags);
		bool is_node_open = ImGui::TreeNodeEx((void*)(uint64_t)(uint32_t)_entity, flag_mod, tag.GetRootFullName().c_str());
	

		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* package = ImGui::AcceptDragDropPayload(ORI_ENTITY_REPARENT_PACKAGE_PAYLOAD))
			{
				Entity new_child = (*(Entity*)package->Data);
				
				Component::TransformComponent& new_child_transform = new_child.GetComponent<Component::TransformComponent>();
				

				transform.AddChild(new_child);
			}
			ImGui::EndDragDropTarget();
		}
		

		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			ImGui::SetTooltip(tag.m_Identifier.c_str());

			ImGui::SetDragDropPayload(ORI_ENTITY_REPARENT_PACKAGE_PAYLOAD, &_entity, sizeof(Entity));

			ImGui::EndDragDropSource();
		}

		if (_entity.HasComponent<Component::CameraComponent>())
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetTooltip(tag.m_Identifier.c_str());

				ImGui::SetDragDropPayload("CameraPayload", &_entity.GetComponent<Component::SelfComponent>(), sizeof(Component::SelfComponent));

				ImGui::EndDragDropSource();
			}
		}

		if (_entity.HasComponent<Component::ThirdPersonCharacterControllerComponent>())
		{
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				ImGui::SetTooltip(tag.m_Identifier.c_str());
				
				ImGui::SetDragDropPayload("ActorPayload", &_entity.GetComponent<Component::SelfComponent>(), sizeof(Component::SelfComponent));

				ImGui::EndDragDropSource();
			}
		}


		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
		{
			SceneManager::GetActiveScene()->GetActiveEntity()->Pick(_entity);
		}
		if (ImGui::IsMouseReleased(ImGuiMouseButton_Right) && ImGui::IsItemHovered())
		{
			SceneManager::GetActiveScene()->GetActiveEntity()->Pick(_entity);
			//ImGui::BeginPopupContextItem();

			m_PopUpID = std::to_string(_entity.GetUUID());
			ImGui::OpenPopup(m_PopUpID.c_str());
			m_OpenedPopupEntityID = _entity.GetUUID();
			m_OpenEntityMiniPopupMenuPopup = true;

		}

		if(m_OpenedPopupEntityID == _entity.GetUUID())
			EntityMiniPopupMenu();

		if (is_node_open)
		{
			ImGui::Indent(32.0f);

			if (!transform.IsLeaf())
				for (auto _child : transform.m_Children)
					DrawEntityNode(*_child, _active_entity);

			ImGui::Indent(-32.0f);

			ImGui::TreePop();
		}
	}


	void SceneHierarchyLayer::EntityMiniPopupMenu()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 10, 6 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.05f, 0.5f });

		if (ImGui::BeginPopupContextItem(m_PopUpID.c_str()))
		{

			if (ImGui::Button("New Folder", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{
				SceneEntityFactory::CreateFolderEntity("New Folder");

				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Add Empty", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{
				SceneEntityFactory::CreateEmptyEntity("Empty");

				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Rename", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{
				Entity active = SceneManager::QueryActiveEntity()->GetActive();

				if (active.HasComponent<Component::TagComponent>())
					RenameWin::Open(active.GetComponent<Component::TagComponent>());
				
				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Mark as player", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{
				Entity active = SceneManager::QueryActiveEntity()->GetActive();
				
				SceneManager::GetActiveScene()->SetActivePlayerEntity(active);


				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Copy", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{

				ImGui::CloseCurrentPopup();
			}
			if (ImGui::Button("Purge", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
			{


				ImGui::CloseCurrentPopup();
			}

			if (SceneManager::QueryActiveEntity()->GetActive().HasComponent<Component::MeshComponent>())
			{
				if (ImGui::Button("Open with MeshEditor", { m_EntityMiniPopupMenuButtonWidth, 0.0f }))
				{
					

					ImGui::CloseCurrentPopup();
				}
			}


			ImGui::EndPopup();
		}


		ImGui::PopStyleVar(4);
	}

}