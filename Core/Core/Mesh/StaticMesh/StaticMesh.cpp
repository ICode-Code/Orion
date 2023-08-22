#include "StaticMesh.h"


namespace OE1Core
{
	StaticMesh::StaticMesh(StaticMeshPkg _pkg)
	{
		m_StaticMeshName = _pkg.Name;
		m_InstanceCount = 0;
		m_VisibleInstanceCount = 0;
		m_InstanceCount = _pkg.IndiceCout;
		m_CoreMeshID = _pkg.CoreMeshID;

	}
	StaticMesh::~StaticMesh()
	{

	}

	std::string StaticMesh::GetName() const { return m_StaticMeshName; }
	int StaticMesh::GetInstanceCount() const { return m_InstanceCount; }
	int StaticMesh::GetVisibleInstanceCount() const { return m_VisibleInstanceCount; }
}