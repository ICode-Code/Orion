#ifndef OE1_IV_OPAQUE_MESH_RENDERER_H_
#define OE1_IV_OPAQUE_MESH_RENDERER_H_

#include "../IVBaseRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVOpaqueMeshRenderer : public IVBaseRenderer
		{
		public:
			IVOpaqueMeshRenderer() = default;
			~IVOpaqueMeshRenderer();

			void Render(Core::IVCoreDrawStaticMeshDataBuffer& _data, int _camera_idx);
			void Render(Core::IVCoreDrawDynamicMeshDataBuffer& _data, int _camera_idx);
		};
	}
}

#endif // !OE1_IV_OPAQUE_MESH_RENDERER_H_
