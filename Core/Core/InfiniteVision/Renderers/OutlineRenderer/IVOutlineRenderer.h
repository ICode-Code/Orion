#ifndef OE1_IV_OUTLINE_RENDERER_H_
#define OE1_IV_OUTLINE_RENDERER_H_


#include "../IVBaseRenderer.h"

namespace OE1Core
{
	class ActiveEntity;
	namespace Renderer
	{
		class IVOutlineRenderer : public IVBaseRenderer
		{
		public:
			IVOutlineRenderer();
			~IVOutlineRenderer();

			void Render(ActiveEntity _active_entity);
		};
	}
}

#endif // !OE1_IV_OUTLINE_RENDERER_H_
