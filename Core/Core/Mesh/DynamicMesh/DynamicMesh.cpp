#include "DynamicMesh.h"
#include "../../Scene/Entity.h"

namespace OE1Core
{
	DynamicMesh::DynamicMesh(IVModel* _model)
		: CoreMesh { _model }
	{
		auto _data = GeometryPacket::GeometryAssetPacketBuffer::GetSkinnedIVModelCustomData(_model->DataIdx);
		
		for (size_t i = 0; i < _data->Animations.size(); i++)
			m_AnimationList.insert(std::make_pair(_data->Animations[i]->GetName(), _data->Animations[i]));
		
	}
	DynamicMesh::~DynamicMesh()
	{

	}
	void DynamicMesh::UpdateData(GeometryPacket::IVModelSkinnedModelData* _geometry_packet)
	{
		for (size_t i = 0; i < _geometry_packet->Animations.size(); i++)
			m_AnimationList.insert(std::make_pair(_geometry_packet->Animations[i]->GetName(), _geometry_packet->Animations[i]));

	}
	uint32_t DynamicMesh::AddInstance(Entity* _entity)
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
	void DynamicMesh::PurgeInstance(uint32_t _instanceID, Scene* _scene)
	{
		int del_idx = -1;
		for (size_t i = 0; i < m_MeshInstanceBuffers.size(); i++)
		{
			Entity my_entity((entt::entity)m_MeshInstanceBuffers[i], _scene);
			if (my_entity.GetComponent<Component::SkinnedMeshComponent>().GetUniqueInstanceID() == _instanceID)
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
			Component::SkinnedMeshComponent& my_mesh = my_entity.GetComponent<Component::SkinnedMeshComponent>();
			my_mesh.SetOffset(StaticMeshInstancePkgSize * i);
			my_mesh.Update();
		}
		UpdateInstanceDrawCount(MeshUtil::ICounter::DECREMENT);
	}

	void DynamicMesh::RegisterAnimation(Animation* _animation)
	{
		if (m_AnimationList.find(_animation->GetName()) != m_AnimationList.end())
			return;

		m_AnimationList.insert(std::make_pair(_animation->GetName(), _animation));
		m_AnimationCount++;
	}
	void DynamicMesh::PurgeAnimation(std::string _name)
	{
		if (m_AnimationList.find(_name) == m_AnimationList.end())
			return;

		m_AnimationList.erase(_name);
	}
	Animation* DynamicMesh::GetAnimation(std::string _name)
	{
		if (m_AnimationList.find(_name) == m_AnimationList.end())
			return nullptr;

		return m_AnimationList[_name];
	}
	std::unordered_map<std::string, Animation*>& DynamicMesh::GetAnimationList()
	{
		return m_AnimationList;
	}

}