#ifndef OE1_TRANSPARENT_MESH_RENDERER_H_
#define OE1_TRANSPARENT_MESH_RENDERER_H_

#include "../IVBaseRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		class IVTransparentMeshRenderer : public IVBaseRenderer
		{
		public:
			IVTransparentMeshRenderer() = default;
			~IVTransparentMeshRenderer();

			void Render(Core::IVCoreDrawStaticMeshDataBuffer& _data, int _camera_idx);
			void Render(Core::IVCoreDrawDynamicMeshDataBuffer& _data, int _camera_idx);
		};
	}
}

#endif // !OE1_TRANSPARENT_MESH_RENDERER_H_
