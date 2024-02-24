#ifndef OE1_FLAT_MAT_MESH_RENDERER_H_
#define OE1_FLAT_MAT_MESH_RENDERER_H_


#include "../IVBaseRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		class IVFlatMaterialMeshRenderer : public IVBaseRenderer
		{
		public:
			IVFlatMaterialMeshRenderer() = default;
			~IVFlatMaterialMeshRenderer();

			/// <summary>
			/// For Static Mesh
			/// </summary>
			/// <param name="_data"></param>
			/// <param name="_camera_idx"></param>
			void Render(Core::IVCoreDrawStaticMeshDataBuffer& _data, int _camera_idx);

			/// <summary>
			/// For Skinned Mesh
			/// </summary>
			/// <param name="_data"></param>
			/// <param name="_camera_idx"></param>
			void Render(Core::IVCoreDrawDynamicMeshDataBuffer& _data, int _camera_idx);
		};
	}
}


#endif // !OE1_FLAT_MAT_MESH_RENDERER_H_
