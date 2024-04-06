#include "MeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		
		MeshComponent::MeshComponent(CoreMeshArg _arg)
			: CoreRenderableMeshComponent{ _arg }
		{
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
		}
		MeshComponent::MeshComponent(const MeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset)
			: CoreRenderableMeshComponent{ _other, _unique_instance_id, _offset }
		{
			m_ShowBoundVolume = _other.m_ShowBoundVolume;
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
		void MeshComponent::Update()
		{
			for (size_t i = 0; i < m_Buffers.size(); i++)
			{
				m_CoreInstanceData.MaterialID = m_MaterialIDs[i];
				glBindBuffer(GL_ARRAY_BUFFER, m_Buffers[i]);
				glBufferSubData(GL_ARRAY_BUFFER, m_Offset, StaticMeshInstancePkgSize, &m_CoreInstanceData);
			}
		}
		void MeshComponent::UpdateBuffers() { this->Update(); }
		StaticMeshInstancePkg MeshComponent::GetInstanceData() const { return m_CoreInstanceData; }
	}
}