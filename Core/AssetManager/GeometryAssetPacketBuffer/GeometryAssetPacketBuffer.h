#ifndef OE1_GEOMETRY_BUFFER_H_
#define OE1_GEOMETRY_BUFFER_H_


#include "GeometryAssetPacket.h"
#include <unordered_map>

namespace OE1Core
{
	namespace GeometryPacket 
	{
		class GeometryAssetPacketBuffer
		{
		public:
			GeometryAssetPacketBuffer() = delete;
			~GeometryAssetPacketBuffer() = delete;


			static uint32_t RegisterStaticMeshGeometry(std::vector<DataBlock::Vertex>& _vert, std::vector<uint32_t>& _indices);
			static uint32_t RegisterSkinnedMeshGeometry(std::vector<DataBlock::WeightedVertex>& _vert, std::vector<uint32_t>& _indices);

			static GeometryPacket::STATIC_MESH* GetStaticMeshGeometry(uint32_t _id);
			static GeometryPacket::SKINNED_MESH* GetSkinnedMeshGeometry(uint32_t _id);

			static int GetNumberOfStaticMeshGeometry();
			static int GetNumberOfSkinnedMeshGeometry();
			static int GetNumberOfRegistedMeshGeometry();

		private:
			inline static std::unordered_map<uint32_t, GeometryPacket::STATIC_MESH> s_StaticMeshGeometryData;
			inline static std::unordered_map<uint32_t, GeometryPacket::SKINNED_MESH> s_SkinnedMeshGeometryData;
			
			inline static uint32_t s_GeometryCounter = 0;
			inline static uint32_t s_StaticMeshGeometryCounter = 0;
			inline static uint32_t s_SkinnedMeshGeometryCounter = 0;
		};
	}
}

#endif // !OE1_GEOMETRY_BUFFER_H_
