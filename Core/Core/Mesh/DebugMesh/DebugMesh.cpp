#include "DebugMesh.h"
#include "../../Scene/Entity.h"

namespace OE1Core
{
	DebugMesh::DebugMesh(IVModel* _model)
		: CoreMesh(_model)
	{

	}

	DebugMesh::~DebugMesh()
	{

	}

	uint32_t DebugMesh::AddInstance(Entity* _entity)
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
	void DebugMesh::PurgeInstance(uint32_t _instanceID, Scene* _scene)
	{
		int del_idx = -1;
		for (size_t i = 0; i < m_MeshInstanceBuffers.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceBuffers[i], _scene);
			if (my_entity.GetComponent<Component::BoundingVolumeComponent>().GetUniqueInstanceID() == _instanceID)
			{
				del_idx = (int)i;
				break;
			}
		}

		if (del_idx == -1)
		{
			LOG_ERROR("ERROR PURGING <BoundingVolumeComponent> No Instance found with id: {0}", _instanceID);
			return;
		}
		m_MeshInstanceBuffers.erase(m_MeshInstanceBuffers.begin() + del_idx);

		for (size_t i = 0; i < m_MeshInstanceBuffers.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceBuffers[i], _scene);
			Component::BoundingVolumeComponent& my_mesh = my_entity.GetComponent<Component::BoundingVolumeComponent>();
			my_mesh.SetOffset(StaticMeshInstancePkgSize * i);
			my_mesh.Update();
		}
		UpdateInstanceDrawCount(MeshUtil::ICounter::DECREMENT);
	}

	uint64_t DebugMesh::GetShapeID()
	{ return m_ShapeID; }
	void DebugMesh::SetShapeID(uint64_t _id)
	{  m_ShapeID = _id; }

	GLenum DebugMesh::GetDrawMode()
	{ return m_DrawMode; }
	void DebugMesh::SetDrawMode(GLenum _mode)
	{ m_DrawMode = _mode; }
}