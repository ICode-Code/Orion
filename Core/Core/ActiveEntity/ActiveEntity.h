#ifndef OE1_ACTIVE_ENTITY_H_
#define OE1_ACTIVE_ENTITY_H_

#include "../Scene/Entity.h"

#include <vector>

namespace OE1Core
{
	class ActiveEntity
	{
	public:
		ActiveEntity() = default;
		~ActiveEntity() = default;

		static void Grab(bool _grab);
		static void Pick(Entity _entity);
		static void PickBatch(Entity _entity);
		static bool IsPicked(Entity _entity);
		static void FlushSelection();
		static bool ValidSelection();
		static Entity GetActive();
		static std::vector<Entity>& GetRegistry();
		static bool IsBatchMode();


	protected:
		inline static std::vector<Entity> s_ActiveRegistry;
		inline static bool s_BatchMode = false;
		inline static bool s_EntitySelected = false;
		inline static bool s_HoldEntity = false;

	};
}

#endif // !OE1_ACTIVE_ENTITY_H_
