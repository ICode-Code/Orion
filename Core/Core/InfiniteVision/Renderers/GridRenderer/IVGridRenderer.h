#ifndef OE1_IV_GRID_RENDERER_H_
#define OE1_IV_GRID_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../../../Grid/Grid.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVGridRenderer : IVBaseRenderer
		{
		public:
			IVGridRenderer();
			~IVGridRenderer();

			void Render(const Grid& _grid, int _camera_idx);
		};
	}
}

#endif // !OE1_IV_GRID_RENDERER_H_
