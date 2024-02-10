#ifndef OE1_CORE_RENDER_COMPONENTS
#define OE1_CORE_RENDER_COMPONENTS

#include "../../../MeshCluster/lwStaticMeshPkg.h"

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
			struct IVCoreDrawPackage
			{
				Shader* SHADER = nullptr;
				/// <summary>
				/// IT can be used as an offset.
				/// THIS MATERIAL ID IS UNIQE IN THE LIST JUST LKE THE MESH ID
				/// </summary>
				uint32_t MATERIAL_ID;
				/// <summary>
				/// Just incase we need it
				/// </summary>
				uint32_t MESH_ID;
				std::vector<lwStaticMeshPkg*> MESH_LIST;
			};

			using IVCoreDrawDataBuffer = std::unordered_map<uint32_t, IVCoreDrawPackage>;
		}
	}
}

#endif // !OE1_CORE_RENDER_COMPONENTS
