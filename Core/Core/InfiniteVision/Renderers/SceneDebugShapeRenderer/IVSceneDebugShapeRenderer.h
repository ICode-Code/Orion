#ifndef OE1_IV_SCENE_DEBUG_SHAPE_RENDERER_H_
#define OE1_IV_SCENE_DEBUG_SHAPE_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../Core/DS/TurboOT/TurboOTNode.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVSceneDebugShapeRenderer : public IVBaseRenderer
		{
		public:
			IVSceneDebugShapeRenderer();
			~IVSceneDebugShapeRenderer();

			void Render(const DS::TurboOTNode& _root_node);
			void Render(const DS::TurboOTNode& _root_node, int _camera_idx);

		protected:
			void RecursiveDraw(const DS::TurboOTNode& _root_node);
		};
	}
}

#endif // !OE1_IV_SCENE_DEBUG_SHAPE_RENDERER_H_
