#include "TransformComponent.h"
#include "../../Scene/Entity.h"
#include <imgui/ImGuizmo.h>


namespace OE1Core
{
	namespace Component
	{
		TransformComponent::TransformComponent(Entity* _owner_entity)
		{

			__Init(_owner_entity);
		}
		TransformComponent::TransformComponent(glm::vec3 _position, Entity* _owner_entity)
		{

			
			__Init(_owner_entity);
		}
		TransformComponent::~TransformComponent()
		{
			if (m_HostEntity)
				delete m_HostEntity;

			if (m_Parent)
				delete m_Parent;

			for (auto child : m_Children)
				delete child;
		}
		void TransformComponent::__Init(Entity* _owner_entity)
		{
			if (_owner_entity)
				m_HostEntity = new Entity(_owner_entity->GetHandle(), _owner_entity->GetScene());
			m_Position = glm::vec3(0.0f);
			m_Scale = glm::vec3(1.0f);
			m_Euler = glm::vec3(0.0f);
			m_Quaternion = glm::quat(glm::radians(m_Euler));
			m_RotationFinal = glm::toMat4(m_Quaternion);
		}
		void TransformComponent::__UpdateHierarchy(Entity* _entity)
		{
			Component::TransformComponent& transform = _entity->GetComponent<Component::TransformComponent>();
			transform.__ComputeWorldTransform();

			for (size_t i = 0; i < transform.m_Children.size(); i++)
			{
				__UpdateHierarchy(transform.m_Children[i]);
				transform.m_Children[i]->UpdateTransformBuffer();
			}
		}
		glm::mat4 TransformComponent::__ComputeWorldTransform()
		{
			if (m_Parent)
				return m_WorldTransform = m_Parent->GetComponent<TransformComponent>().__ComputeWorldTransform() * __ComputeLocalTransform();
			else
				return m_WorldTransform = __ComputeLocalTransform();
		}
		glm::mat4 TransformComponent::__ComputeLocalTransform()
		{
			m_Dirty = false;
			m_Quaternion = glm::quat(glm::radians(m_Euler));
			m_RotationFinal = glm::toMat4(m_Quaternion);
			return m_LocalTransform = glm::translate(glm::mat4(1.0f), m_Position) *
				m_RotationFinal *
				glm::scale(glm::mat4(1.0f), m_Scale);
		}
		void TransformComponent::ExtractTransform(const glm::mat4& _src_transform)
		{
			// extract
			ImGuizmo::DecomposeMatrixToComponents(
				glm::value_ptr(_src_transform),
				glm::value_ptr(m_Position),
				glm::value_ptr(m_Euler),
				glm::value_ptr(m_Scale)
			);
		}
		void TransformComponent::ReadTransform(const btTransform& _src_transform)
		{
			_src_transform.getOpenGLMatrix(glm::value_ptr(m_WorldTransform));
			m_WorldTransform = glm::scale(m_WorldTransform, m_Scale);
			ExtractTransform(m_WorldTransform);
		}
		void TransformComponent::SetRotation(glm::quat _rot)
		{
			m_Quaternion = _rot;
			m_Euler = glm::degrees(glm::eulerAngles(m_Quaternion));
			m_Dirty = true;
		}

		glm::mat4& TransformComponent::QueryLocalTransform() { return m_LocalTransform; }
		glm::mat4& TransformComponent::QueryWorldTransform() { return m_WorldTransform; }
		void TransformComponent::Update()
		{
			// TODO what if the Transform Component does not related to any entity
			// Host Entity is nullptr
			__UpdateHierarchy(m_HostEntity);
		}

		glm::vec3 TransformComponent::GetFront()	{ return -m_LocalTransform[2]; }
		glm::vec3 TransformComponent::Getback()		{ return m_LocalTransform[2]; }
		glm::vec3 TransformComponent::GetRight()	{ return m_LocalTransform[0]; }
		glm::vec3 TransformComponent::GetUp()		{ return m_LocalTransform[1]; }
		bool TransformComponent::IsDirty()			{ return m_Dirty; }
		bool TransformComponent::IsLeaf()			{ return m_Leaf; }

		void TransformComponent::SetHostEntity(Entity _entity)
		{
			if (m_HostEntity)
			{
				delete m_HostEntity;
				m_HostEntity = new Entity(_entity.GetHandle(), _entity.GetScene());
			} else 
				m_HostEntity = new Entity(_entity.GetHandle(), _entity.GetScene());
		}
		Entity TransformComponent::GetHostEntity()
		{
			if (m_HostEntity)
				return *m_HostEntity;
			return Entity();
		}

