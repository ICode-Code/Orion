#include "TransformComponent.h"
#include "../../Scene/Entity.h"


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

		glm::mat4 TransformComponent::GetLocalTransform()
		{
			m_Dirty = false;
			m_Quaternion = glm::quat(glm::radians(m_Euler));
			m_RotationFinal = glm::toMat4(m_Quaternion);
			return m_LocalTransform =	glm::translate(glm::mat4(1.0f), m_Position) *
										m_RotationFinal *
										glm::scale(glm::mat4(1.0f), m_Scale);
		}
		glm::mat4 TransformComponent::GetWorldTransform()
		{
			if (m_Parent)
				return m_WorldTransform = m_Parent->GetComponent<TransformComponent>().GetWorldTransform() * GetLocalTransform();
			else
				return m_WorldTransform = GetLocalTransform();
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
				m_Parent->GetComponent<TransformComponent>().RemoveChild(*this->m_HostEntity);
		}
		void TransformComponent::AddChild(Entity _entity)
		{
			if (!HasChild(_entity))
			{
				m_Children.push_back(new Entity(_entity.GetHandle(), _entity.GetScene()));
				_entity.GetComponent<Component::TransformComponent>().SetParent(*this->m_HostEntity);
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
					m_Children.erase(it);
					delete* it; // Deallocate memory for the child entity
				}

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
	}
}