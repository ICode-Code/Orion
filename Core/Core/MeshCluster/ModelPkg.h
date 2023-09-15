#ifndef OE1_MODEL_PKG_H_
#define OE1_MODEL_PKG_H_

#include "CoreStaticMeshPkg.h"

namespace OE1Core
{
	struct ModelPkg
	{
		std::string Name;
		uint32_t PackageID;
		glm::vec3 Extents;
		int SubMeshCount	= 0;
		int VertexCount		= 0;
		int IndicesCount	= 0;
		int TriangleCount	= 0;
		GLuint SnapShot		= 0;
		std::vector<CoreStaticMeshPkg> MeshList;
		
	};
}

#endif // !OE1_MODEL_PKG_H_
