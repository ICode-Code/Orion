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

			void Render(std::vector<lwStaticMeshPkg*>& _list);

		protected:

		};
	}
}

#endif // !OE1_IV_OPAQUE_MESH_RENDERER_H_
