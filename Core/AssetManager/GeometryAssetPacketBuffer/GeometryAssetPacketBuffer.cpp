#include "GeometryAssetPacketBuffer.h"



namespace OE1Core
{
	namespace GeometryPacket
	{
		GeometryAssetPacketBuffer::~GeometryAssetPacketBuffer()
		{
			s_SkinnedIVModelData.clear();
		}
		uint32_t GeometryAssetPacketBuffer::RegisterStaticMeshGeometry(std::vector<DataBlock::Vertex>& _vert, std::vector<uint32_t>& _indices)
		{
			uint32_t __insert_id = s_GeometryCounter++;

			GeometryPacket::STATIC_MESH __mesh;
			__mesh.Indices = _indices;
			__mesh.Vertex = _vert;
			__mesh.Nth_Wave = s_StaticMeshGeometryCounter++;

			s_StaticMeshGeometryData.insert(std::make_pair(__insert_id, __mesh));

			return __insert_id;
		}
		uint32_t GeometryAssetPacketBuffer::RegisterSkinnedMeshGeometry(std::vector<DataBlock::WeightedVertex>& _vert, std::vector<uint32_t>& _indices)
		{
			uint32_t __insert_id = s_GeometryCounter++;

			GeometryPacket::SKINNED_MESH __mesh;
			__mesh.Indices = _indices;
			__mesh.Vertex = _vert;
			__mesh.Nth_Wave = s_SkinnedMeshGeometryCounter++;

			s_SkinnedMeshGeometryData.insert(std::make_pair(__insert_id, __mesh));

			return __insert_id;
		}

		GeometryPacket::STATIC_MESH* GeometryAssetPacketBuffer::GetStaticMeshGeometry(uint32_t _id)
		{
			if (s_StaticMeshGeometryData.find(_id) == s_StaticMeshGeometryData.end())
				return nullptr;

			return &s_StaticMeshGeometryData[_id];
		}
		GeometryPacket::SKINNED_MESH* GeometryAssetPacketBuffer::GetSkinnedMeshGeometry(uint32_t _id)
		{
			if (s_SkinnedMeshGeometryData.find(_id) == s_SkinnedMeshGeometryData.end())
				return nullptr;

			return &s_SkinnedMeshGeometryData[_id];
		}

		int GeometryAssetPacketBuffer::GetNumberOfStaticMeshGeometry()
		{
			return (int)s_StaticMeshGeometryCounter;
		}
		int GeometryAssetPacketBuffer::GetNumberOfSkinnedMeshGeometry()
		{
			return (int)s_SkinnedMeshGeometryCounter;
		}
		int GeometryAssetPacketBuffer::GetNumberOfRegistedMeshGeometry()
		{
			return (int)s_GeometryCounter;
		}


		uint32_t GeometryAssetPacketBuffer::RegisterSkinnedIVModelCustomData(std::map<std::string, DataBlock::BoneInfo>& _bones, std::vector<Animation*> _animations)
		{
			uint32_t __insert_id = s_IVModelCustomDataCounter++;

			GeometryPacket::IVModelSkinnedModelData __data;
			__data.BoneInfoMap = _bones;
			__data.Animations = _animations;


			s_SkinnedIVModelData.insert(std::make_pair(__insert_id, __data));

			return __insert_id;
		}
		void GeometryAssetPacketBuffer::UpdateSkinnedIVModelCustomData(uint32_t _id, std::map<std::string, DataBlock::BoneInfo>& _bones, std::vector<Animation*> _animations, bool _add_animation)
		{
			if (s_SkinnedIVModelData.find(_id) == s_SkinnedIVModelData.end())
				return;

			if (_add_animation)
			{
				for (size_t i = 0; i < _animations.size(); i++)
					s_SkinnedIVModelData[_id].Animations.push_back(_animations[i]);
			}else
				s_SkinnedIVModelData[_id].Animations = _animations;

			s_SkinnedIVModelData[_id].BoneInfoMap = _bones;
		}
		GeometryPacket::IVModelSkinnedModelData* GeometryAssetPacketBuffer::GetSkinnedIVModelCustomData(uint32_t _id)
		{
			if (s_SkinnedIVModelData.find(_id) == s_SkinnedIVModelData.end())
				return nullptr;

			return &s_SkinnedIVModelData[_id];
		}
	}
}