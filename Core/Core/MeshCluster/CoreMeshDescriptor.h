#ifndef OE1_MESH_BOUND_H_
#define OE1_MESH_BOUND_H_

#include <glm/glm.hpp>

namespace OE1Core
{
	namespace CoreMeshDescriptor
	{
		/// <summary>
		/// AABB
		/// </summary>
		struct MeshBound
		{
			glm::vec3 Min;
			glm::vec3 Max;
		};

		enum class CoreMeshType
		{
			STATIC,
			DYNAMIC
		};
	}
}

#endif // !OE1_MESH_BOUND_H_
