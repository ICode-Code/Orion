#include "MeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		
		MeshComponent::MeshComponent(uint32_t _package_id, uint32_t _unique_instance_id, GLintptr _offset, std::vector<GLuint> _geometry_buffers, std::vector<uint32_t> _mat_offsets)
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

			m_CoreInstanceData.RenderID = m_UniqueInstanceID;

		}
		MeshComponent::MeshComponent(const MeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset)
		{
			*this = _other;
			m_Offset = _offset;
			m_UniqueInstanceID = _unique_instance_id;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
		}
		MeshComponent::~MeshComponent()
		{

		}
		void MeshComponent::Update(const glm::mat4& _transform)
		{
			m_CoreInstanceData.TransformComponent = _transform;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}
		void MeshComponent::Update(glm::mat4 _transform)
		{
			m_CoreInstanceData.TransformComponent = _transform;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}
		void MeshComponent::Update()
		{
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}

		void MeshComponent::SetOffset(GLintptr _offset)
		{
			m_Offset = _offset;
		}
		GLintptr MeshComponent::GetOffset() const { return m_Offset; }
		uint32_t MeshComponent::GetPackageID() const { return m_PackageID; }
		uint32_t MeshComponent::GetUniqueInstanceID() const { return m_UniqueInstanceID; }
		StaticMeshInstancePkg MeshComponent::GetInstanceCore() const { return m_CoreInstanceData; }
	}
}