#include "ActiveEntity.h"


namespace OE1Core
{
	void ActiveEntity::Grab(bool _grab) { s_HoldEntity = _grab; }

	void ActiveEntity::Pick(Entity _entity) 
	{
		s_EntitySelected = true;
		s_BatchMode = false;
		s_ActiveRegistry.clear();
		s_ActiveRegistry.push_back(_entity);
	}
	void ActiveEntity::PickBatch(Entity _entity)
	{
		s_EntitySelected = true;
		s_BatchMode = true;
		s_ActiveRegistry.push_back(_entity);
	}
	bool ActiveEntity::IsPicked(Entity _entity)
	{
		auto iter = std::find_if(s_ActiveRegistry.begin(), s_ActiveRegistry.end(), [_entity](Entity CEntity)
			{
				return (uint32_t)CEntity == (uint32_t)_entity;
			});
		return iter != s_ActiveRegistry.end();
	}
	void ActiveEntity::FlushSelection()
	{
		s_ActiveRegistry.clear();
		s_BatchMode = false;
		s_EntitySelected = false;
	}
	bool ActiveEntity::ValidSelection() { return s_EntitySelected; }
	Entity ActiveEntity::GetActive() { return s_ActiveRegistry.back(); }
	std::vector<Entity>& ActiveEntity::GetRegistry() { return s_ActiveRegistry; }
	bool ActiveEntity::IsBatchMode() { return s_BatchMode; }
}