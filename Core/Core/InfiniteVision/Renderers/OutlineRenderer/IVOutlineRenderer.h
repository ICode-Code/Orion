#ifndef OE1_IV_OUTLINE_RENDERER_H_
#define OE1_IV_OUTLINE_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "EntityType.h"

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

			void Render(ActiveEntity* _active_entity, int _camera_idx);


		protected:
			void IssueProxyRender(Entity _entity, int _camera_idx);
			void IssueSolidOutLineRender(Entity _entity, int _camera_idx);

		protected: // Util
			bool ValidEntityToOutline(EntityType _type);

			IVModel* GetRenderbaleModel(Entity _entity);
		};
	}
}

#endif // !OE1_IV_OUTLINE_RENDERER_H_
