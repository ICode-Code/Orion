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
			
			using IVDrawList = std::pair<Shader*, std::vector<lwStaticMeshPkg*>>;
			using IVDrawData = std::unordered_map<MaterialType, IVDrawList>;
			void RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, MaterialType _type);
			void RegisterTransparentMesh(lwStaticMeshPkg* _mesh, MaterialType _type);

			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveOpaqueMesh(MaterialType _package_id);
			// This will remove the mesh form the stack comletely regarless of the instance count
			// do this if the instance count is 0 or if you don't want to NOT render the model
			void RemoveTransparentMesh(MaterialType __package_id);


			/// <summary>
			/// This dud find and return draw list based on the material type
			/// Start With Opaque Mesh, You can use the optional parameter to change this
			/// </summary>
			/// <param name="_type">Which type of material this draw list uses</param>
			/// <param name="_start_with_opaque">set it false if you want to start searching from transparent and move to opaque</param>
			/// <returns></returns>
			IVDrawList* GetDrawList(MaterialType _type, bool _start_with_opaque = true);
			void SearchAndDestroy(MaterialType _type);

		protected:
			IVRenderStack::IVDrawData s_OpaqueMeshList;
			IVRenderStack::IVDrawData s_TransparentMeshList;

		};
	}
}

#endif // !OE1_RENDER_STACK_H_
