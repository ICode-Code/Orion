#include "SkinnedMeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		SkinnedMeshComponent::SkinnedMeshComponent(uint32_t _package_id, uint32_t _unique_instance_id, GLintptr _offset, uint32_t _armature_id, std::vector<GLuint> _geometry_buffers, std::vector<uint32_t> _mat_offsets)
		{

		}
		SkinnedMeshComponent::SkinnedMeshComponent(const SkinnedMeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset)
		{

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
			
		}
		GLintptr SkinnedMeshComponent::GetOffset() const
		{
			return m_Offset;
		}
		void SkinnedMeshComponent::Update(const glm::mat4& _transform)
		{

		}
		void SkinnedMeshComponent::Update()
		{

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