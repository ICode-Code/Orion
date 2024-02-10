#ifndef OE1_RENDER_STACK_H_
#define OE1_RENDER_STACK_H_

#include "../../MeshCluster/lwStaticMeshPkg.h"
#include "CoreRenderComponent/CoreRenderComponent.h"

#include <vector>


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
			
			void RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id);
			void RegisterTransparentMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id);
			void RegisterFlatMaterialMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id);

			
			/// <summary>
			/// Since we do not have access to indiviual instance
			/// this will decreament instance count and if the instance count is 0
			/// it will remove it completely
			/// </summary>
			/// <param name="_id"></param>
			void PurgeFromStack(uint32_t _mesh_id);
			std::vector<lwStaticMeshPkg*> QueryLWStaticMeshByMaterial(uint32_t _material_id, bool _clear_existing);

		protected:

			Core::IVCoreDrawDataBuffer s_FlatMaterialMeshList;
			Core::IVCoreDrawDataBuffer s_OpaqueMeshList;
			Core::IVCoreDrawDataBuffer s_TransparentMeshList;


		private:
			void PurgeFromMeshList(Core::IVCoreDrawDataBuffer& buffer, uint32_t _mesh_id);
			/// <summary>
			/// This function will collect all the lwStaticMeshPkg data
			/// which use the same material.
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void CollectLWMeshByMaterial(Core::IVCoreDrawDataBuffer& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _material_id);
			/// <summary>
			/// This function will collect all the lwStaticMeshPkg data
			/// which use the same material and REMOVE them from the original list - really important
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void ClearCollectLWMeshByMaterial(Core::IVCoreDrawDataBuffer& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _material_id);


		private:
			void RegisterCoreMesh(Core::IVCoreDrawDataBuffer& _buffer, lwStaticMeshPkg* _mesh, uint32_t _mesh_id);
		};
	}
}

#endif // !OE1_RENDER_STACK_H_
