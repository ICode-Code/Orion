#include "StaticMesh.h"
#include "../../Scene/Entity.h"

namespace OE1Core
{
	StaticMesh::StaticMesh(ModelPkg* _pkg)
	{
		m_StaticMeshName = _pkg->Name;
		m_InstanceCount = 0;
		m_VisibleInstanceCount = 0;
		m_IndiceCount = _pkg->IndicesCount;
		m_PackageID = _pkg->PackageID;

		// Register mesh Package
		for (size_t i = 0; i < _pkg->MeshList.size(); i++)
		{
			lwStaticMeshPkg lw_mesh;

			lw_mesh.DrawCount			= 0;
			lw_mesh.IBO					= _pkg->MeshList[i].IBO;
			lw_mesh.VAO					= _pkg->MeshList[i].VAO;
			lw_mesh.Material			= _pkg->MeshList[i].Material;
			lw_mesh.IndiceCount			= _pkg->MeshList[i].IndiceCount;
			lw_mesh.MaterialID			= _pkg->MeshList[i].MaterialID;
			lw_mesh.PackageID			= _pkg->MeshList[i].PackageID;

			m_StaticMeshPkg.push_back(lw_mesh);
		}

	}
	StaticMesh::~StaticMesh()
	{

	}

	uint32_t StaticMesh::AddIntance(Entity* _entity)
	{
		uint32_t my_entity = (uint32_t)_entity->GetHandle();

		UpdateInstanceCount(ICounter::INCREMENT);
		auto iter = std::find_if(m_MeshInstanceData.begin(), m_MeshInstanceData.end(), [my_entity](uint32_t _id) {
			return _id == my_entity;
			});
		if (iter == m_MeshInstanceData.end())
			m_MeshInstanceData.push_back(my_entity);

		return (uint32_t)((m_MeshInstanceData.size() - 1) * StaticMeshInstancePkgSize);
	}
	void StaticMesh::RemoveInstance(uint32_t _instanceID, Scene* _scene)
	{
		int del_idx = -1;
		for (size_t i = 0; i < m_MeshInstanceData.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceData[i], _scene);
			if (my_entity.GetComponent<Component::MeshComponent>().GetUniqueInstanceID() == _instanceID)
			{
				del_idx = (int)i;
				break;
			}
		}

		if (del_idx == -1)
		{
			LOG_ERROR("No Instance found with id: {0}", _instanceID);
			return;
		}
		m_MeshInstanceData.erase(m_MeshInstanceData.begin() + del_idx);
		m_MeshInstanceData.pop_back();

		for (size_t i = 0; i < m_MeshInstanceData.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceData[i], _scene);
			my_entity.GetComponent<Component::MeshComponent>().SetOffset(StaticMeshInstancePkgSize * i);
		}
		UpdateInstanceCount(ICounter::DECREMENT);
	}

	void StaticMesh::UpdateInstanceCount(ICounter _update_value)
	{
		for (size_t i = 0; i < m_StaticMeshPkg.size(); i++)
			m_StaticMeshPkg[i].DrawCount += (int)_update_value;
	}
	const std::vector<lwStaticMeshPkg>& StaticMesh::GetMeshpackage()
	{
		return m_StaticMeshPkg;
	}
	uint32_t StaticMesh::GetPackageID() const { return m_PackageID; }
	std::string StaticMesh::GetName() const { return m_StaticMeshName; }
	int StaticMesh::GetInstanceCount() const { return m_InstanceCount; }
	int StaticMesh::GetVisibleInstanceCount() const { return m_VisibleInstanceCount; }
}