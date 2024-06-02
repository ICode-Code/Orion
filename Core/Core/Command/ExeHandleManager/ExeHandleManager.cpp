#include "ExeHandleManager.h"


namespace OE1Core
{
	namespace CommandHnd
	{
		ExeHandleManager::ExeHandleManager(Scene* _scene)
		{
			s_CommandContextHighFreOperationHandler = new  CommandHnd::CommandContextHighFreqOperationHandle(_scene);
			s_CommandContextOperationExeHandler = new  CommandHnd::CommandContextOperationExeHandler(_scene);
			s_CommandIgnitionExecutionHandler = new  CommandHnd::CommandIgnitionExecutionHandle(_scene);
			s_CommandMasterOperationExecutionHandler = new  CommandHnd::CommandMasterOperationExecutionHandle(_scene);
			s_CommandSceneIntializationExecuationHandler = new CommandHnd::CommandSceneInitalization(_scene);
		}
		ExeHandleManager::~ExeHandleManager()
		{
			delete s_CommandContextHighFreOperationHandler;
			delete s_CommandContextOperationExeHandler;
			delete s_CommandIgnitionExecutionHandler;
			delete s_CommandMasterOperationExecutionHandler;
		}

		void ExeHandleManager::ProcessHighFrequencyCommands()
		{
		}
		void ExeHandleManager::ProcessContextCommandQueue()
		{
			CommandHnd::CommandContextOperationExeHandler::ProcessQueue();
			CommandHnd::CommandSceneInitalization::ProcessQueue();

		}
		void ExeHandleManager::ProcessLowFrequencyCommands()
		{
			CommandIgnitionExecutionHandle::ProcessQueue();
			CommandMasterOperationExecutionHandle::ProcessQueue();
		}
	}
}