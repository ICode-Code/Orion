#ifndef OE1_MODEL_PKG_H_
#define OE1_MODEL_PKG_H_

#include "CoreStaticMeshPkg.h"

namespace OE1Core
{
	struct ModelPkg
	{
		std::string Name;
		uint32_t PackageID;
		std::vector<CoreStaticMeshPkg> MeshList;
		
	};
}

#endif // !OE1_MODEL_PKG_H_
