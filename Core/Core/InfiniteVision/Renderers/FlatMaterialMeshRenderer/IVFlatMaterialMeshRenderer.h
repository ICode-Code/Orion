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

			void Render(Core::IVCoreDrawDataBuffer& _data, int _camera_idx);
		};
	}
}


#endif // !OE1_FLAT_MAT_MESH_RENDERER_H_
