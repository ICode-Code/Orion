#ifndef OE1_RENDER_STACK_H_
#define OE1_RENDER_STACK_H_

#include "../../MeshCluster/lwStaticMeshPkg.h"
#include <vector>

namespace OE1Core
{
	namespace Renderer
	{
		class IVRenderStack
		{
			friend class IVMasterRenderer;
			friend class IVSceneRenderer;
		public:
			IVRenderStack() = default;
			~IVRenderStack();

			void RegisterOpaqueMesh(lwStaticMeshPkg* _mesh);
			void RegisterTransparentMesh(lwStaticMeshPkg* _mesh);

			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveOpaqueMesh(uint32_t _package_id);
			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveTransparentMesh(uint32_t __package_id);


		protected:
			std::vector<lwStaticMeshPkg*> s_OpaqueMeshList;
			std::vector<lwStaticMeshPkg*> s_TransparentMeshList;

		};
	}
}

#endif // !OE1_RENDER_STACK_H_
