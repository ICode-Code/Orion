#ifndef OE1_CORE_MESH_H_
#define OE1_CORE_MESH_H_


#include "../../Component/IComponent.h"
#include "../../MeshCluster/MeshUtil.h"
#include "../../MeshCluster/IVModel.h"
#include "../../MeshCluster/CoreMeshInstanceRenderDescriptor.h"

#include <string>
#include <vector>

namespace OE1Core
{
		namespace Renderer { class IVMasterRenderer; };

	class CoreMesh
	{
		friend class Renderer::IVMasterRenderer;
	public:
		CoreMesh() = default;
		CoreMesh(IVModel* _model);
		~CoreMesh();


		int GetInstanceCount() const;
		int GetVisibleInstanceCount() const;
		int GetIndicesCount() const;
		uint32_t GetPackageID() const;
		std::string GetName() const;
		bool IsValid() const;

		std::vector<CoreMeshInstanceRenderDescriptor>& GetCoreMeshInstanceDescriptorSet();
		virtual uint32_t AddInstance(class Entity* _entity) = 0;
		virtual void PurgeInstance(uint32_t _instance_id, class Scene* _scene) = 0;


	protected:
		int m_InstanceCount = 0;
		int m_VisibleInstanceCount = 0;
		int m_IndicesCount = 0;

		bool m_Valid = false;

		std::string m_CoreMeshName;
		uint32_t m_PackageID;

		// I don't know the purpose 
		std::vector<uint32_t> m_InstanceBuffers;

		std::vector<CoreMeshInstanceRenderDescriptor> m_CoreMeshInstanceDescriptorSet;
		std::vector<uint32_t> m_MeshInstanceBuffers;

	protected:
		/// <summary>
		/// This will increase or decrease the draw count for this
		/// mesh based on the arg
		/// </summary>
		/// <param name="_val"></param>
		void UpdateInstanceDrawCount(MeshUtil::ICounter _val);
	};
}

#endif // !OE1_CORE_MESH_H_
