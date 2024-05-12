#include "CommandContextHighFreqOperationHandler.h"


namespace OE1Core
{
	namespace CommandHnd
	{
		CommandContextHighFreqOperationHandle::CommandContextHighFreqOperationHandle(Scene* _scene)
			: ExecutionHandleBase{_scene}
		{

		}
		CommandContextHighFreqOperationHandle::~CommandContextHighFreqOperationHandle() 
		{

		}
		void CommandContextHighFreqOperationHandle::ProcessQueue()
		{
			ProcessClickReadbackCommand();
		}



		// Process
		void CommandContextHighFreqOperationHandle::ProcessClickReadbackCommand()
		{
			while (!Command::s_EntitySelectionCommands.empty())
			{
				CommandDef::EntitySelectionCommandDef& _command = Command::s_EntitySelectionCommands.back();

				uint32_t entity_id = static_cast<uint32_t>(m_Scene->m_MasterSceneCamera->Camera->MainFB()->Readi1(1, _command.posX, _command.posY));

				Entity entity_query = SceneManager::GetActiveScene()->GetEntity(entity_id, true);

				if (entity_query.IsFunctional())
				{
					if (_command.Batch)
					{
						m_Scene->GetActiveEntity()->PickBatch(entity_query);
					}
					else
					{
						m_Scene->GetActiveEntity()->Pick(entity_query);
					}
				}
				else
					m_Scene->GetActiveEntity()->FlushSelection();

				Command::s_EntitySelectionCommands.pop();
			}
		}
	}
}