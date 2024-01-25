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

			void Render(IVRenderStack::IVDrawData& _data);
		};
	}
}

#endif // !OE1_TRANSPARENT_MESH_RENDERER_H_
