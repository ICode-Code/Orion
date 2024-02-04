#ifndef OE1_MESH_RENDERER_H_
#define OE1_SCEOE1_MESH_RENDERER_H_NE_RENDERER_H_

#include "../IIVRenderer.h"
#include "../../RenderStack/RenderStack.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVMeshRenderer
		{
		public:
			IVMeshRenderer();
			~IVMeshRenderer();

			void Render(IVRenderStack* _render_stack, int _camera_idx);

		protected:
			IVOpaqueMeshRenderer* m_OpaqueMeshRenderer = nullptr;
			IVTransparentMeshRenderer* m_TransparentMeshRenderer = nullptr;
			IVFlatMaterialMeshRenderer* m_FlatMaterialMeshRenderer = nullptr;
		};
	}
}

#endif // !OE1_MESH_RENDERER_H_
