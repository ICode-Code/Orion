#ifndef OE1_STATIC_MESH_H_
#define OE1_STATIC_MESH_H_


#include "../../MeshCluster/lwStaticMeshPkg.h"
#include "../../MeshCluster/ModelPkg.h"
#include "StaticMeshUtil.h"
#include "../../Component/IComponent.h"


#include <string>
#include <vector>

namespace OE1Core
{
	namespace Renderer { class IVMasterRenderer; };
	class StaticMesh
	{
		friend class Renderer::IVMasterRenderer;
	public:
		StaticMesh() = default;
		StaticMesh(ModelPkg* _pkg);
		~StaticMesh();

		const std::vector<lwStaticMeshPkg>& GetMeshpackage();
		uint32_t GetPackageID() const;
		std::string GetName() const;
		int GetInstanceCount() const;
		int GetVisibleInstanceCount() const;

		uint32_t AddIntance(class Entity* _entity);
		void RemoveInstance(uint32_t _instanceID, class Scene* _scene);

	private:
		int								m_InstanceCount = 0;
		int								m_VisibleInstanceCount = 0;
		int								m_IndiceCount = 0;
		std::string						m_StaticMeshName;
		uint32_t						m_PackageID;
		std::vector<lwStaticMeshPkg>	m_StaticMeshPkg;
		std::vector<uint32_t>			m_InstanceBuffers;
		std::vector<uint32_t>			m_MeshInstanceData;

	protected: // Util
		void UpdateInstanceCount(ICounter _update_value);
	};
}


#endif // !OE1_STATIC_MESH_H_
