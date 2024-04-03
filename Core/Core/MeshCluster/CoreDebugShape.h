#ifndef OE1_CORE_DEBUG_SHAPE_H_
#define OE1_CORE_DEBUG_SHAPE_H_

#include "CoreRenderableMesh.h"


namespace OE1Core
{
	struct CoreDebugShape : public CoreRenderableMeshPackage
	{
		int DrawType;
		int InstanceCount = 0;
		uint64_t ShapeID = 0;
	};
}

#endif // !OE1_CORE_DEBUG_SHAPE_H_
