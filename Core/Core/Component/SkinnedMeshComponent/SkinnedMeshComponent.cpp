#include "SkinnedMeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		SkinnedMeshComponent::SkinnedMeshComponent(uint32_t _package_id, uint32_t _unique_instance_id, GLintptr _offset, uint32_t _armature_id, std::vector<GLuint> _geometry_buffers, std::vector<uint32_t> _mat_offsets)
		{
			if (_mat_offsets.size() != _geometry_buffers.size())
			{
				LOG_ERROR("material offset count and geometry buffer count do not match! failed to create MeshComponent");
				return;
			}
			
			m_PackageID = _package_id;
			m_UniqueInstanceID = _unique_instance_id;
			m_Offset = _offset;
			m_Buffers = _geometry_buffers;
			m_MaterialIDs = _mat_offsets;

			m_CoreInstanceData.AnimationID = _armature_id;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
		}
		SkinnedMeshComponent::SkinnedMeshComponent(const SkinnedMeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset)
		{
			*this = _other;
			m_Offset = _offset;
			m_UniqueInstanceID = _unique_instance_id;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
		}

		SkinnedMeshComponent::~SkinnedMeshComponent()
		{

		}

		void SkinnedMeshComponent::SetArmatureBufferID(uint32_t _id)
		{

		}
		uint32_t SkinnedMeshComponent::GetArmatureBufferID() const
		{
			return m_ArmatureBufferID;
		}
		void SkinnedMeshComponent::SetOffset(GLintptr _offset)
		{
			m_Offset = _offset;
			m_CoreInstanceData.AnimationID = _offset;
		}
		GLintptr SkinnedMeshComponent::GetOffset() const
		{
			return m_Offset;
		}
		void SkinnedMeshComponent::Update(const glm::mat4& _transform)
		{
			m_CoreInstanceData.TransformComponent = _transform;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, DynamicMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}
		void SkinnedMeshComponent::Update()
		{
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, DynamicMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}

		uint32_t SkinnedMeshComponent::GetPackageID() const
		{
			return m_PackageID;
		}
		uint32_t SkinnedMeshComponent::GetUniqueInstanceID() const
		{
			return m_UniqueInstanceID;
		}
		DynamicMeshInstancePkg SkinnedMeshComponent::GetInstanceCore() const
		{
			return m_CoreInstanceData;
		}
	}
}