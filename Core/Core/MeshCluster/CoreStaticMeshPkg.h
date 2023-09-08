#ifndef OE1_CORE_STATIC_MESH_PKG_H_
#define OE1_CORE_STATIC_MESH_PKG_H_

#include <Util/DataBlock.h>
#include <glm/glm.hpp>

namespace OE1Core
{
	struct CoreStaticMeshPkg
	{
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		unsigned int IBO;

		int TriangleCount;
		int VertexCount;
		int IndiceCount;

		glm::vec3 MinPoint;
		glm::vec3 MaxPoint;

		uint32_t PackageID;
		uint32_t MaterialID;
		std::string Name;

		std::vector<DataBlock::Vertex> VertexData; // Big
		std::vector<uint32_t> IndiceData;  // Big


	};
}


#endif // !OE1_CORE_STATIC_MESH_PKG_H_
