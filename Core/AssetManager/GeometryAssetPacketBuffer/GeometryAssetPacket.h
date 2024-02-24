#ifndef OE1_GEOMETRY_ASSET_PACKET_H_
#define OE1_GEOMETRY_ASSET_PACKET_H_


#include "../src/Util/DataBlock.h"
#include <vector>

namespace OE1Core
{
	namespace GeometryPacket
	{
		struct STATIC_MESH
		{
			std::vector<DataBlock::Vertex> Vertex;
			std::vector<uint32_t> Indices;
			uint32_t Nth_Wave;
		};

		struct SKINNED_MESH
		{
			std::vector<DataBlock::WeightedVertex> Vertex;
			std::vector<uint32_t> Indices;
			uint32_t Nth_Wave;
		};
	}
}

#endif // !OE1_GEOMETRY_ASSET_PACKET_H_
