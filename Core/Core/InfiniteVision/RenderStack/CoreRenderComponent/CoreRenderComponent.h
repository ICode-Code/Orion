#ifndef OE1_CORE_RENDER_COMPONENTS
#define OE1_CORE_RENDER_COMPONENTS

#include "../../../MeshCluster/CoreMeshInstanceRenderDescriptor.h"

#include <vector>
#include <unordered_map>

namespace OE1Core
{
	namespace Renderer
	{
		namespace Core
		{
			/// <summary>
			/// A group of mesh data that use the same pipleline/ material and shader so we can call them by 
			/// attaching one shader and issue a draw call by attaching each mesh material
			/// </summary>
			struct IVCoreDrawStaticMeshPackage
			{
				Shader* SHADER = nullptr;
				uint32_t MATERIAL_ID;
				uint32_t MESH_ID;
				std::vector<CoreMeshInstanceRenderDescriptor*> MESH_LIST;
			};

			using IVCoreDrawStaticMeshDataBuffer = std::unordered_map<uint32_t, IVCoreDrawStaticMeshPackage>;



			/// <summary>
			/// A group of mesh data that use the same pipleline/ material and shader so we can call them by 
			/// attaching one shader and issue a draw call by attaching each mesh material
			/// </summary>
			struct IVCoreDrawDynamicMeshPackage
			{
				Shader* SHADER = nullptr;
				uint32_t MATERIAL_ID;
				uint32_t MESH_ID;
				std::vector<CoreMeshInstanceRenderDescriptor*> MESH_LIST;
			};

			using IVCoreDrawDynamicMeshDataBuffer = std::unordered_map<uint32_t, IVCoreDrawDynamicMeshPackage>;
		}
	}
}

#endif // !OE1_CORE_RENDER_COMPONENTS
