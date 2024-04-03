#include "CoreMesh.h"


namespace OE1Core
{
	CoreMesh::CoreMesh(IVModel* _model)
	{
		if (!_model)
			return;


		m_CoreMeshName = _model->Name;
		m_InstanceCount = 0;
		m_VisibleInstanceCount = 0;
		m_IndicesCount = _model->TotalIndicesCount;
		m_PackageID = _model->PackageID;

		m_Valid = _model->SubMeshs.size() > 0;

		for (size_t i = 0; i < _model->SubMeshs.size(); i++)
		{
			CoreMeshInstanceRenderDescriptor mesh_desc;

			mesh_desc.DrawCount = 0;
			mesh_desc.VAO = _model->SubMeshs[i].VAO;
			mesh_desc.IBO = _model->SubMeshs[i].IBO;
			mesh_desc.Material = _model->SubMeshs[i].Material;
			mesh_desc.VertexCount = _model->SubMeshs[i].VertexCount;
			mesh_desc.IndiceCount = _model->SubMeshs[i].IndicesCount;
			mesh_desc.Type = _model->SubMeshs[i].MeshType;
			mesh_desc.MaterialID = _model->SubMeshs[i].MaterialID;
			mesh_desc.PackageID = _model->SubMeshs[i].PackageID;

			m_CoreMeshInstanceDescriptorSet.push_back(mesh_desc);
		}
	}
	CoreMesh::~CoreMesh()
	{

	}

	int CoreMesh::GetInstanceCount() const { return m_InstanceCount; }
	int CoreMesh::GetVisibleInstanceCount() const { return m_VisibleInstanceCount; }
	int CoreMesh::GetIndicesCount() const { return m_IndicesCount; }
	uint32_t CoreMesh::GetPackageID() const { return m_PackageID; }
	std::string CoreMesh::GetName() const { return m_CoreMeshName; }
	bool CoreMesh::IsValid() const { return m_Valid; }


	std::vector<CoreMeshInstanceRenderDescriptor>& CoreMesh::GetCoreMeshInstanceDescriptorSet()
	{
		return m_CoreMeshInstanceDescriptorSet;
	}

	void CoreMesh::UpdateInstanceDrawCount(MeshUtil::ICounter _val)
	{
		m_InstanceCount += (int)_val;
		m_VisibleInstanceCount += (int)_val;
		for (size_t i = 0; i < m_CoreMeshInstanceDescriptorSet.size(); i++)
			m_CoreMeshInstanceDescriptorSet[i].DrawCount += (int)_val;
	}
}