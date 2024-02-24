#ifndef OE1_CORE_MESH_INSTANCE_RENDER_DESCRIPTOR_H_
#define OE1_CORE_MESH_INSTANCE_RENDER_DESCRIPTOR_H_

#include <stdint.h>
#include "CoreMeshDescriptor.h"
#include "../Material/MasterMaterial.h"

namespace OE1Core
{
	struct CoreMeshInstanceRenderDescriptor
	{
		unsigned int VAO;
		unsigned int IBO;

		int IndiceCount;
		int DrawCount;

		uint32_t PackageID;
		uint32_t MaterialID;
		MasterMaterial* Material = nullptr;
		CoreMeshDescriptor::CoreMeshType Type;
		
	};
}

#endif // !OE1_CORE_INSTANCE_RENDER_DESCRIPTOR_H_