		void TransformComponent::SetParent(Entity _entity)
		{
			if (_entity.IsFunctional())
			{
				if (m_Parent)
					m_Parent->GetComponent<TransformComponent>().RemoveChild(*this->m_HostEntity);

				m_Parent = new Entity(_entity);
				_entity.GetComponent<TransformComponent>().AddChild(*this->m_HostEntity);
			}
			else
				m_Parent = nullptr;
		}
		void TransformComponent::RemoveParent()
		{
			if (m_Parent)
			{
				glm::vec3 _Position;
				glm::vec3 _Scale;
				glm::vec3 __Rot;
				
				ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(QueryWorldTransform()), glm::value_ptr(_Position), glm::value_ptr(__Rot), glm::value_ptr(_Scale));

				m_Position = _Position;
				m_Scale = _Scale;
				m_Euler = __Rot;

				m_Parent->GetComponent<TransformComponent>().RemoveChild(*this->m_HostEntity);
			}
		}
		void TransformComponent::AddChild(Entity _entity)
		{
			if (!HasChild(_entity))
			{
				if (__IsDecendent(&_entity))
					return;
				// check entity parent
				Component::TransformComponent& new_child_transform = _entity.GetComponent<Component::TransformComponent>();
				if (new_child_transform.m_Parent)
					new_child_transform.m_Parent->GetComponent<Component::TransformComponent>().RemoveChild(_entity);


				m_Children.push_back(new Entity(_entity.GetHandle(), _entity.GetScene()));
				_entity.GetComponent<Component::TransformComponent>().SetParent(*this->m_HostEntity);

				/// Compute proper transform
				glm::mat4 inverse_new_parent_transform = glm::inverse(m_WorldTransform);
				Component::TransformComponent& child_transform = m_Children.back()->GetComponent<Component::TransformComponent>();
				glm::mat4 _trans = inverse_new_parent_transform * child_transform.QueryWorldTransform();


				glm::vec3 _Position;
				glm::vec3 _Scale;
				glm::vec3 __Rot;

				ImGuizmo::DecomposeMatrixToComponents(glm::value_ptr(_trans), glm::value_ptr(_Position), glm::value_ptr(__Rot), glm::value_ptr(_Scale));

				child_transform.m_Position = _Position;
				child_transform.m_Scale = _Scale;
				child_transform.m_Euler = __Rot;




				m_Leaf = false;
			}

		}
		void TransformComponent::RemoveChild(Entity _entity)
		{
			if (HasChild(_entity))
			{

				// unlink
				delete _entity.GetComponent<TransformComponent>().m_Parent;
				_entity.GetComponent<TransformComponent>().m_Parent = nullptr;

				// Remove the child entity from the parent's children list
				auto it = std::find_if(m_Children.begin(), m_Children.end(), [&](Entity* __ent) {
					return _entity == *__ent;
					});

				if (it != m_Children.end())
				{
					delete *it; // Deallocate memory for the child entity
					m_Children.erase(it);
				}

				if(m_Children.empty())
					m_Leaf = true;;

			}
		}
		bool TransformComponent::HasChild(Entity _entity)
		{
			auto search_result = std::find_if(m_Children.begin(), m_Children.end(), [&](Entity* __ent)
				{
					return _entity == *__ent;
				});

			if (search_result != m_Children.end())
				return true;

			return false;
		}
		bool TransformComponent::HasChild(Entity _test_owner_entity, Entity _test_chid_entity)
		{
			auto& test_owner_children = _test_owner_entity.GetComponent<TransformComponent>().m_Children;
			auto search_result = std::find_if(test_owner_children.begin(), test_owner_children.end(), [&](Entity* __ent)
				{
					return _test_chid_entity == *__ent;
				});

			if (search_result != test_owner_children.end())
				return true;

			return false;
		}
		bool TransformComponent::__IsDecendent(Entity* _entity)
		{
			Component::TransformComponent& transform = _entity->GetComponent<Component::TransformComponent>();
			if (!_entity || !transform.m_Parent)
				return false;

			if (_entity->GetUUID() == transform.m_Parent->GetUUID())
				return true;

			// Recursively check the parent of the current entity
			return __IsDecendent(transform.m_Parent);
		}
	}
}