#ifndef OE1_IV_DEBUG_SHAPE_RENDERER_H_
#define OE1_IV_DEBUG_SHAPE_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../Core/Mesh/DebugMesh/DebugMesh.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVDebugShapeRenderer : public IVBaseRenderer
		{
		public:
			IVDebugShapeRenderer();
			~IVDebugShapeRenderer();

			void Render(std::unordered_map<uint32_t, DebugMesh*>& _shapes);
			void Render(std::unordered_map<uint32_t, DebugMesh*>& _shapes, int _camera_idx);
		};
	}
}

#endif // !OE1_IV_DEBUG_SHAPE_RENDERER_H_
