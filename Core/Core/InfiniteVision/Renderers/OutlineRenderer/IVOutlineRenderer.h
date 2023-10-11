#ifndef OE1_IV_OUTLINE_RENDERER_H_
#define OE1_IV_OUTLINE_RENDERER_H_


#include "../IVBaseRenderer.h"

namespace OE1Core
{
	class Entity;
	class ActiveEntity;
	namespace Renderer
	{
		class IVOutlineRenderer : public IVBaseRenderer
		{
		public:
			IVOutlineRenderer();
			~IVOutlineRenderer();

			void Render(ActiveEntity* _active_entity);


		protected:
			void IssueProxyRender(Entity _entity);
			void IssueSolidOutLineRender(Entity _entity);
		};
	}
}

#endif // !OE1_IV_OUTLINE_RENDERER_H_
