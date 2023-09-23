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

		void Grab(bool _grab);
		void Pick(Entity _entity);
		void PickBatch(Entity _entity);
		bool IsPicked(Entity _entity);
		void FlushSelection();
		bool ValidSelection();
		Entity GetActive();
		std::vector<Entity>& GetRegistry();
		bool IsBatchMode();


	protected:
		std::vector<Entity> s_ActiveRegistry;
		bool s_BatchMode = false;
		bool s_EntitySelected = false;
		bool s_HoldEntity = false;

	};
}

#endif // !OE1_ACTIVE_ENTITY_H_
