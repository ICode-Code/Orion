#ifndef OE1_ACTIVE_ENTITY_H_
#define OE1_ACTIVE_ENTITY_H_

#include "../Scene/Entity.h"

#include <vector>
#include <functional>

namespace OE1Core
{
	class ActiveEntity
	{
	public:
		ActiveEntity();
		~ActiveEntity();

		bool IsHold();
		void Hold(bool _hold);
		void Pick(Entity _entity, bool _hold = false);
		void PickBatch(Entity _entity);
		bool IsPicked(Entity _entity);
		void FlushSelection();
		bool ValidSelection();
		void SetOnFlushCallback(std::function<void(std::vector<Entity>&)>* _flush_list);
		Entity GetActive();
		std::vector<Entity>& GetRegistry();
		bool IsBatchMode();
		
	protected:
		std::vector<Entity> m_ActiveRegistry;
		bool m_BatchMode = false;
		bool m_EntitySelected = false;
		bool m_Hold = false;
		std::function<void(std::vector<Entity>&)>* m_OnFlushCallback = nullptr;
	};
}

#endif // !OE1_ACTIVE_ENTITY_H_
