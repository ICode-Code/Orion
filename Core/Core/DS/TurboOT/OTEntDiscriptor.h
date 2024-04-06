#ifndef OE1_OCTREE_ENTITY_DISCRIPTOR_H_
#define OE1_OCTREE_ENTITY_DISCRIPTOR_H_

#include <glm/glm.hpp>
#include <functional>
#include "../Core/MeshCluster/CoreMeshDescriptor.h"

namespace OE1Core
{
	namespace DS
	{
		struct OTEntDiscriptor
		{
			uint32_t EntityID;
			glm::vec3 Position;
			std::function<void(void)> UpdateBuffer;
			std::function<void(int)> UpdateOffset;
			CoreMeshDescriptor::MeshBound Bound;
			bool Valid = false;
		};
	}

}
#endif // OE1_OCTREE_ENTITY_DISCRIPTOR_H_
