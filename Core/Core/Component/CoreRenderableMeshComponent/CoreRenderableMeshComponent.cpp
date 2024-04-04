#include "CoreRenderableMeshComponent.h"


namespace OE1Core
{
	namespace Component
	{
		CoreRenderableMeshComponent::CoreRenderableMeshComponent(CoreMeshArg _arg)
		{
			m_UniqueInstanceID = _arg.InstanceID;
			m_PackageID = _arg.PackageID;
			m_Offset = _arg.Offset;
			
			m_Buffers = _arg.GeometryBuffer;
			m_MaterialIDs = _arg.MaterialAccessIndices;

			if (m_Buffers.size() != m_MaterialIDs.size())
			{
				LOG_ERROR("material offset count and geometry buffer count do not match! failed to create MeshComponent");
			}
		}

		CoreRenderableMeshComponent::CoreRenderableMeshComponent(
			const CoreRenderableMeshComponent& _other,
			uint32_t _instance_id,
			GLintptr _offset)
		{
			*this = _other;
			m_UniqueInstanceID = _instance_id;
			m_Offset = _offset;
		}

		CoreRenderableMeshComponent::~CoreRenderableMeshComponent()
		{

		}

		void CoreRenderableMeshComponent::SetOffset(GLintptr _offset) { m_Offset = _offset; }
		GLintptr CoreRenderableMeshComponent::GetOffset() const { return m_Offset; }


		uint32_t CoreRenderableMeshComponent::GetPackageID() const { return m_PackageID; }
		uint32_t CoreRenderableMeshComponent::GetUniqueInstanceID() const { return m_UniqueInstanceID; }
	}
}