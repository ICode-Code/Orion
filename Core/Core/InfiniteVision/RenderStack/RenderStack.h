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
			using IVDrawData = std::unordered_map<uint32_t, IVDrawList>;
			void RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, uint32_t _id);
			void RegisterTransparentMesh(lwStaticMeshPkg* _mesh, uint32_t _id);
			void RegisterFlatMaterialMesh(lwStaticMeshPkg* _mesh, uint32_t _id);

			
			/// <summary>
			/// Since we do not have access to indiviual instance
			/// this will decreament instance count and if the instance count is 0
			/// it will remove it completely
			/// </summary>
			/// <param name="_id"></param>
			void PurgeFromStack(uint32_t _id);
			std::vector<lwStaticMeshPkg*> QueryLWStaticMesh(uint32_t _id, bool _clear_existing);

		protected:
			IVRenderStack::IVDrawData s_FlatMaterialMeshList; // to Avoid binding non existing material
			IVRenderStack::IVDrawData s_OpaqueMeshList;
			IVRenderStack::IVDrawData s_TransparentMeshList;


		private:
			void PurgeFromMeshList(IVRenderStack::IVDrawData& buffer, uint32_t _id);
			void CollectLWMesh(IVRenderStack::IVDrawData& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _id);

			// This will remove the existing and return the value
			void ClearCollectLWMesh(IVRenderStack::IVDrawData& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _id);

		};
	}
}

#endif // !OE1_RENDER_STACK_H_
