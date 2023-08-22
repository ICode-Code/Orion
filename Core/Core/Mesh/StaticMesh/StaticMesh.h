#ifndef OE1_STATIC_MESH_H_
#define OE1_STATIC_MESH_H_

#include <string>
#include <vector>

#include "../../MeshCluster/lwStaticMeshPkg.h"

namespace OE1Core
{
	struct StaticMeshPkg
	{
		std::vector<lwStaticMeshPkg> Package;
		std::string Name;
		uint32_t CoreMeshID;
		int IndiceCout;
	};
	class StaticMesh
	{
	public:
		StaticMesh() = default;
		StaticMesh(StaticMeshPkg _pkg);
		~StaticMesh();

		std::string GetName() const;
		int GetInstanceCount() const;
		int GetVisibleInstanceCount() const;

	private:
		int								m_InstanceCount = 0;
		int								m_VisibleInstanceCount = 0;
		int								m_IndiceCount = 0;
		std::string						m_StaticMeshName;
		uint32_t						m_CoreMeshID;
		std::vector<lwStaticMeshPkg*>	m_StaticMeshPkg;
		std::vector<uint32_t>			m_InstanceBuffers;
	};
}


#endif // !OE1_STATIC_MESH_H_
