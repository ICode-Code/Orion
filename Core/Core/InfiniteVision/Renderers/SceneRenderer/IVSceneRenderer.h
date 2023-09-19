#ifndef OE1_SCENE_RENDERER_H_
#define OE1_SCENE_RENDERER_H_

#include "../IIVRenderer.h"
#include "../../RenderStack/RenderStack.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVSceneRenderer
		{
		public:
			IVSceneRenderer();
			~IVSceneRenderer();

			void Render(IVRenderStack* _render_stack);

		protected:
			IVOpaqueMeshRenderer* m_OpaqueMeshRenderer;
		};
	}
}

#endif // !OE1_SCENE_RENDERER_H_
