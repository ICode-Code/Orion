#ifndef OE1_RENDER_STACK_H_
#define OE1_RENDER_STACK_H_

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
			
			void RegisterOpaqueStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
			void RegisterTransparentStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
			void RegisterFlatMaterialStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);

			void RegisterOpaqueSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
			void RegisterTransparentSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
			void RegisterFlatMaterialSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);

			
			/// <summary>
			/// Since we do not have access to indiviual instance
			/// this will decreament instance count and if the instance count is 0
			/// it will remove it completely
			/// </summary>
			/// <param name="_id"></param>
			void PurgeFromStack(uint32_t _mesh_id);
			std::vector<CoreMeshInstanceRenderDescriptor*> QueryLWStaticMeshByMaterial(uint32_t _material_id, bool _clear_existing);
			std::vector<CoreMeshInstanceRenderDescriptor*> QueryLWDynamicMeshByMaterial(uint32_t _material_id, bool _clear_existing);

		protected:

			Core::IVCoreDrawStaticMeshDataBuffer m_STATIC_MESH_FLAT_MATERIAL_BUFFER;
			Core::IVCoreDrawStaticMeshDataBuffer m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER;
			Core::IVCoreDrawStaticMeshDataBuffer m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER;

			Core::IVCoreDrawDynamicMeshDataBuffer m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER;
			Core::IVCoreDrawDynamicMeshDataBuffer m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER;
			Core::IVCoreDrawDynamicMeshDataBuffer m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER;


		private:
			void PurgeFromStaticMeshList(Core::IVCoreDrawStaticMeshDataBuffer& buffer, uint32_t _mesh_id);
			/// <summary>
			/// This function will collect all the CoreMeshInstanceRenderDescriptor data
			/// which use the same material.
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void CollectLWStaticMeshByMaterial(Core::IVCoreDrawStaticMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id);
			/// <summary>
			/// This function will collect all the CoreMeshInstanceRenderDescriptor data
			/// which use the same material and REMOVE them from the original list - really important
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void ClearCollectLWStaticMeshByMaterial(Core::IVCoreDrawStaticMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id);



			void PurgeFromDynamicMeshList(Core::IVCoreDrawDynamicMeshDataBuffer& buffer, uint32_t _mesh_id);
			/// <summary>
			/// This function will collect all the lwDynamicMesh data
			/// which use the same material.
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void CollectLWDynamicMeshByMaterial(Core::IVCoreDrawDynamicMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id);
			/// <summary>
			/// This function will collect all the lwDynamicMesh data
			/// which use the same material and REMOVE them from the original list - really important
			/// </summary>
			/// <param name="_mem">Source</param>
			/// <param name="_buffer">Destination</param>
			/// <param name="_material_id">Filter</param>
			void ClearCollectLWDynamicMeshByMaterial(Core::IVCoreDrawDynamicMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id);


		private:
			void RegisterCoreStaticMesh(Core::IVCoreDrawStaticMeshDataBuffer& _buffer, CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
			void RegisterCoreDynamicMesh(Core::IVCoreDrawDynamicMeshDataBuffer& _buffer, CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id);
		};
	}
}

#endif // !OE1_RENDER_STACK_H_
