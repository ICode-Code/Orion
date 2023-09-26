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


		if (ImGui::IsMouseReleased(ImGuiMouseButton_Left) && ImGui::IsItemHovered())
		{
			SceneManager::GetActiveScene()->GetActiveEntity()->Pick(_entity);
		}

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

}