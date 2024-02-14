#ifndef OE1_EXE_HANDLE_MANAGER_H_
#define OE1_EXE_HANDLE_MANAGER_H_

#include "../CommandExecutionHnd/ICommandExecutionHnd.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		class ExeHandleManager
		{
		public:
			ExeHandleManager(Scene* _scene);
			~ExeHandleManager();

			static void ProcessHighFrequencyCommands();
			static void ProcessLowFrequencyCommands();
			
			/// <summary>
			/// Any command that require the MainThread Attention
			/// </summary>
			static void ProcessContextCommandQueue();


		private:
			inline static CommandHnd::CommandContextHighFreqOperationHandle* s_CommandContextHighFreOperationHandler = nullptr;
			inline static CommandHnd::CommandContextOperationExeHandler* s_CommandContextOperationExeHandler = nullptr;
			inline static CommandHnd::CommandIgnitionExecutionHandle* s_CommandIgnitionExecutionHandler = nullptr;
			inline static CommandHnd::CommandMasterOperationExecutionHandle* s_CommandMasterOperationExecutionHandler = nullptr;

		};
	}
}

#endif // !OE1_EXE_HANDLE_MANAGER_H_
