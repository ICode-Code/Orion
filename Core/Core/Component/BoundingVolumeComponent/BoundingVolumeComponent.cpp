#include "BoundingVolumeComponent.h"


namespace OE1Core
{
	namespace Component
	{
		BoundingVolumeComponent::BoundingVolumeComponent(uint32_t _pkg_id, std::vector<GLuint> _buffers, uint32_t _unique_id, GLintptr _offset, glm::vec3 _min, glm::vec3 _max)
		{
			m_PackageID = _pkg_id;
			m_InstanceBuffers = _buffers;
			m_UniqueInstanceID = _unique_id;
			m_Offset = _offset;
			m_Bound.Min = _min;
			m_Bound.Max = _max;
		}
		BoundingVolumeComponent::BoundingVolumeComponent(const BoundingVolumeComponent& _other, uint32_t _unique_id, GLintptr _offset)
		{
			m_PackageID = _other.m_PackageID;
			m_InstanceBuffers = _other.m_InstanceBuffers;
			m_Bound = _other.m_Bound;

			m_UniqueInstanceID = _unique_id;
			m_Offset = _offset;
		}
		BoundingVolumeComponent::~BoundingVolumeComponent()
		{

		}

		void BoundingVolumeComponent::SetOffset(GLintptr _offset)
		{
			m_Offset = _offset;
		}
		GLintptr BoundingVolumeComponent::GetOffset() const
		{
			return m_Offset;
		}
		void BoundingVolumeComponent::Update(const glm::mat4& _transform)
		{
			m_CoreInstanceData.TransformComponent = _transform;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;

			for (size_t i = 0; i < m_InstanceBuffers.size(); i++)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBuffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
		void BoundingVolumeComponent::Update()
		{
			for (size_t i = 0; i < m_InstanceBuffers.size(); i++)
			{
				glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBuffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
		}
		uint32_t BoundingVolumeComponent::GetPackageID() const { return m_PackageID; }
		uint32_t BoundingVolumeComponent::GetUniqueInstanceID() const { return m_UniqueInstanceID; }
		StaticMeshInstancePkg BoundingVolumeComponent::GetInstanceCore() const { return m_CoreInstanceData; }
		CoreMeshDescriptor::MeshBound BoundingVolumeComponent::GetBound() { return m_Bound; };
	}
}