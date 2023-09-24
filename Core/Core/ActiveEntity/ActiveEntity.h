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

		bool IsHold();
		void Hold(bool _hold);
		void Pick(Entity _entity, bool _hold = false);
		void PickBatch(Entity _entity);
		bool IsPicked(Entity _entity);
		void FlushSelection();
		bool ValidSelection();
		Entity GetActive();
		std::vector<Entity>& GetRegistry();
		bool IsBatchMode();


	protected:
		std::vector<Entity> m_ActiveRegistry;
		bool m_BatchMode = false;
		bool m_EntitySelected = false;
		bool m_Hold = false;

	};
}

#endif // !OE1_ACTIVE_ENTITY_H_
