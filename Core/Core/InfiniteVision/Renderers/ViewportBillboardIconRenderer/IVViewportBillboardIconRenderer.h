#ifndef OE1_IVVIEWPORT_BILLBOARD_ICON_RENDERER_H_
#define OE1_IVVIEWPORT_BILLBOARD_ICON_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../../../Mesh/ViewportBillboardIcon/ViewportBillboardIcon.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVViewportBillboardIconRenderer : public IVBaseRenderer
		{
		public:
			IVViewportBillboardIconRenderer();
			~IVViewportBillboardIconRenderer();

			void Render(std::unordered_map<ViewportIconBillboardType, ViewportBillboardIcon*>& _sprite_list, int _camera_idx);
		};
	}
}

#endif // !OE1_IVVIEWPORT_BILLBOARD_ICON_RENDERER_H_
