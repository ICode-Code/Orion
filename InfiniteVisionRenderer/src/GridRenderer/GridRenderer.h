#ifndef OE1_GRID_RENDERER_H_
#define OE1_GRID_RENDERER_H_

#include "../BaseRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) GridRenderer : public BaseRenderer
		{
		public:
			GridRenderer(SceneInterface* _scene_interface, CoreSystemInterface* _coreSystem_interface);
			~GridRenderer();
			void Render();

		protected:
			Grid* m_Grid = nullptr;
		};
	}
}

#endif // !OE1_GRID_RENDERER_H_
