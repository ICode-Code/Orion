#ifndef OE1_SELF_COMPONENT_H_
#define OE1_SELF_COMPONENT_H_

#include <stdint.h>

namespace OE1Core
{
	class Scene;
	class Entity;

	namespace Component
	{
		class SelfComponent
		{
		public:
			SelfComponent(Entity* _entity, Scene* _scene);
			~SelfComponent();

			Entity* GetEntity();
			Scene* GetScene();
			uint32_t GetEntityID();

		protected:
			Scene* m_Scene = nullptr;
			Entity* m_Entity = nullptr;
			uint32_t m_EntityID;
		};
	}
}

#endif // !OE1_SELF_COMPONENT_H_
