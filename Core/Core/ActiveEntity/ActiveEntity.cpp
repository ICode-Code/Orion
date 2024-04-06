#include "ActiveEntity.h"

namespace OE1Core
{
	ActiveEntity::ActiveEntity()
	{

	}
	ActiveEntity::~ActiveEntity()
	{
		if (m_OnFlushCallback)
			delete m_OnFlushCallback;
	}
	void ActiveEntity::Hold(bool _val) { m_Hold = _val; }
	bool ActiveEntity::IsHold() { return m_Hold; }
	void ActiveEntity::Pick(Entity _entity, bool _hold)
	{
		this->FlushSelection();

		m_Hold = _hold;
		m_EntitySelected = true;

		m_ActiveRegistry.push_back(_entity);
	}
	void ActiveEntity::PickBatch(Entity _entity)
	{
		m_EntitySelected = true;
		m_BatchMode = true;
		
		// For hightlight
		m_ActiveRegistry.push_back(_entity);

	}
	bool ActiveEntity::IsPicked(Entity _entity)
	{
		auto iter = std::find_if(m_ActiveRegistry.begin(), m_ActiveRegistry.end(), [_entity](Entity CEntity)
			{
				return (uint32_t)CEntity == (uint32_t)_entity;
			});
		return iter != m_ActiveRegistry.end();
	}
	void ActiveEntity::FlushSelection()
	{
		if (m_OnFlushCallback)
			(*m_OnFlushCallback)(m_ActiveRegistry);

		m_ActiveRegistry.clear();
		
		m_Hold = false;
		m_BatchMode = false;
		m_EntitySelected = false;
	}
	void ActiveEntity::SetOnFlushCallback(std::function<void(std::vector<Entity>&)>* _flush_list)
	{
		m_OnFlushCallback = _flush_list;
	}
	bool ActiveEntity::ValidSelection() { return m_EntitySelected; }
	Entity ActiveEntity::GetActive() { return m_ActiveRegistry.back(); }
	std::vector<Entity>& ActiveEntity::GetRegistry() { return m_ActiveRegistry; }
	bool ActiveEntity::IsBatchMode() { return m_BatchMode; }
}