#include "StaticMesh.h"
#include "../../Scene/Entity.h"

namespace OE1Core
{
	StaticMesh::StaticMesh(IVModel* _model)
		: CoreMesh{_model}
	{
	}
	StaticMesh::~StaticMesh()
	{

	}

	uint32_t StaticMesh::AddInstance(Entity* _entity)
	{
		uint32_t my_entity = (uint32_t)_entity->GetHandle();

		UpdateInstanceDrawCount(MeshUtil::ICounter::INCREMENT);
		auto iter = std::find_if(m_MeshInstanceBuffers.begin(), m_MeshInstanceBuffers.end(), [my_entity](uint32_t _id) {
			return _id == my_entity;
			});
		if (iter == m_MeshInstanceBuffers.end())
			m_MeshInstanceBuffers.push_back(my_entity);

		return (uint32_t)((m_MeshInstanceBuffers.size() - 1) * StaticMeshInstancePkgSize);
	}
	void StaticMesh::PurgeInstance(uint32_t _instanceID, Scene* _scene)
	{
		int del_idx = -1;
		for (size_t i = 0; i < m_MeshInstanceBuffers.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceBuffers[i], _scene);
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
		m_MeshInstanceBuffers.erase(m_MeshInstanceBuffers.begin() + del_idx);

		for (size_t i = 0; i < m_MeshInstanceBuffers.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceBuffers[i], _scene);
			Component::MeshComponent& my_mesh = my_entity.GetComponent<Component::MeshComponent>();
			my_mesh.SetOffset(StaticMeshInstancePkgSize * i);
			my_mesh.Update();
		}
		UpdateInstanceDrawCount(MeshUtil::ICounter::DECREMENT);
	}

}