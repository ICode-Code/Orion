#ifndef OE1_RENDER_STACK_H_
#define OE1_RENDER_STACK_H_

#include "../../MeshCluster/lwStaticMeshPkg.h"

#include <vector>
#include <unordered_map>

namespace OE1Core
{
	namespace Renderer
	{
		class IVRenderStack
		{
			friend class IVMasterRenderer;
			friend class IVMeshRenderer;
		public:
			IVRenderStack() = default;
			~IVRenderStack();
			
			using IVDrawData = std::unordered_map<MaterialType, std::pair<Shader*, std::vector<lwStaticMeshPkg*>>>;
			void RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, MaterialType _type);
			void RegisterTransparentMesh(lwStaticMeshPkg* _mesh, MaterialType _type);

			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveOpaqueMesh(uint32_t _package_id);
			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveTransparentMesh(uint32_t __package_id);


		protected:
			IVRenderStack::IVDrawData s_OpaqueMeshList;
			IVRenderStack::IVDrawData s_TransparentMeshList;

		};
	}
}

#endif // !OE1_RENDER_STACK_H_
