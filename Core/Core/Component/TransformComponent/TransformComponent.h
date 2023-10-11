#ifndef OE1_TRANSFORM_COMPONENT_H_
#define OE1_TRANSFORM_COMPONENT_H_



#include <imgui/imgui.h>
#include <imgui/ImGuizmo.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_Transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Bullet/btBulletDynamicsCommon.h>
#include <optional>
#include <vector>
#include <memory>


namespace OE1Core
{
	class Entity;
	class ProxyTransform;
	namespace Component
	{
		/// <summary>
		// Constructor to initialize the TransformComponent with an optional owner entity.
		// The owner entity establishes a relationship between the TransformComponent and the entity it belongs to.
		// If no entity is provided, the TransformComponent can be used in non-entity-related contexts.
		/// </summary>
		class TransformComponent
		{
			friend class ProxyTransform;
			friend class InspectorComponent;
		public:
			TransformComponent(Entity* _owner_entity = nullptr);
			TransformComponent(glm::vec3 _position, Entity* _owner_entity = nullptr);
			TransformComponent(const TransformComponent&) = delete;
			~TransformComponent();


		public:
			void ExtractTransform(const glm::mat4& _src_transform);
			void ReadTransform(const btTransform& _src_transform);
			void SetRotation(glm::quat _rot);
			glm::vec3 GetFront();
			glm::vec3 Getback();
			glm::vec3 GetRight();
			glm::vec3 GetUp();
			bool IsDirty();
			bool IsLeaf();
			void Update();
			glm::mat4& QueryLocalTransform();
			glm::mat4& QueryWorldTransform();

			// operators
			inline operator glm::mat4& () { return m_WorldTransform;  };
			inline operator const glm::mat4& () const { return m_WorldTransform; };



			// Scene Hierarchy
			Entity GetHostEntity();
			void SetHostEntity(Entity _entity);
			void SetParent(Entity _entity);
			void RemoveParent();
			void AddChild(Entity _entity);
			void RemoveChild(Entity _entity);
			bool HasChild(Entity _entity);
			bool HasChild(Entity _test_owner_entity, Entity _test_chid_entity);

		public:
			glm::vec3 m_Position;
			glm::vec3 m_Scale;
			glm::vec3 m_Euler;
			glm::quat m_Quaternion;
			glm::mat4 m_RotationFinal;

			Entity*					m_HostEntity = nullptr;
			Entity*					m_Parent = nullptr;
			std::vector<Entity*>	m_Children;


		protected:
			glm::mat4 m_WorldTransform;
			glm::mat4 m_LocalTransform;
			bool m_Dirty = true;
			bool m_Leaf = true;

		protected:
			void __Init(Entity* _owner_entity);
			void __UpdateHierarchy(Entity* _entity);
			glm::mat4 __ComputeWorldTransform();
			glm::mat4 __ComputeLocalTransform();
			bool __IsDecendent(Entity* _entity);
		};
	}
}

#endif // !OE1_TRANSFORM_COMPONENT_H_
