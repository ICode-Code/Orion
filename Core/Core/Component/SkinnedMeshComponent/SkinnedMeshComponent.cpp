#include "SkinnedMeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		SkinnedMeshComponent::SkinnedMeshComponent(CoreMeshArg _arg, uint32_t _armature_id, int _bone_count)
			: CoreRenderableMeshComponent{ _arg }
		{

			m_BoneCount = _bone_count;
			m_CoreInstanceData.AnimationID = _armature_id;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
			m_CoreInstanceData.AnimationBufferIndex = 0;
		}
		SkinnedMeshComponent::SkinnedMeshComponent(
			const SkinnedMeshComponent& _other, 
			uint32_t _unique_instance_id, 
			GLintptr _offset,
			uint32_t _armature_id)

			: CoreRenderableMeshComponent{ _other, _unique_instance_id, _offset }
		{
			m_ShowBoundVolume = _other.m_ShowBoundVolume;
			m_CoreInstanceData.RenderID = m_UniqueInstanceID;
			m_CoreInstanceData.AnimationID = _armature_id;
		}

		SkinnedMeshComponent::~SkinnedMeshComponent()
		{
		}

		void SkinnedMeshComponent::SetArmatureBufferIndex(int _id) { m_CoreInstanceData.AnimationBufferIndex = _id; }

		int SkinnedMeshComponent::GetArmatureBufferID() const { return m_CoreInstanceData.AnimationID; }
		
		void SkinnedMeshComponent::Update(const glm::mat4& _transform)
		{
			m_CoreInstanceData.TransformComponent = _transform;
	
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
		void SkinnedMeshComponent::UpdateBuffers() { this->Update(); }

		DynamicMeshInstancePkg SkinnedMeshComponent::GetInstanceData() const { return m_CoreInstanceData; }
	}
}