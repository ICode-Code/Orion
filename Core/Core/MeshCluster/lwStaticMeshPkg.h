#ifndef OE1_LW_STATIC_MESH_PKG_H_
#define OE1_LW_STATIC_MESH_PKG_H_

#include <stdint.h>
#include "../Material/MasterMaterial.h"

namespace OE1Core
{
	struct lwStaticMeshPkg
	{
		unsigned int VAO;
		unsigned int IBO;

		int IndiceCount;
		int DrawCount;
		uint32_t PackageID;
		uint32_t MaterialID;
		MasterMaterial* Material = nullptr;
	};
}

#endif // !OE1_LW_STATIC_MESH_PKG_H_
